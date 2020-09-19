#pragma once

#include "Searcher.hpp"
#include "SearchResult.hpp"
#include "SearchExceptions.hpp"
#include <stack>
#include <map>
#include <utility>
#include <algorithm>

namespace searcher {

    template <typename Identifier>
    class DFSSearcher : public Searcher<SearchResult, Identifier> {

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
                    // popping an element
                    Element<Identifier> current = stack.top();
                    stack.pop();

                    // in case that the popped element is the end element, then finishing the search
                    if (current == searchable.getEndElement()) {
                        return reconstructPath(searchable, cameFrom);
                    }

                    // getting all of the reachable elements of the popped element
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

        private:

            SearchResult reconstructPath(const Searchable<Identifier>& searchable, 
                std::map<Element<Identifier>, Element<Identifier>, CompareByIdentifier<Identifier>>& cameFrom) const {
                    // this vector will hold the directions of the path from the start element to the end element
                    std::vector<std::string> directions;

                    // this variable will hold the total cost of the path. 
                    // first, initializing it just with the cost of the start element
                    auto pathCost = searchable.getStartElement().getValue();

                    // iterating over the elements, and initializing the directions vector according to the path
                    const auto *temp = &searchable.getEndElement();
                    while (*temp != searchable.getStartElement()) {
                        // adding the cost of the current element to the total cost of the path
                        pathCost += temp->getValue();
                        // adding a direction between two elements in the path 
                        directions.insert(directions.begin(), searchable.getDirection(cameFrom.at(*temp), *temp));
                        // moving to the previous element
                        temp = &cameFrom.at(*temp);
                    }

                    return SearchResult(directions, pathCost, "DFS");
            }
    };
}
