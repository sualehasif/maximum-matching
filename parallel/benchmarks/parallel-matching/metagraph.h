#pragma once

#include <tuple>
#include "../../gbbs/gbbs.h"
#include "MaximalMatching.h"
#include "CherryTree.h"

struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

namespace gbbs {
    template <class Graph>
        inline sequence<std::tuple<uintE,uintE>> MetaGraphMatching(Graph& G) {
        using W = typename Graph::weight_type;
        using vertex = typename Graph::vertex;
        using edge = std::tuple<uintE, uintE, W>;
        using Label = uintE;
        using CherryTree = maxmatching::norm::MCherryTree<Label>;
        // initialize a sequence which maps vertices to their partners.
        sequence<uintE> partners;
        // initialize a sequence which maps vertices to whether they are even.
        sequence<char> even;

        // get an initial matching based on a greedy algorithm in parallel.
        auto unmatched = MaximalMatching(G);

        // TODO: find the unmatched vertices given the list of matched edges.

        // setup a vector of cherry trees based on the unmatched vertices.
        sequence<CherryTree> vct = sequence<CherryTree>::from_function(
                unmatched.size, [&](size_t i) { return CherryTree(unmatched[i]);}
                );

        // initialize a map which matches the cherry tree ID to the cherry tree.
        std::unordered_map<uintE , CherryTree*> activeCherryTrees;
        // initialize a hash table of the vertices which says whether they have been grabbed by a cherry tree.
        std::unordered_map<edge, char, pair_hash> edgeHashMap;

        // as long as we have cherry trees that can be matched loop over them.

        while (vct.size() > 1){
            // set up a list of edges that will be part of the meta graph.
            sequence<edge> metaEdges;

            // we now start growing
            bool canGrow;
            while(canGrow){
                // TODO: do a parallel loop over all the cherry trees
                // cilk_for (auto ct: vct)
                // TODO: fix this
                CherryTree& ct;

                // TODO: get the list of growable vertices for this round from the cherry tree.
                // setup a new list of growable vertices for the next round.
                sequence<uintE> growable;
                sequence<uintE> willGrow;

                // start growing the vertices.
                for (auto gv: growable){
                    auto map_f = [&](const uintE& src, const uintE& target, const W& wgh, const uintT& e){
                        if (partners[src] == target) return;

                        auto target_ct = activeCherryTrees[target];
                        auto target_partner = partners[target];

                        // TODO: figure out the way to get the ID of the edge from target to target_partner
                        edge eFromTarget;

                        if (target_ct == nullptr){
                            if (edgeHashMap[eFromTarget] == 1){
                                //TODO: verify this and update this when cherry trees are done.
                                // ct.add(e);
                                // ct.add(eFromTarget);
                                // eht[eFromTarget] = 0;
                            }
                        } else if (target_ct != ct){
                            // TODO: make this to use IDs
                            metaEdges.push_back(std::make_tuple(ct, target_ct, W(0)));
                        } else if (target_ct == ct){
                            if (even[target]) ct.makeBlossom(target);
                        }

                    };

                    // apply map_f to all the out_neighbors of gv.
                    G.get_vertex(gv).out_neighbors().map_with_index(map_f, false);
                }

                // TODO: update canGrow here.
            }


            if (metaEdges.empty()) break;
            else {
                Graph& metaGraph = sym_graph_from_edges(metaEdges);
                auto metaMatching = MetaGraphMatching(metaGraph);

                auto map_apply_matching = [&](const uintE& u, const uintE& v){
                    auto uCherryTree = activeCherryTrees[u];
                    auto vCherryTree = activeCherryTrees[v];

                    // uCherryTree.rotate(u);
                    // vCherryTree.rotate(v);

                    partners[u]=v;
                    partners[v]=u;

                    vct.erase(uCherryTree);
                    vct.erase(vCherryTree);
                };
            }
        }

        // TODO: update the matching based on the new partners index.
        // TODO: return that new matching.

        return sequence<std::tuple<uintE, uintE>>(1, std::make_pair(0,0));
    }



}
