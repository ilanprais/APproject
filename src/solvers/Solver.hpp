#pragma once

#include <string>

namespace solver {

    template <typename Problem, typename Solution>
    class Solver {

        public:

            virtual std::string solve(const std::string& problemString) const = 0;
    };
}