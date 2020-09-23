#include "ClientHandler.hpp"
#include "../solvers/Solver.hpp"
#include "../solvers/SearchSolver.hpp"
#include "../server/ServerExceptions.hpp"
#include "../solvers/SolverFactory.hpp"
#include "../cachemanager/CacheManager.hpp"
#include "../cachemanager/SolverOperation.hpp"
#include "../search/SearchExceptions.hpp"
#include "../cachemanager/util/HashUtil.hpp"
#include <unistd.h>
#include <string>

namespace server {

    namespace clientside {

        template <typename Problem, typename Solution>
        class SolverClientHandler : public ClientHandler {

            static const int s_bufferSize = 1000000;
            static const double s_version = 1.0;
            static const double s_emptyResponseLength = 0;
            static const double s_successStatus = 0;
            mutable cache::CacheManager m_cache;

            public:

                SolverClientHandler(const cache::CacheManager& cache)
                : m_cache(cache) {}

                void handleClient(const uint32_t clientSocket) const override {

                    //read problem
                    std::string command = readSock(clientSocket);

                    //error in recieving problem
                    if(command == ""){
                        writeSock(clientSocket, getLog(7, s_emptyResponseLength));
                        close(clientSocket);
                        return;
                    }

                    //success in recieving problem
                    if (writeSock(clientSocket, getLog(s_successStatus, s_emptyResponseLength)) < 0) {
                        close(clientSocket);
                        return;
                    }

                    //read input
                    std::string problemString = readSock(clientSocket);

                    //error in recieving input
                    if(problemString == ""){
                        writeSock(clientSocket, getLog(7, s_emptyResponseLength));
                        close(clientSocket);
                        return;
                    }

                    // success in recieving input, solving the problem with the input.
                    // this variable will hold the solution, as string
                    std::string solutionString;
                    // this variable will hold the status of the solving
                    uint32_t status = 0;

                    // first, searching for the solution in the cache:
                    // getting the hashCode of the operation
                    const uint32_t hashCode = util::HashUtil::calculateHash(command + problemString);
                    // if the operation result also exists in the cache, so getting it from the cache
                    if (m_cache.contains(hashCode)) {
                        try {
                            solutionString = m_cache.getOperationFileContent(hashCode);
                            // loading the operation into the cache
                            m_cache.load(operation::SolverOperation(hashCode, solutionString));
                        } catch (...) {
                            status = 6;
                        }

                    } else {
                        //getting the right solver according to the specific command
                        solver::SolverFactory<Problem, Solution> sFactory;
                        const auto solver = sFactory.getSolver(command);

                        //trying to solve the problem, return error message if one accurs
                        try {
                            solutionString = solver->solve(problemString);
                            // loading the operation into the cache
                            m_cache.load(operation::SolverOperation(hashCode, solutionString));
                        }
                        catch(const searcher::exceptions::PathDoesNotExistException&){
                            status = 1;
                        }
                        catch(const searcher::exceptions::InvalidPositionException&){
                            status = 2;
                        }
                        catch(const server::exceptions::InvalidCommandException&){
                            status = 3;
                        }
                        catch(const server::exceptions::ProtocolException&){
                            status = 4;
                        }
                        catch (...) {
                            status = 5;
                        }
                    }

                    //the calculation has succeeded
                    if(status == 0){
                        //send success message
                        if(writeSock(clientSocket, getLog(status, solutionString.size())) < 0){
                            close(clientSocket);
                            return;
                        }
                        //send solution
                        if(writeSock(clientSocket, solutionString) < 0){
                            close(clientSocket);
                            return;
                        }
                    }
                    //if the calculation has failed
                    else{
                        //send error message
                        if(writeSock(clientSocket, getLog(status, s_emptyResponseLength)) < 0){
                            close(clientSocket);
                            return;
                        }    
                    }

                    //close the port
                    close(clientSocket);          
                }

                int writeSock(const uint32_t clientSocket, std::string message){
                    return write(clientSocket, message.c_str(), message.size());
                }

                std::string readSock(const uint32_t clientSocket) const {
                    
                    char buffer[s_bufferSize];
                    size_t bytesRead;
                    int messageSize = 0;

                    while(bytesRead == read(clientSocket, buffer + messageSize, sizeof(buffer) - messageSize - 1) >= 0) {
                        messageSize += bytesRead;
                        if(messageSize > s_bufferSize - 1){
                            //fail
                            return "";
                        }
                        if(buffer[messageSize - 1] = "\r\n\r\n"){
                            break;
                        }
                    }

                    if(bytesRead < 0){
                        //fail
                        return "";
                    }
                    
                    //success
                    return static_cast<std::string>(buffer);
                

                    std::string message = static_cast<std::string>(buffer).substr(0, message.size() - 4);
                
                    //success
                    return message;
                }    
            

                std::string getLog(uint32_t status, uint32_t length) {
                    return "Version: " + s_version + "\r\n"
                    + "status: " + status + "\r\n"
                    + "response-length: " + length + "\r\n";
                }
        };
    }
}

