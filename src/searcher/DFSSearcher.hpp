#pragma once
#include "Searcher.hpp"
#include "string"

namespace searcher{

    class DFSSearcher : public Searcher {

        public:
            template <typename ElementType>
            SearchSolution search(const Searchable<ElementType>& searchable) const;

        private:
            template <typename ElementType>
            uint32_t recursiveSearch(std::vector<ElementType>& visited, std::vector<std::string>& directions, const Searchable<ElementType>& searchable, const ElementType& elm);
    };
}