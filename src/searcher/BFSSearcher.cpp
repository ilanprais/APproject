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
        // this vector will hold the directions of the optimal way from the start element to the end element
        std::vector<std::string> directions;

        // the cost of the optimal path
        double optimalCost = 0;

        // this queue will be used for the BFS algorithm
        std::queue<ElementType> queue;

        std::map<ElementType, std::pair<double, ElementType>> nodes;

        // adding the start element to the visited elements vector and enqueuing it
        visited.push_back(searchable.getStartElement());
        queue.push_back(searchable.getStartElement());

        while (!queue.empty()) {
            // dequeuing an element
            auto current = queue.pop();

            if(current == searchable.getEndElement()){

                optimalCost = nodes[current].first;

                ElementType temp = current;

                while(*temp != searchable.getStartElement()){

                    directions.insert(directions.begin(), searchable.getDirection(nodes[temp].second, temp));

                    temp = nodes[temp].second;
                }
            }

            // getting all of the reachable elements of the dequeued element
            // if one of them has not been visited, then adding it to the visited elements vector and enqueuing it
            for (auto reachable : searchable.getAllReachableElements(current)) {
                if (std::find(visited.begin(), visited.end(), reachable) == visited.end()) {

                    nodes[reachable] = std::pair(reachable.getValue() + nodes[current].first, current);

                    queue.push(reachable);
                }
                else{
                    if(reachable.getValue() + nodes[current].first < nodes[std::find(visited.begin(), visited.end(), reachable)].first){
                        nodes[reachable] = std::pair(reachable.getValue() + nodes[current].first, current);
                    }
                }
            }  

        }
    }
}

