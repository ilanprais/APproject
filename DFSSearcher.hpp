#pragma once

#include "Searcher.hpp"
#include "SearchResult.hpp"
#include <algorithm>
#include <limits>
#include <iostream>

namespace searcher {

    template <typename ElementType>
    class DFSSearcher : public Searcher<SearchResult, ElementType> {

        public:

            SearchResult search(const Searchable<ElementType>& searchable) const {
                // this vector will hold the visited elements
                std::vector<ElementType> visited;

                // this vector will hold the directions of the optimal path from the start element to the end element
                std::vector<std::string> directions;
                
                // getting the optimal cost of the way from the start element to the end element
                double value = recursiveSearch(searchable, visited, directions, searchable.getStartElement());

                return SearchResult(directions, value, "DFS");
            }

        private:

            double recursiveSearch(const Searchable<ElementType>& searchable, std::vector<ElementType>& visited,
                std::vector<std::string>& directions, const ElementType& current) const {
            
                if (current == searchable.getEndElement()) {
                    return searchable.getEndElement().getValue();
                }

                visited.push_back(current);

                double recursiveCost = std::numeric_limits<uint32_t>::max();
                ElementType *recursiveNode = nullptr;

                for (auto reachable : searchable.getAllReachableElements(current)) {
                    if (std::find(visited.begin(), visited.end(), reachable) == visited.end()) {
                        double tempCost = recursiveSearch(searchable, visited, directions, reachable);
                        if (tempCost != std::numeric_limits<uint32_t>::max()) {
                            recursiveCost = tempCost;
                            recursiveNode = &reachable;
                            std::cout << recursiveCost << std::endl;
                            break;
                        }
                    }
                }

                if (recursiveNode == nullptr) {
                    return std::numeric_limits<uint32_t>::max();
                }

                directions.insert(directions.begin(), searchable.getDirection(current, *recursiveNode));

                return recursiveCost + current.getValue();
            }
    };
}