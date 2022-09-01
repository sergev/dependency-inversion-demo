#include "client_interface.h"
#include <iostream>

//
// Real service.
//
class service : public service_interface {
public:
    //
    // Calls from the client to the service.
    //
    void call_service() override { std::cout << "service called\n"; client.call_client(); }

    //
    // Destructor.
    //
    ~service() override { std::cout << "service deallocated\n"; }

    //
    // Constructor.
    //
    explicit service(client_interface &clnt) : client(clnt) { std::cout << "service allocated\n"; }

private:
    client_interface &client;
};

//
// Allocate a service for the given client.
//
std::unique_ptr<service_interface> make_service(client_interface &client)
{
    return std::make_unique<service>(client);
}

//
// Need to define the pure virtual destructors.
//
service_interface::~service_interface()
{
    // Empty.
}

client_interface::~client_interface()
{
    // Empty.
}
