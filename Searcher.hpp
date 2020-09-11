#pragma once

#include "Searchable.hpp"

namespace searcher {

    class Searcher {

        public:
        
            template <typename ResultType, typename ElementType>
            ResultType search(const Searchable<ElementType>& searchable) const;
    };
}