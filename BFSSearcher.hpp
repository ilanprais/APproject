#pragma once

#include "Searcher.hpp"
#include "SearchResult.hpp"
#include <queue>
#include <map>
#include <utility>
#include <algorithm>

namespace searcher {

    template <typename ElementType>
    class BFSSearcher : public Searcher<SearchResult, ElementType> {

        public:

            SearchResult search(const Searchable<ElementType>& searchable) const {
                // this vector will hold the visited elements
                std::vector<ElementType> visited;
                // this queue will be used for the BFS algorithm
                std::queue<ElementType> queue;
                // this map will hold for each element pair with the cost of the element and the previous element in this path
                std::map<ElementType, std::pair<double, ElementType>> pathsInfo;

                // this vector will hold the directions of the optimal way from the start element to the end element
                std::vector<std::string> directions;

                // adding the start element to the visited elements vector, enqueuing it, and adding it to the optimal paths map
                visited.push_back(searchable.getStartElement());
                queue.push(searchable.getStartElement());
                optimalPathsInfo.emplace(searchable.getStartElement(), std::make_pair(searchable.getStartElement().getValue(), searchable.getStartElement()));

                while (!queue.empty()) {
                    // dequeuing an element
                    ElementType current = queue.front();
                    queue.pop();

                    // in case that the dequeued element is the end element, then finishing the search
                    if (current == searchable.getEndElement()) {
                        // getting the optimal cost of the path, according the optimal paths that were calculated before
                        double cost = 0;

                        // iterating over the elements, and initializing the directions vector according to the optimal path
                        ElementType *temp = &current;
                        while (*temp != searchable.getStartElement()) {
                            cost += optimalPathsInfo.at(*temp).first;
                            // adding a direction between two elements in the optimal path 
                            directions.insert(directions.begin(), searchable.getDirection(optimalPathsInfo.at(*temp).second, *temp));
                            // moving to the previous element
                            temp = &optimalPathsInfo.at(*temp).second;
                        }

                        return SearchResult(directions, optimalCost, "BFS");
                    }

                    // getting all of the reachable elements of the dequeued element
                    for (auto reachable : searchable.getAllReachableElements(current)) {
                        // if the reachable element has not been visited, then adding it to the visited elements vector, 
                        // enqueuing it to the queue, and initializing its optimal path
                        if (std::find(visited.begin(), visited.end(), reachable) == visited.end()) {
                            visited.push_back(reachable);
                            queue.push(reachable);
                            pathsInfo.emplace(reachable, std::make_pair(reachable.getValue(), current));
                        }
                    }  
                }
            }
    };
}