#pragma once

#include "Searchable.hpp"

namespace searcher {
    
    template <typename ElementType>
    class AbstractSearchable : public Searchable<ElementType> {

        const ElementType m_startElement;
        const ElementType m_endElement;

        public:
        
            AbstractSearchable(const ElementType& startElement,
                const ElementType& endElement)
            : m_startElement(startElement),
            m_endElement(endElement) {}

            const ElementType& getStartElement() const {
                return m_startElement;
            }

            const ElementType& getEndElement() const {
                return m_endElement;
            }

            virtual std::vector<ElementType> getAllReachableElements(const ElementType& current) const = 0;

            virtual std::string getDirection(const ElementType& origin, const ElementType& destination) const = 0;
    };
}