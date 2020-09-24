#pragma once

#include <vector>
#include <string>
#include <utility>
#include <cstdint>

namespace searcher {
typedef std::pair<uint32_t, uint32_t> pair;
    /**
     * @brief This class represents a specific search result of a pathfinding search.
     * 
     */
    class SearchResult {
        
        uint32_t m_matrixSize;
        uint32_t m_numEvaluated;
        uint32_t m_cost;

        public:

            /**
             * @brief Construct a new Search Result object
             * 
             * @param directions the directions vector of the search
             * @param cost the total cost of the search
             * @param algorithmName the name of the algorithm used for the search
             */
            SearchResult(uint32_t matrixSize, uint32_t numEvaluated, uint32_t cost);

            /**
             * @brief Convert the search result to a string
             * 
             * @return std::string a string represents the search result
             */
            std::string toString() const;  
    };
}