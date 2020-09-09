#include "BFSSearcher.hpp"
#include <queue>

namespace searcher {

    template <typename ElementType>
    SearchResult BFSSearcher::search(const Searchable<ElementType>& searchable) const {
        // this vector will hold the visited elements
        std::vector<ElementType> visited;
        // this vector will hold the directions of the optimal way from the start element to the end element
        std::vector<std::string> directions;

        // this queue will be used for the BFS algorithm
        std::queue<ElementType> queue;

        // adding the start element to the visited elements vector and enqueuing it
        visited.push_back(searchable.getStartElement());
        queue.push_back(searchable.getStartElement());

        while (!queue.empty()) {
            // dequeuing an element
            auto dequeued = queue.pop();

            // getting all of the reachable elements of the dequeued element
            // if one of them has not been visited, then adding it to the visited elements vector and enqueuing it
            for (auto reachable : searchable.getAllReachableElements(dequeued)) {
                if (std::find(visited.begin(), visited.end(), reachable) == visited.end()) {

                }
            }  
        }
    }
}

