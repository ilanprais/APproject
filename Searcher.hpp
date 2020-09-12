#pragma once

#include "Searchable.hpp"

namespace searcher {

    template <typename SearchResultType, typename ElementType>
    class Searcher {

        public:
        
            virtual SearchResultType search(const Searchable<ElementType>& searchable) const = 0;
    };
}