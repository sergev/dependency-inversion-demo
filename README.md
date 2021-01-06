Let's design a demo of a generic service API which
follows the Dependency Inversion Principle. Details of the
service should be isolated from the client.

Assume we need to implement a service which has a few methods
available for the client, for example:

    call_service();

The service also has some state, hidden from the client.

To perform it's job, the service should call back the client
via a set of predefined methods, for example:

    call_client();

The client also has some state, hidden from the server.

First, we define an abstract class which exposes the service interface to the client.
A real service inherits from this class to be implemented.

```
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
```

A client needs one more method (actually a global function) to be able
to allocate the service instance. A parameter for this method is
a reference to the client object.

```
class client_interface;
std::unique_ptr<service_interface> make_service(client_interface &client);
```

Now we define an abstract class for the client.
The server uses this interface to call the client back when needed.

Besides virtual client methods, this class has one additional member:
a pointer to the service object. When constructed, this pointer is
initialized by make_service() function from above.

When the client object is deleted, the server object is
autometically deallocated.

```
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
```

That's all about virtual classes. Now let's implement a real client.

```
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
```

Here is an implementation of a real service.
Note, that the service holds a reference to the client, initialized by the constructor.

```
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
    service(client_interface &clnt) : client(clnt) { std::cout << "service allocated\n"; }

private:
    client_interface &client;
};
```

A global function for allocating a service is pretty straightforward.

```
std::unique_ptr<service_interface> make_service(client_interface &client)
{
    return std::make_unique<service>(client);
}
```

Add a main routine, which allocated a client and invokes it.

```
int main()
{
    client clnt;

    clnt.do_the_job();

    return 0;
}
```

Now let's run all this stuff.

```
$ make
c++ -g -O -std=c++14 -Wall   -c -o service.o service.cpp
c++ -g -O -std=c++14 -Wall   -c -o client.o client.cpp
c++ -g service.o client.o -o demo
$ ./demo
service allocated
client allocated
do the job
service called
client called
client deallocated
service deallocated
```

As you can see, the service and client are allocated, then the client's `do_the_job()` routine is invoked,
which calls the service, which calls the client back. Finally both client and service are deallocated.
