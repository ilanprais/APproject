#pragma once

#include <utility>
#include <cstdint>

namespace searcher {

    typedef std::pair<uint32_t, uint32_t> pair;

    class Element {

        const pair m_location;
        const double m_value;

        public:

            Element(const pair& location, const double value)
            : m_location(location),
            m_value(value) {}

            const pair& getLocation() const {
                return m_location;
            }

            double getValue() const {
                return m_value;
            }

            bool operator==(const Element& other) const {
                return m_location == other.m_location && m_value == other.m_value;
            }

            bool operator!=(const Element& other) const {
                return !(*this == other);
            }
    };
}