#include "server.h"

void RunServer() {

    std::string server_address("0.0.0.0:50051");
    LoGinOut comunication;
    GetInc getincidents;

    // Build server
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&comunication);
    builder.RegisterService(&getincidents);
    std::unique_ptr<Server> server{builder.BuildAndStart()};

    // Run server
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main()
{
    RunServer();
    return 0;
}
