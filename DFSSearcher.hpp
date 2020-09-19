#pragma once

#include "AbstractSearcher.hpp"
#include "SearchExceptions.hpp"
#include <stack>
#include <utility>
#include <algorithm>

namespace searcher {

    template <typename Identifier>
    class DFSSearcher : public AbstractSearcher<SearchResult, Identifier> {

        public:

            SearchResult search(const Searchable<Identifier>& searchable) const {
                // this vector will hold the visited elements
                std::vector<Element<Identifier>> visited;
                // this stack will be used for the DFS algorithm
                std::stack<Element<Identifier>> stack;

                // this map will hold for every element in the path, its previous element in the path.
                // the elements will be ordered in the map using the element identifier comparator
                std::map<Element<Identifier>, Element<Identifier>, CompareByIdentifier<Identifier>> cameFrom;

                // adding the start element to the visited elements vector, pushing it to the stack
                visited.push_back(searchable.getStartElement());
                stack.push(searchable.getStartElement());

                while (!stack.empty()) {
                    // popping an element from the stack
                    Element<Identifier> current = stack.top();
                    stack.pop();

                    // in case that the popped element is the end element, then finishing the search
                    if (current == searchable.getEndElement()) {
                        return reconstructPath(searchable, cameFrom);
                    }

                    // else, getting all of the reachable elements of the popped element
                    for (auto& reachable : searchable.getAllReachableElements(current)) {
                        // if the reachable element has not been visited, then adding it to the visited elements vector, 
                        // pushing it to the stack, and getting its previos element in the path
                        if (std::find(visited.begin(), visited.end(), reachable) == visited.end()) {
                            visited.push_back(reachable);
                            stack.push(reachable);
                            cameFrom.emplace(reachable, current);         
                        }
                    }  
                }

                // if the end element has not been visited, then the path does not exist
                if (std::find(visited.begin(), visited.end(), searchable.getEndElement()) == visited.end()) {
                    throw exceptions::PathDoesNotExistException();
                }
            }
    };
}
