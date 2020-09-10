#include "BFSSearcher.hpp"
#include <queue>
#include <map>
#include <utility>
#include <memory>

namespace searcher {

    template <typename ElementType>
    SearchResult BFSSearcher::search(const Searchable<ElementType>& searchable) const {
        // this vector will hold the visited elements
        std::vector<ElementType> visited;
        // this queue will be used for the BFS algorithm
        std::queue<ElementType> queue;
        // this map will hold for each element pair with the cost of the optimal path from the start element to the element
        // and the previous element in this path
        std::map<ElementType, std::pair<double, ElementType>> optimalPathInfo;

        // this vector will hold the directions of the optimal way from the start element to the end element
        std::vector<std::string> directions;
        // the cost of the optimal path
        double optimalCost = 0;

        // adding the start element to the visited elements vector and enqueuing it
        visited.push_back(searchable.getStartElement());
        queue.push_back(searchable.getStartElement());

        while (!queue.empty()) {
            // dequeuing an element
            auto current = queue.pop();

            if (current == searchable.getEndElement()) {

                optimalCost = optimalPathInfo[current].first;

                ElementType *temp = &current;

                while (*temp != searchable.getStartElement()) {

                    directions.insert(directions.begin(), searchable.getDirection(optimalPathInfo[*temp].second, *temp));

                    temp = &optimalPathInfo[*temp].second;
                }

                return SearchResult(directions, optimalCost, "BFS");
            }

            // getting all of the reachable elements of the dequeued element
            // if one of them has not been visited, then adding it to the visited elements vector and enqueuing it
            for (auto reachable : searchable.getAllReachableElements(current)) {
                if (std::find(visited.begin(), visited.end(), reachable) == visited.end()) {

                    optimalPathInfo[reachable] = std::pair(reachable.getValue() + optimalPathInfo[current].first, current);

                    queue.push(reachable);
                }
                else if (reachable.getValue() + optimalPathInfo[current].first < optimalPathInfo[std::find(visited.begin(), visited.end(), reachable)].first) {
                        optimalPathInfo[reachable] = std::pair(reachable.getValue() + optimalPathInfo[current].first, current);
                }
            }  

        }
    }
}

