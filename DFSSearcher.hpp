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

                // this vector will hold the directions of the optimal path from the start element to the end element
                std::vector<std::string> directions;
                
                // getting the optimal cost of the way from the start element to the end element
                double value = recursiveSearch(searchable, visited, directions, searchable.getStartElement());

                return SearchResult(directions, value, "DFS");
            }

        private:

            double recursiveSearch(const Searchable<Element<Identifier>>& searchable, std::vector<Element<Identifier>>& visited,
                std::vector<std::string>& directions, const Element<Identifier>& current) const {
            
                if (current == searchable.getEndElement()) {
                    return searchable.getEndElement().getValue();
                }

                visited.push_back(current);

                double recursiveCost = std::numeric_limits<uint32_t>::max();
                Element<Identifier>* recursiveElement = nullptr;

                for (auto reachable : searchable.getAllReachableElements(current)) {
                    if (std::find(visited.begin(), visited.end(), reachable) == visited.end()) {
                        double tempCost = recursiveSearch(searchable, visited, directions, reachable);
                        if (tempCost != std::numeric_limits<uint32_t>::max()) {
                            recursiveCost = tempCost;
                            recursiveElement = &reachable;
                            break;
                        }
                    }
                }

                if (recursiveCost == std::numeric_limits<uint32_t>::max()) {
                    return recursiveCost;
                }

                directions.insert(directions.begin(), searchable.getDirection(current, *recursiveElement));

                return current.getValue() + recursiveCost;
            }
    };
}