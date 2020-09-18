#pragma once

#include "Searcher.hpp"
#include "SearchResult.hpp"
#include <queue>
#include <map>
#include <utility>
#include <algorithm>
#include <iostream>

namespace searcher {

    template <typename Identifier>
    class BFSSearcher : public Searcher<SearchResult, Identifier> {

        public:

            SearchResult search(const Searchable<Identifier>& searchable) const {
                // this vector will hold the visited elements
                std::vector<Element<Identifier>> visited;
                // this queue will be used for the BFS algorithm
                std::queue<Element<Identifier>> queue;
                // this map will hold for every element in the path, its previous element in the path
                std::map<Element<Identifier>, Element<Identifier>> pathsInfo;

                // this vector will hold the directions of the path from the start element to the end element
                std::vector<std::string> directions;

                // adding the start element to the visited elements vector, enqueuing it, and adding it to the optimal paths map
                visited.push_back(searchable.getStartElement());
                queue.push(searchable.getStartElement());

                while (!queue.empty()) {
                    // dequeuing an element
                    const auto current = queue.front();
                    queue.pop();

                    // in case that the dequeued element is the end element, then finishing the search
                    if (current == searchable.getEndElement()) {
                        // this variable will hold the total cost of the path. 
                        // first, initializing it just with the cost of the start element
                        auto pathCost = searchable.getStartElement().getValue();

                        // iterating over the elements, and initializing the directions vector according to the path
                        Element<Identifier> *temp = &current;
                        while (*temp != searchable.getStartElement()) {
                            // adding the cost of the current element to the total cost of the path
                            pathCost += temp->getValue();
                            // adding a direction between two elements in the path 
                            directions.push_back(searchable.getDirection(pathsInfo.at(*temp), *temp));
                            // moving to the previous element
                            temp = &pathsInfo.at(*temp);
                        }
                        
                        return SearchResult(directions, pathCost, "BFS");
                    }

                    // getting all of the reachable elements of the dequeued element
                    for (auto& reachable : searchable.getAllReachableElements(current)) {
                        // if the reachable element has not been visited, then adding it to the visited elements vector, 
                        // enqueuing it to the queue, and getting its previos element in the path
                        if (std::find(visited.begin(), visited.end(), reachable) == visited.end()) {
                            visited.push_back(reachable);
                            queue.push(reachable);
                            pathsInfo.emplace(reachable, current);         
                        }
                    }  
                }
            }
    };
}
