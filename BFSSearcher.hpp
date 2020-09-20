#pragma once

#include "AbstractSearcher.hpp"
#include <queue>

namespace searcher {

    template <typename Identifier>
    class BFSSearcher : public AbstractSearcher<Identifier> {

        // the queue which will be used for the BFS algorithm
        std::queue<Element<Identifier>> queue;

        protected:

            void pushToContainer(const Element<Identifier>& element) override {
                queue.push(element);
            }

            const Element<Identifier>& popFromContainer() override {
                const Element<Identifier> popped = queue.front();
                queue.pop();
                return popped;
            }

            bool isContainerEmpty() const override {
                return queue.empty();
            }

            void clearContainer() {
                while(!queue.empty()) {
                    queue.pop();
                }
            }

            void std::string getAlgorithmName() const {
                return "BFS";
            }
    };
}