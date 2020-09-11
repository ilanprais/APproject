#pragma once

namespace searcher {

    template <typename IdentifierType>
    class Element {

        const IdentifierType m_identifier;
        const double m_value;

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
    };
}