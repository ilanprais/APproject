#pragma once

#include "Searcher.hpp"
#include "SearchResult.hpp"
#include <algorithm>
#include <limits>

namespace searcher {

    template <typename Identifier>
    class DFSSearcher : public Searcher<SearchResult, Identifier> {

        public:

            SearchResult search(const Searchable<Identifier>& searchable) const {
                // this vector will hold the visited elements
                std::vector<Element<Identifier>> visited;

                // this vector will hold the directions of the path from the start element to the end element
                std::vector<std::string> directions;
                
                // getting the optimal cost of the way from the start element to the end element
                const auto value = recursiveSearch(searchable, visited, directions, searchable.getStartElement());

                // if the end element has not been visited, then the path does not exist
                if (std::find(visited.begin(), visited.end(), searchable.getEndElement()) == visited.end()) {
                    throw exceptions::PathDoesNotExistException();
                }

                return SearchResult(directions, value, "DFS");
            }

        private:

            double recursiveSearch(const Searchable<Identifier>& searchable, std::vector<Element<Identifier>>& visited,
                std::vector<std::string>& directions, const Element<Identifier>& current) const {
            
                // if the current element is the end element, stopping the recursive search
                if (current == searchable.getEndElement()) {
                    return searchable.getEndElement().getValue();
                }

                // adding the current element to the visited elements vector, to mark it as visited
                visited.push_back(current);

                // this variable will point to a reachable element of the current element, which has a path
                // from the start element to it 
                Element<Identifier> *reachableElement = nullptr;
                // this variable will hold the cost of the path from the start element to reachableElement
                double reachableElementPathCost = std::numeric_limits<double>::max();

                // for every element from the reachable elements of the current element, checking if there is a path
                // from the start element to this element
                for (auto& reachable : searchable.getAllReachableElements(current)) {
                    if (std::find(visited.begin(), visited.end(), reachable) == visited.end()) {
                        // getting the cost of the path from the start element to this reachable element
                        const auto temp = recursiveSearch(searchable, visited, directions, reachable);
                        // if the path actually exists (the path cost isn't infinity), breaking the loop
                        if (temp != std::numeric_limits<uint32_t>::max()) {
                            reachableElement = &reachable;
                            reachableElementPathCost = temp;
                            break;
                        }
                    }
                }

                // if there isn't a path from the start element to a reachable element of the current element,
                // so returning infinity
                if (reachableElementPathCost == std::numeric_limits<double>::max()) {
                    return reachableElementPathCost;
                }

                // adding the direction from the current element to the reachable element to the directions vector
                directions.insert(directions.begin(), searchable.getDirection(current, *reachableElement));

                return current.getValue() + reachableElementPathCost;
            }
    };
}