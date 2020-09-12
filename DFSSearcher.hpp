#pragma once

#include "Searcher.hpp"
#include "SearchResult.hpp"
#include <algorithm>
#include <limits>

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

                double optimalCost = std::numeric_limits<uint32_t>::max();
                ElementType *optimalNode = nullptr;

                for (auto reachable : searchable.getAllReachableElements(current)) {
                    if (std::find(visited.begin(), visited.end(), reachable) == visited.end()) {
                        if (double currentPrice = recursiveSearch(searchable, visited, directions, reachable) < optimalCost) {
                            optimalCost = currentPrice;
                            optimalNode = &reachable;
                        }
                    }
                }

                if (optimalNode == nullptr) {
                    return std::numeric_limits<uint32_t>::max();
                }

                directions.push_back(searchable.getDirection(current, *optimalNode));

                return current.getValue() + optimalCost;
            }
    };
}