#pragma once

#include <tuple>
#include "../../gbbs/gbbs.h"
#include "MaximalMatching.h"
#include "CherryTree.h"
#include "MVertex.h"
#include "parlay/primitives.h"
#include "../../gbbs/pbbslib/sparse_table.h"

struct pair_hash {
    template<class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

namespace maxmatching::norm {
    template<class Label>
    class MVertex;
}

namespace gbbs {
    // Wrapper for a hash function
    struct hashtup {
        inline size_t operator()(const uintE &a) const { return pbbslib::hash64_2(a); }
    };

    struct edge_hash {
        std::size_t operator()(const std::pair<uintE, uintE> &pair) const {
            return pbbslib::hash64_2(pair.first) ^ pbbslib::hash64_2(pair.second);
        }

        template<class W>
        std::size_t operator()(const std::tuple<uintE, uintE, W> &pair) {
            return pbbslib::hash64_2(std::get<0>(pair)) ^ pbbslib::hash64_2(std::get<1>(pair));
        }
    };

    template<class Graph>
    inline sequence<std::tuple<uintE, uintE>> MetaGraphMatching(Graph &G) {
        size_t n = G.n;
        using W = typename Graph::weight_type;
        using vertex = typename Graph::vertex;
        using edge = std::tuple<uintE, uintE, W>;
        using Label = uintE;
        using CherryTree = typename maxmatching::norm::MCherryTree<Label>;
        using MVertex = typename maxmatching::norm::MVertex<Label>;
        using HalfEdge = typename maxmatching::norm::HalfEdge<Label>;

        uintE matchingSize = 0;
        // todo: properly initialize a sequence which maps vertices to their partners.
        sequence<uintE> partners;
        // initialize a sequence which maps vertices to whether they are even.
        sequence<char> even;

        auto matched = sequence<uintE>::from_function(n, [](size_t i) { return i; });
        matchingSize = matched.size();

        // get an initial matching based on a greedy algorithm in parallel.
        auto greedyMatching = MaximalMatching(G);

        // update all the  matched vertices
        // Check that this is a valid matching
        par_for(0, greedyMatching.size(), [&](size_t i) {
            const auto &edge = greedyMatching[i];
            matched[std::get<0>(edge)] = -1;
            matched[std::get<1>(edge)] = -1;

            partners[std::get<0>(edge)] = std::get<1>(edge);
            partners[std::get<1>(edge)] = std::get<0>(edge);
        });

        // TODO: verify that the unmatched are actually the vertex ids of the unmatched vertices.
        sequence<uintE> unmatched = filter(matched, [](uintE v) { return matched[v] > 0; });

        // setup a vector of cherry trees based on the unmatched vertices.
        sequence<CherryTree> vct = sequence<CherryTree>::from_function(
                unmatched.size(), [&](size_t i) {
                    MVertex m_vtx = maxmatching::norm::MVertex<Label>(unmatched[i]);
                    return CherryTree(&m_vtx);
                }
        );

        // initialize a map which matches the cherry tree ID to the cherry tree.
        std::unordered_map<uintE, CherryTree *> activeCherryTrees;
        for(auto ct: vct){
            activeCherryTrees[ct.getId()] = &ct;
        }

        // initialize a hash table of the vertices which says whether they have been grabbed by a cherry tree.
        size_t edge_table_size = n;
        auto edgeHashMap = pbbslib::sparse_table<edge, bool, edge_hash>(edge_table_size, std::make_tuple(
                std::make_tuple(UINT_E_MAX, UINT_E_MAX, gbbs::empty{}), false), edge_hash());
        G.mapEdges([&](const uintE &u, const uintE &v, const W &wgh) {
            if (u < v) {
                edgeHashMap.insert(std::make_tuple(edge(u, v, gbbs::empty{}), true));
            }
        });
//        std::unordered_map<edge, char, pair_hash> edgeHashMap;

        // define the map over each cherry tree in a loop.
        auto map_ct = [&](CherryTree &ct, sequence<edge>& metaEdges, bool& canGrow) {
            // TODO: get the list of growable vertices for this round from the cherry tree.
            // setup a new list of growable vertices for the next round.
            std::vector<uintE> growable = ct.growable;
            std::vector<uintE> willGrow;

            // start growing the vertices.
            for (auto gv: growable) {
                auto map_f = [&](const uintE &src, const uintE &target, const W &wgh, const uintT &e) {
                    if (partners[src] == target) return;

                    auto target_tuple = activeCherryTrees.find(target);
                    auto target_partner = partners[target];

                    // TODO: figure out the way to get the ID of the edge from target to target_partner
                    auto vt = MVertex((uintE) target);
                    auto vtp = MVertex((uintE) target_partner);
                    HalfEdge eFromTarget(&vt, &vtp, nullptr);

                    if (target_tuple == activeCherryTrees.end()) {
                        if (edgeHashMap[eFromTarget].second) {
                            edgeHashMap[eFromTarget] = false;
                            //TODO: verify this and update this when cherry trees are done.
                            auto start = (uintE) src;
                            auto end = (uintE) target;
                            // FIXME: need to populate the inside with the right MVertex which is inside
                            auto ms = MVertex(start);
                            auto me = MVertex(end);

                            auto eLabel = (uintE) e;
                            auto he = HalfEdge(&ms, &me, nullptr);

                            ct.add(&he);
                            ct.add(&eFromTarget);
                        }
                    } else if (target_tuple->second->getId() != ct.getId()) {
                        // TODO: make this to use IDs
                        auto target_ct = target_tuple->second;
                        metaEdges.push_back(std::make_tuple(ct.getId(), target_ct->getId(), gbbs::empty{}));
                    } else if (target_tuple->second->getId() == ct.getId()) {
                        if (even[target]) {
                            auto start = (uintE) src;
                            auto end = (uintE) target;
                            // FIXME: need to populate the inside with the right MVertex which is inside
                            auto ms = MVertex(start);
                            auto me = MVertex(end);

                            auto eLabel = (uintE) e;

                            auto he = HalfEdge(&ms, &me, nullptr);
                            ct.makeBlossom(&he);
                        }
                    }

                };

                // apply map_f to all the out_neighbors of gv.
                G.get_vertex(gv).out_neighbors().map_with_index(map_f, false);

                // FIXME: figure out updating will Grow.
            }
            if (!willGrow.empty()) canGrow = true;
            ct.growable = willGrow;
        };

        // as long as we have cherry trees that can be matched loop over them.

        while (vct.size() > 1) {
            // set up a list of edges that will be part of the meta graph.
            sequence<edge> metaEdges;

            // we now start growing
            bool canGrow = false;
            while (canGrow) {
                parallel_for(0, vct.size(), [&](size_t i) { map_ct(vct[i], &metaEdges, &canGrow); });
            }


            if (metaEdges.empty()) break;
            else {
                Graph &metaGraph = sym_graph_from_edges(metaEdges);
                auto metaMatching = MetaGraphMatching(metaGraph);

                auto map_apply_matching = [&](const uintE &u, const uintE &v) {
                    auto uCherryTree = activeCherryTrees[u];
                    auto vCherryTree = activeCherryTrees[v];

                    // uCherryTree.rotate(u);
                    // vCherryTree.rotate(v);

                    partners[u] = v;
                    partners[v] = u;

                    vct.erase(uCherryTree);
                    vct.erase(vCherryTree);

                    pbbslib::write_add(&matchingSize, 1);
                };
            }
        }
        sequence<std::tuple<uintE, uintE>> finalMatching;

        parallel_for(0, n, [&](size_t i){
           if (i < partners[i]){
               finalMatching.push_back(std::make_pair(i, partners[i]));
           }
        });

        return sequence<std::tuple<uintE, uintE>>(1, std::make_pair(0, 0));
    }
}



