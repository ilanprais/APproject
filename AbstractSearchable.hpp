#pragma once

#include "Searchable.hpp"

namespace searcher {
    
    template <typename Identifier>
    class AbstractSearchable : public Searchable<Identifier> {

        const Element<Identifier> m_startElement;
        const Element<Identifier> m_endElement;

        public:
        
            AbstractSearchable(const Element<Identifier>& startElement, const Element<Identifier>& endElement)
            : m_startElement(startElement),
            m_endElement(endElement) {}

            const Element<Identifier>& getStartElement() const {
                return m_startElement;
            }

            const Element<Identifier>& getEndElement() const {
                return m_endElement;
            }

            virtual std::vector<Element<Identifier>> getAllReachableElements(const Element<Identifier>& current) const = 0;

            virtual std::string getDirection(const Element<Identifier>& origin, const Element<Identifier>& destination) const = 0;
    };
}