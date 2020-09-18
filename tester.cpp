#include "Graph.hpp"
#include "BFSSearcher.hpp"
#include "DFSSearcher.hpp"
#include <iostream>

using namespace searcher;

int main() {
    // initializing a matrix
    int k = 1;
    matrix::Matrix gMatrix(5, 5);
    for (uint32_t i = 0; i < gMatrix.getHeight(); i++) {
        for (uint32_t j = 0; j < gMatrix.getWidth(); j++) {
            if(i == 2 && j == 2){
                gMatrix.setAt(i, j, 0);
            }else{
                gMatrix.setAt(i, j, k);
            }
            k++;
        }
    }

    std::cout << gMatrix << std::endl;


    // creating a graph object from the matrix
    Graph graph(gMatrix, std::pair<uint32_t, uint32_t>(0, 0), std::pair<uint32_t, uint32_t>(4, 4));

    // creating a BFS searcher object
    BFSSearcher<pair> BFS = BFSSearcher<pair>();

    // searching on the graph
    SearchResult result = BFS.search(graph);

    // printing the search result
    std::cout << result.toString();
}