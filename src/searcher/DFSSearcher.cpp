#include "DFSSearcher.hpp"
#include <algorithm>
#include <memory>
#include <limits>


namespace searcher {
    
    template <typename ElementType>
    SearchResult DFSSearcher::search(const Searchable<ElementType>& searchable) const {
        std::vector<ElementType> visited;
        std::vector<std::string> directions;
        double value = recursiveSearch(searchable, visited, directions, searchable.getStartElement());

        SearchResult result(directions, value, "DFS");

        return result;
    }

    template <typename ElementType>
    double DFSSearcher::recursiveSearch(const Searchable<ElementType>& searchable, std::vector<ElementType>& visited,
        std::vector<std::string>& directions, const ElementType& current){
    
        if (current == searchable.getEndElement()) {
            return searchable.getEndElement().getValue();
        }

        visited.push_back(current);

        double optimalPrice = std::numeric_limits<uint32_t>::max();
        std::unique_ptr<ElementType> optimalNode = nullptr;

        for (auto next : searchable.getAllReachableElements(current)) {
            if (std::find(visited.begin(), visited.end(), current) == visited.end()) {
                if (double currentPrice = recursiveSearch(searchable, visited, directions, next) < optimalPrice) {
                    optimalPrice = currentPrice;
                    optimalNode = std::make_unique<ElementType>(next);
                }
            }
        }

        if (optimalNode = nullptr) {
            return std::numeric_limits<uint32_t>::max();
        }

        directions.push_back(searchable.getDirection(current, *optimalNode);

        return cur.getValue() + optimalPrice;
    }
}