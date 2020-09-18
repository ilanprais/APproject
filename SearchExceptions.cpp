#include "SearchExceptions.hpp"

namespace searcher {

    namespace exceptions {

        InvalidStartPositionException::InvalidStartPositionException()
            : std::runtime_error("Invalid start position") {}

        InvalidEndPositionException::InvalidEndPositionException()
            : std::runtime_error("Invalid end position") {}
    }
}