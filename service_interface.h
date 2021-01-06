#include <memory>

//
// Service inherits from this class to be implemented.
//
class service_interface {
public:
    //
    // Calls from the client to the service.
    //
    virtual void call_service() = 0;

    //
    // Destructor.
    //
    virtual ~service_interface() = 0;
};

//
// Allocate the service: global function.
//
class client_interface;
std::unique_ptr<service_interface> make_service(client_interface &client);
