#pragma once

#include "Searcher.hpp"
#include "SearchResult.hpp"
#include <queue>
#include <unordered_map>
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
                // this map will hold for each element pair with the cost of the optimal path from the start element to the element
                // and the previous element in this path

                std::unordered_map<ElementType, ElementType> optimalPathsPrevElements;
                std::unordered_map<ElementType, double> optimalPathsCosts;

                // this vector will hold the directions of the optimal way from the start element to the end element
                std::vector<std::string> directions;
                // the cost of the optimal path
                double optimalCost = 0;

                // adding the start element to the visited elements vector and enqueuing it
                visited.push_back(searchable.getStartElement());
                queue.push(searchable.getStartElement());

                while (!queue.empty()) {
                    // dequeuing an element
                    ElementType current = queue.front();
                    queue.pop();

                    // in case that the dequeued element is the end element, then finishing the search
                    if (current == searchable.getEndElement()) {
                        // getting the optimal cost of the path, according the optimal paths that were calculated before
                        optimalCost = optimalPathsCosts.at(current);

                        // iterating over the elements, and initializing the directions vector according to the optimal path
                        ElementType *temp = &current;
                        while (*temp != searchable.getStartElement()) {
                            // adding a direction between two elements in the optimal path 
                            directions.insert(directions.begin(), searchable.getDirection(optimalPathsPrevElements.at(*temp), *temp));
                            // moving to the previous element
                            *temp = optimalPathsPrevElements.at(*temp);
                        }
                    }

                    // getting all of the reachable elements of the dequeued element
                    for (auto reachable : searchable.getAllReachableElements(current)) {
                        // if the reachable element has not been visited, then adding it to the visited elements vector, 
                        // enqueuing it to the queue, and initializing its optimal path
                        if (std::find(visited.begin(), visited.end(), reachable) == visited.end()) {
                            visited.push_back(reachable);
                            queue.push(reachable);
                            optimalPathsPrevElements.emplace(reachable, current);
                            optimalPathsCosts.emplace(reachable, reachable.getValue() + optimalPathsCosts.at(current));
                        }
                        // if the reachable element has been visited already, then checking if the path to this reachable element
                        // from the current element is more optimal than the current optimal path to the reachable, and if it is,
                        // then updating it accordingly 
                        else if (reachable.getValue() + optimalPathsCosts.at(current) < optimalPathsCosts.at(reachable)) {
                            optimalPathsPrevElements.emplace(reachable, current);
                            optimalPathsCosts.emplace(reachable, reachable.getValue() + optimalPathsCosts.at(current));
                        }
                    }  
                }

                return SearchResult(directions, optimalCost, "BFS");
            }
    };
}