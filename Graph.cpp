#include "Graph.hpp"

namespace searcher {

    Graph::Graph(const matrix::Matrix& graphMatrix, const pair& startLocation, const pair& endLocation)
    : AbstractSearchable(Element(startLocation, graphMatrix(startLocation.first, startLocation.second)), 
    Element(endLocation, graphMatrix(endLocation.first, endLocation.second))), 
    m_graphMatrix(graphMatrix) {}

    std::vector<Element> Graph::getAllReachableElements(const Element& current) const {
        // this vector will contain the elements which can be reached from the current element
        std::vector<Element> reachables;

        // getting the exact location of the current element
        uint32_t rowIdx = current.getLocation().first;
        uint32_t colIdx = current.getLocation().second;

        // adding the element above the current element, if exists
        if (rowIdx > 0) {
            reachables.push_back(Element(pair(rowIdx - 1, colIdx), m_graphMatrix(rowIdx - 1, colIdx)));
        }

        // adding the element below the current element, if exists
        if (rowIdx < m_graphMatrix.getHeight() - 1) {
            reachables.push_back(Element(pair(rowIdx + 1, colIdx), m_graphMatrix(rowIdx + 1, colIdx)));
        }

        // adding the element in the left of the current element, if exists
        if (colIdx > 0) {
            reachables.push_back(Element(pair(rowIdx, colIdx - 1), m_graphMatrix(rowIdx, colIdx - 1)));
        }

        // adding the element in the right of the current element, if exists
        if (colIdx < m_graphMatrix.getWidth() - 1) {
            reachables.push_back(Element(pair(rowIdx, colIdx + 1), m_graphMatrix(rowIdx, colIdx + 1)));
        }

        return reachables;
    }

    std::string Graph::getDirection(const Element& origin, const Element& destination) const {
        if (origin.getLocation().first == destination.getLocation().first + 1
            && origin.getLocation().second == destination.getLocation().second) {
                return "Left";
        }
        else if (origin.getLocation().first == destination.getLocation().first - 1
            && origin.getLocation().second == destination.getLocation().second) {
                return "Right";
        }
        else if (origin.getLocation().first == destination.getLocation().first
            && origin.getLocation().second == destination.getLocation().second + 1) {
                return "Up";
        }
        else if (origin.getLocation().first == destination.getLocation().first
            && origin.getLocation().second == destination.getLocation().second - 1) {
                return "Down";
        }
        return "";
    }

}