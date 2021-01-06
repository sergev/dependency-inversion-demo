#include "service_interface.h"

//
// Client inherits from this class to use the service.
//
class client_interface {
public:
    //
    // Calls from the service to the client.
    //
    virtual void call_client() = 0;

    //
    // Destructor.
    //
    virtual ~client_interface() = 0;

    //
    // Reference from the client to the service.
    //
    std::unique_ptr<service_interface> service = make_service(*this);
};
