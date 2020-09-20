#pragma once

#include "AbstractSearcher.hpp"
#include <queue>

namespace searcher {

    template <typename Identifier>
    class AStarSearcher : public AbstractSearcher<Identifier> {

        // the proirity queue which will be used for the A* algorithm.
        // the best element in the priority queue will be the element which its F Score is the best.
        // so, the elements in the priority queue will be ordered using the element F Score comparator
        std::priority_queue<Element<Identifier>, std::vector<Element<Identifier>>, CompareByFScore<Identifier>> pqueue;

        protected:

            void pushToContainer(const Element<Identifier>& element) override {
                pqueue.push(element);
            }

            const Element<Identifier>& popFromContainer() override {
                const Element<Identifier> popped = pqueue.top();
                pqueue.pop();
                return popped;
            }

            bool isContainerEmpty() const override {
                return pqueue.empty();
            }

            void clearContainer() {
                while(!pqueue.empty()) {
                    pqueue.pop();
                }
            }

            void std::string getAlgorithmName() const {
                return "A*";
            }
    };
}