#include "client_interface.h"
#include <iostream>

//
// Real client.
//
class client : public client_interface {
public:
    //
    // Calls from the service to the client.
    //
    void call_client() override { std::cout << "client called\n"; }

    //
    // Destructor.
    //
    ~client() override { std::cout << "client deallocated\n"; }

    //
    // Constructor.
    //
    client() { std::cout << "client allocated\n"; }

    //
    // Some other methods.
    //
    void do_the_job() { std::cout << "do the job\n"; service->call_service(); }
};

//
// Run the code.
//
int main()
{
    client clnt;

    clnt.do_the_job();
    return 0;
}
