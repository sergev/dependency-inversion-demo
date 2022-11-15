#include "service_interface.h"
#include <iostream>

//
// Real client.
//
class client : public client_interface {
private:
    //
    // Link to the service.
    //
    std::unique_ptr<service_interface> service;

public:
    //
    // Local call.
    //
    void do_the_job() override {
        std::cout << "do the job\n";
        service->call_service();
    }

    //
    // Call back from the service to the client.
    //
    void call_client() override {
        std::cout << "client called\n";
    }

    //
    // Destructor.
    //
    ~client() override {
        std::cout << "client deallocated\n";
    }

    //
    // Constructor.
    //
    client()
        : service(service_interface::make_service(*this)) {
        std::cout << "client allocated\n";
    }
};

//
// Allocate a client.
//
std::unique_ptr<client_interface> client_interface::make_client()
{
    return std::make_unique<client>();
}
