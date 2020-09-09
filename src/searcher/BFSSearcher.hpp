#pragma once

#include "Searcher.hpp"
#include "SearchResult.hpp"

namespace searcher {

    class BFSSearcher : public Searcher {

        public:

            template <typename ElementType>
            SearchResult search(const Searchable<ElementType>& searchable) const override;
    };
}