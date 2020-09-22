#pragma once

#include "InputParser.hpp"
#include "Graph.hpp"

namespace parser {

    class SearcherInputParser : public InputParser<searcher::Graph> {

        public:

            searcher::Graph parseInput(const std::string& input) const;
    }
}