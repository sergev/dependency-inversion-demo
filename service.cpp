#include "service_interface.h"
#include <iostream>

//
// Real service.
//
class service : public service_interface {
private:
    //
    // Reference to the client.
    //
    client_interface &client;

public:
    //
    // Call from the client to the service.
    //
    void call_service() override {
        std::cout << "service called\n";
        client.call_client();
    }

    //
    // Destructor.
    //
    ~service() override {
        std::cout << "service deallocated\n";
    }

    //
    // Constructor.
    //
    explicit service(client_interface &clnt)
        : client(clnt) {
        std::cout << "service allocated\n";
    }
};

//
// Allocate a service for the given client.
//
std::unique_ptr<service_interface> service_interface::make_service(client_interface &client)
{
    return std::make_unique<service>(client);
}
