#include "Graph.hpp"
#include "BFSSearcher.hpp"
#include "DFSSearcher.hpp"
#include <iostream>

using namespace searcher;

int main() {
    // initializing a matrix
    matrix::Matrix gMatrix(3, 3);
    for (uint32_t i = 0; i < gMatrix.getHeight(); i++) {
        for (uint32_t j = 0; j < gMatrix.getWidth(); j++) {
            gMatrix.setAt(i, j, 1);
        }
    }

    // creating a graph object from the matrix
    Graph graph(gMatrix, std::pair<uint32_t, uint32_t>(0, 0), std::pair<uint32_t, uint32_t>(2, 2));

    // creating a BFS searcher object
    BFSSearcher BFS = BFSSearcher();

    // searching on the graph
    auto result = BFS.search(graph);

    // printing the search result
    std::cout << result.toString();
}