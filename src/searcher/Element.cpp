#include "Element.hpp"

namespace searcher {

    template <typename IdentifierType>
    Element<IdentifierType>::Element(const IdentifierType& identifier, const double value)
    : m_identifier(identifier),
    m_value(value) {}

    template <typename IdentifierType>
    const IdentifierType& Element<IdentifierType>::getIdentifier() const {
        return m_identifier;
    }

    template <typename IdentifierType>
    double Element<IdentifierType>::getValue() const {
        return m_value;
    }
}