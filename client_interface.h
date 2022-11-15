#include <memory>

//
// Client inherits from this class to use the service.
//
class client_interface {
public:
    //
    // Local calls.
    //
    virtual void do_the_job() = 0;

    //
    // Calls back from the service to the client.
    //
    virtual void call_client() = 0;

    //
    // Destructor.
    //
    virtual ~client_interface() {}

    //
    // Factory to create a client: static method.
    //
    static std::unique_ptr<client_interface> make_client();
};
