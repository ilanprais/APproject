#include "server/SerialServer.hpp"
#include "clienthandlers/SolverClientHandler.hpp"
#include "search/searcher/SearchResult.hpp"
#include "search/searchable/Graph.hpp"
#include "cachemanager/CacheManager.hpp"

        int main(){

            cache::CacheManager cache(5, "cache");

            server_side::client_handler::SolverClientHandler<searcher::Graph, searcher::SearchResult> handler(cache);

            server_side::SerialServer serialServer = server_side::SerialServer();

            serialServer.open(8081, handler);

            return 0;
        }