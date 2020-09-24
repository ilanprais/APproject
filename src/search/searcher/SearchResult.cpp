#include "SearchResult.hpp"

namespace searcher {

    SearchResult::SearchResult(uint32_t matrixSize, uint32_t numEvaluated, uint32_t cost)
    : m_matrixSize(matrixSize),
    m_numEvaluated(numEvaluated),
    m_cost(cost) {}

    std::string SearchResult::toString() const {
        return std::to_string(m_matrixSize) + "\t" + std::to_string(m_numEvaluated) 
        + "\t" + std::to_string(m_cost);
    }
}