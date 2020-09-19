#pragma once

#include "AbstractSearcher.hpp"
#include "SearchExceptions.hpp"
#include <queue>
#include <utility>
#include <algorithm>

namespace searcher {

    template <typename Identifier>
    class BFSSearcher : public AbstractSearcher<Identifier> {

        public:

            SearchResult search(const Searchable<Identifier>& searchable) const {
                // this vector will hold the visited elements
                std::vector<Element<Identifier>> visited;
                // this queue will be used for the BFS algorithm
                std::queue<Element<Identifier>> queue;

                // this map will hold for every element in the path, its previous element in the path.
                // the elements will be ordered in the map using the element identifier comparator
                std::map<Element<Identifier>, Element<Identifier>, CompareByIdentifier<Identifier>> cameFrom;

                // adding the start element to the visited elements vector, enqueuing it
                visited.push_back(searchable.getStartElement());
                queue.push(searchable.getStartElement());

                while (!queue.empty()) {
                    // dequeuing an element from the queue
                    Element<Identifier> current = queue.front();
                    queue.pop();

                    // in case that the dequeued element is the end element, then finishing the search
                    if (current == searchable.getEndElement()) {
                        return reconstructPath(searchable, cameFrom);
                    }

                    // else, getting all of the reachable elements of the dequeued element
                    for (auto& reachable : searchable.getAllReachableElements(current)) {
                        // if the reachable element has not been visited, then adding it to the visited elements vector, 
                        // enqueuing it to the queue, and getting its previos element in the path
                        if (std::find(visited.begin(), visited.end(), reachable) == visited.end()) {
                            visited.push_back(reachable);
                            queue.push(reachable);
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