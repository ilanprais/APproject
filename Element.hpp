#pragma once

#include <vector>

namespace searcher {

    template <typename IdentifierType>
    class Element {

        const IdentifierType m_identifier;
        const double m_value;

        public:

            Element(const IdentifierType& identifier, const double value);

            const IdentifierType& getIdentifier() const;

            double getValue() const;
    };
}