#pragma once
#include <queue>
#include <PathFinder.h>
#include <vector>

template <class T, class C, class F>
    C& Container(std::priority_queue<T, C, F> &q) {
        struct HackedQueue : private std::priority_queue<T, C, F> {
            static C& Container(std::priority_queue<T, C, F> &q) {
                return q.*&HackedQueue::c;
            }
        };
        return HackedQueue::Container(q);
    }