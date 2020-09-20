#include "Element.hpp"
#include <cstdint>
#include <utility>
#include <cmath>

namespace searcher {

    typedef std::pair<uint32_t, uint32_t> pair;

    template<>
    bool CompareByFScore<pair>::operator()(const Element<pair>& e1, const Element<pair>& e2) const {
        double F1 = abs(e1.getIdentifier().first - m_goal.getIdentifier().first)
            + abs(e1.getIdentifier().second - m_goal.getIdentifier().second);
        double F2 = abs(e2.getIdentifier().first - m_goal.getIdentifier().first)
            + abs(e2.getIdentifier().second - m_goal.getIdentifier().second);
        return F1 > F2;
    }
}