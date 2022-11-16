#ifndef SERVER_H
#define SERVER_H

#include <v1/auth/auth-endpoints.grpc.pb.h>
#include <v1/incident/incident-endpoints.grpc.pb.h>

#include <iostream>
#include <certificate.h>
#include <utility>
#include <list>
#include <map>
#include <grpc++/grpc++.h>

const static std::string password = "password";
const static std::string logger = "logger@gmail.com";
const static std::string session_token_id = "111102YM";
const static std::string session_user_id = "11";

using namespace grpc;

class LoGinOut final : public AuthService::Service {

    Status login(ServerContext* context, const LoginRequest* request, LoginResponse* response) override{

        if (request->login() == logger && request->password() == password )
        {
            response->set_user_id(session_user_id);
            response->set_session_token(session_token_id);
            return Status::OK;
        }
        else
        {
            return Status(StatusCode::UNAUTHENTICATED, "UNAUTHORIZED WHILE LOGIN");
        }

    }

    Status logout(ServerContext* context, const google::protobuf::Empty* request, google::protobuf::Empty* response) override{

        const std::multimap<grpc::string_ref, grpc::string_ref> metadata = context->client_metadata();

        auto token_id = metadata.find("x-session-token");
        if(token_id->second != "111102YM")
        {
             return Status(StatusCode::UNAUTHENTICATED, "UNAUTHORIZED WRONG SESSION_TOKEN WHILE LOGOUT ");
        }

        auto user_id = metadata.find("x-session-user");
        if(user_id->second != session_user_id)
        {
             return Status(StatusCode::UNAUTHENTICATED, "UNAUTHORIZED  WRONG SESSION_USER WHILE LOGOUT ");
        }

         return Status::OK;
    }

} ;

class GetInc final :  public IncidentService::Service{

    Status getActiveIncidentIds(ServerContext* context,  const google::protobuf::Empty* request, ActiveIncidentIds* response) override  {

        const std::multimap<grpc::string_ref, grpc::string_ref> metadata = context->client_metadata();

          auto token_id = metadata.find("x-session-token");
          if(token_id->second != session_token_id)
          {
              std::cout << token_id->second <<std::endl;
             return Status(StatusCode::UNAUTHENTICATED, "UNAUTHORIZED wrong session_token incidents ");
          }

        auto user_id = metadata.find("x-session-user");
        if(user_id->second != session_user_id)
        {
             return Status(StatusCode::UNAUTHENTICATED, "UNAUTHORIZED  wrong session_user incidents ");
        }

        google::protobuf::RepeatedPtrField<std::string> incidents;
        incidents.Add("1111111111111");
        incidents.Add("2222222222222");
        incidents.Add("3333333333333");
        *response-> mutable_id() = incidents;

        return Status::OK;
    }

} ;

#endif // SERVER_H
