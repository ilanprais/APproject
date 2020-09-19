#include "Graph.hpp"
#include "BFSSearcher.hpp"
#include "DFSSearcher.hpp"
#include <iostream>

using namespace searcher;

int main() {
    // initializing a matrix
    int k = 1;
    matrix::Matrix gMatrix(3, 3);
    for (uint32_t i = 0; i < gMatrix.getHeight(); i++) {
        for (uint32_t j = 0; j < gMatrix.getWidth(); j++) {
            gMatrix.setAt(i, j, k);
            k++;
        }
    } gMatrix.setAt(1, 1, 0);

    std::cout << gMatrix << std::endl;


    // creating a graph object from the matrix
    Graph graph(gMatrix, std::pair<uint32_t, uint32_t>(0, 0), std::pair<uint32_t, uint32_t>(2, 2));

    // creating a BFS searcher object
    DFSSearcher<pair> DFS = DFSSearcher<pair>();

    try {
        
        // searching on the graph
        SearchResult result = DFS.search(graph);
        // printing the search result
        std::cout << result.toString();

    } catch (const std::runtime_error& e) {
        std::cout << e.what();
    }
}