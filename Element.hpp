#pragma once

#include <utility>
#include <cstdint>

namespace searcher {

    template <typename Identifier>
    class Element {

        const Identifier m_identifier;
        const double m_value;

        public:

            Element(const Identifier& identifier, const double value)
            : m_identifier(identifier),
            m_value(value) {}

            const Identifier& getIdentifier() const {
                return m_identifier;
            }

            double getValue() const {
                return m_value;
            }

            bool operator==(const Element& other) const {
                return m_identifier == other.m_identifier && m_value == other.m_value;
            }

            bool operator!=(const Element& other) const {
                return !(*this == other);
            }

            bool operator<(const Element& other) const {
                return m_value < other.m_value;
            }
    };
}