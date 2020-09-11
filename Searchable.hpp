#pragma once

#include "Element.hpp"
#include <vector>
#include <string>

namespace searcher {
    
    template <typename ElementType>
    class Searchable {

        public:

            virtual const ElementType& getStartElement() const = 0;

            virtual const ElementType& getEndElement() const = 0;

            virtual std::vector<ElementType> getAllReachableElements(const ElementType& current) const = 0;

            virtual std::string getDirection(const ElementType& origin, const ElementType& destination) const = 0;
    };
}