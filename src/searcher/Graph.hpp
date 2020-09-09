#pragma once

#include "AbstractSearchable.hpp"
#include "Matrix.hpp"
#include <cstdint>
#include <utility>

namespace searcher {

    typedef std::pair<uint32_t, uint32_t> pair;
    typedef Element<pair> graphElement;

    class Graph : public AbstractSearchable<graphElement> {

        const matrix::Matrix m_graphMatrix;

        public:

            Graph(const matrix::Matrix& graphMatrix, const pair& startLocation, const pair& endLocation);
            
            std::vector<graphElement> getAllReachableElements(const graphElement& current) const override;

            std::string getDirection(const graphElement& origin, const graphElement& destination) const override;
    };
}