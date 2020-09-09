#include "DFSSearcher.hpp"
#include <algorithm>
#include <memory>
#include <limits>


namespace searcher{
    
    template <typename ElementType>
    SearchSolution DFSSearcher::search(const Searchable<ElementType>& searchable) const{
        std::vector<ElementType> visited;
        std::vector<std::string> directions;
        uint32_t value = recursiveSearch(visited, directions, searchable, searchable.getStartElement());

        SearchSolution solution(directions, value);

        return solution;
    }

    template <typename ElementType>
     uint32_t DFSSearcher::recursiveSearch(std::vector<ElementType>& visited, std::vector<std::string>& directions, const Searchable<ElementType>& searchable, const ElementType& cur){
       
         if(cur == searchable.getEndElement()){
             return searchable.getEndElement().getValue();
         }
         
         visited.push_back(cur);

         uint32_t optimalPrice = std::numeric_limits<uint32_t>::max();
         std::unique_ptr<ElementType> optimalNode = nullptr;

         for(auto next : searchable.getAllReachableElements(elm)){
            if(std::find(visited.begin(), visited.end(), elm) == visited.end()){
                if(uint32_t curPrice = recursiveSearch(visited, directions, searchable, next) < optimalPrice){
                    optimalPrice = curPrice;
                    optimalNode = std::make_unique<ElementType>(next);
                }
            }
         }

         if(optimalNode = nullptr){
             return std::numeric_limits<uint32_t>::max();
         }

         directions.push_back(searchable.getDirection(cur, *optimalNode));

         return cur.getValue() + optimalPrice;

     }

}