#include "client.h"
#include <array>

Client::Client(std::shared_ptr<Channel> channel) : stubtologin{AuthService::NewStub(channel)},
    stubtotakeincidents{IncidentService::NewStub(channel)} {}

std::pair<std::string, std::string>Client::login(std::string login_str,std::string password_str) {

    // Prepare request
    LoginRequest request;
    request.set_login(login_str);
    request.set_password(password_str);
    request.set_machine_id("af381d9c-25de-4059-b132-0f03b29a6385");

    // Send request
    LoginResponse response;

    ClientContext context;

    //Add metadata
    Status status;
    status = stubtologin->login(&context, request, &response);

    // Handle response
    if (status.ok()) {
        return make_pair(response.user_id(),response.session_token());
    } else {
        throw std::runtime_error(std::to_string(status.error_code()) + ": " + status.error_message());
    }
}

std::vector<std::string>Client::getActiveIncidentIds(std::string session_user,
                                                     std::string session_token,
                                                     std::string user_agent) {
    // Prepare request
    google::protobuf::Empty request;

    // Send request
    ActiveIncidentIds response;

    //Add metadata
    ClientContext context;
    context.AddMetadata("x-session-user", session_user);
    context.AddMetadata("x-session-token", session_token);
    context.AddMetadata("x-user-agent", user_agent);

    Status status;
    status = stubtotakeincidents->getActiveIncidentIds(&context, request, &response);

    // Handle response
    if (status.ok()) {

        std::vector<std::string> return_data;
        return_data.reserve(100);
        for(int var = 0; var < response.id().size(); ++var )
        {
            return_data.emplace_back(response.id().at(var));
        }

        return return_data;
    } else {

        throw std::runtime_error(std::to_string(status.error_code()) + ": " + status.error_message());
    }
}

void Client::logout(std::string session_user, std::string session_token, std::string user_agent) {

    // Prepare request
    google::protobuf::Empty request;

    // Send request
    google::protobuf::Empty response;

    //Add metadata
    ClientContext context;
    context.AddMetadata("x-session-user", session_user);
    context.AddMetadata("x-session-token", session_token);
    context.AddMetadata("x-user-agent", user_agent);

    Status status;
    status = stubtologin->logout(&context, request, &response);

    // Handle response
    if (!status.ok()) {
        throw std::runtime_error(std::to_string(status.error_code()) + ": " + status.error_message());
    }
}
