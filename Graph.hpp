#pragma once

#include "AbstractSearchable.hpp"
#include "Element.hpp"
#include "Matrix.hpp"
#include <cstdint>
#include <utility>

namespace searcher {

    class Graph : public AbstractSearchable<Element> {

        const matrix::Matrix m_graphMatrix;

        public:

            Graph(const matrix::Matrix& graphMatrix, const pair& startLocation, const pair& endLocation);
            
            std::vector<Element> getAllReachableElements(const Element& current) const override;

            std::string getDirection(const Element& origin, const Element& destination) const override;
    };
}