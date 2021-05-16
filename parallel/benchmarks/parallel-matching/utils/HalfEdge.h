//
// Created by sualehasif on 5/16/21.
//

#ifndef MAXIMUM_MATCHING_HALFEDGE_H
#define MAXIMUM_MATCHING_HALFEDGE_H

#include "../MVertex.h"

namespace maxmatching::norm {
    /* Basic half edge implementation. Basically a struct, if you will. */
    template <class Label>
    class HalfEdge {
    public:
        MVertex<Label>* start;
        MVertex<Label>* end;
        HalfEdge<Label>* label;
        HalfEdge<Label>* inverse;


        HalfEdge(MVertex<Label>* start, MVertex<Label>* end, HalfEdge<Label>* label);
        ~HalfEdge() = default;
    };

    template <class Label>
    HalfEdge<Label>::HalfEdge(MVertex<Label>* start, MVertex<Label>* end, HalfEdge<Label>* label)
            : start(start)
            , end(end)
            , label(label)
            , inverse(nullptr) {
    }
}

#endif //MAXIMUM_MATCHING_HALFEDGE_H
