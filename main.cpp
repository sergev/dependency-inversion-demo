#include "client_interface.h"

//
// Run the code.
//
int main()
{
    auto client = client_interface::make_client();

    client->do_the_job();
    return 0;
}
