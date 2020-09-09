#pragma once

#include "Searcher.hpp"
#include "SearchResult.hpp"
#include <string>

namespace searcher {

    class DFSSearcher : public Searcher {

        public:

            template <typename ElementType>
            SearchResult search(const Searchable<ElementType>& searchable) const override;

        private:

            template <typename ElementType>
            double recursiveSearch(const Searchable<ElementType>& searchable, std::vector<ElementType>& visited,
                std::vector<std::string>& directions, const ElementType& current);
    };
}