#include "Element.hpp"
#include <cstdint>
#include <utility>
#include <cmath>

namespace searcher {

    typedef std::pair<uint32_t, uint32_t> pair;

    template<>
    void Element<pair>::calculateHeuristics(const Element<pair>& startPos, const const Element<pair>& endPos) {
                m_gScore = getValue();
                m_hScore = abs(getIdentifier().first - endPos.getIdentifier().first)
                    + abs(getIdentifier().second - endPos.getIdentifier().second);
            }
}