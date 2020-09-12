#pragma once

#include <utility>
#include <cstdint>

namespace searcher {

    template <typename IdentifierType>
    class Element {

        IdentifierType m_identifier;
        double m_value;

        public:

            Element(const IdentifierType& identifier, const double value)
            : m_identifier(identifier),
            m_value(value) {}

            const IdentifierType& getIdentifier() const {
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