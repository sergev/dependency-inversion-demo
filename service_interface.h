#include "client_interface.h"
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
    virtual ~service_interface() {}

    //
    // Factory to create a service: static method.
    //
    static std::unique_ptr<service_interface> make_service(client_interface &client);
};
