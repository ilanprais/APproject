#pragma once

#include "Searcher.hpp"
#include "SearchResult.hpp"
#include <map>

namespace searcher {

    template <typename Identifier>
    class AbstractSearcher : public Searcher<SearchResult, Identifier> {

        public:

            virtual SearchResult search(const Searchable<Identifier>& searchable) const = 0;

        protected:

            virtual SearchResult reconstructPath(const Searchable<Identifier>& searchable, 
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

                return SearchResult(directions, pathCost, "BFS");
            }
    };
}