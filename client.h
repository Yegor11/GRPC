#ifndef CLIENT_H
#define CLIENT_H

#include <v1/auth/auth-endpoints.grpc.pb.h>
#include <v1/incident/incident-endpoints.grpc.pb.h>

#include <iostream>
#include <certificate.h>
#include <utility>
#include <list>
#include <grpc++/grpc++.h>

using namespace grpc;

class Client {
public:

    Client(std::shared_ptr<Channel> channel);

    std::pair<std::string,std::string> login(std::string login_str,std::string password_str);
    void logout(std::string session_user, std::string session_token, std::string user_agent );
    std::vector<std::string> getActiveIncidentIds( std::string session_user,
                                                   std::string session_token,
                                                   std::string user_agent );
private:
    std::unique_ptr<AuthService::Stub> stubtologin;
    std::unique_ptr<IncidentService::Stub> stubtotakeincidents;
};


#endif // CLIENT_H
