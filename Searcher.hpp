#pragma once

#include "Searchable.hpp"

namespace searcher {

    template <typename SearchResultType, typename Identifier>
    class Searcher {

        public:
        
            virtual SearchResultType search(const Searchable<Element<Identifier>>& searchable) const = 0;
    };
}