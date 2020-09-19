#pragma once

#include "AbstractSearcher.hpp"
#include "SearchExceptions.hpp"
#include <queue>
#include <algorithm>

namespace searcher {

    template <typename Identifier>
    class BFSSearcher : public AbstractSearcher<Identifier> {

        public:

            SearchResult search(const Searchable<Identifier>& searchable) const override {
                // this vector will hold the visited elements
                std::vector<Element<Identifier>> visited;
                // this proirity queue will be used for the BestFS algorithm.
                // the best element in this priority queue will be the element which its F Score is the best.
                // so, the elements in the priority queue will be ordered using the element F Score comparator
                std::priority_queue<Element<Identifier>, std::vector<Element<Identifier>>, CompareByFScore<Identifier>> pqueue;

                // this map will hold for every element in the path, its previous element in the path.
                // the elements will be ordered in the map using the element Identifier comparator
                std::map<Element<Identifier>, Element<Identifier>, CompareByIdentifier<Identifier>> cameFrom;

                // adding the start element to the visited elements vector, enqueuing it
                visited.push_back(searchable.getStartElement());
                pqueue.push(searchable.getStartElement());

                while (!pqueue.empty()) {
                    // dequeuing an element from the queue
                    Element<Identifier> current = pqueue.top();
                    pqueue.pop();

                    // in case that the dequeued element is the end element, then finishing the search
                    if (current == searchable.getEndElement()) {
                        return this->reconstructPath(searchable, cameFrom);
                    }

                    // else, getting all of the reachable elements of the dequeued element
                    for (auto& reachable : searchable.getAllReachableElements(current)) {
                        // if the reachable element has not been visited, then adding it to the visited elements vector, 
                        // enqueuing it to the queue, and getting its previos element in the path
                        if (std::find(visited.begin(), visited.end(), reachable) == visited.end()) {
                            visited.push_back(reachable);
                            pqueue.push(reachable);
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