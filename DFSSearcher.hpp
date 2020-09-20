#pragma once

#include "AbstractSearcher.hpp"
#include <stack>

namespace searcher {

    template <typename Identifier>
    class DFSSearcher : public AbstractSearcher<Identifier> {

        // the stack which will be used for the DFS algorithm
        std::stack<Element<Identifier>> stack;

        protected:

            void pushToContainer(const Element<Identifier>& element) override {
                stack.push(element);
            }

            const Element<Identifier>& popFromContainer() override {
                const Element<Identifier> popped = stack.top();
                stack.pop();
                return popped;
            }

            bool isContainerEmpty() const override {
                return stack.empty();
            }

            void clearContainer() {
                while(!stack.empty()) {
                    stack.pop();
                }
            }

            void std::string getAlgorithmName() const {
                return "DFS";
            }        
    };
}
