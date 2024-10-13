#include <iostream>
#include <string>
#include "webserver.h"
// #include "loadbalancer.cpp"
#include "request.h"

using namespace std;

int main()
{
    // loadbalancer lb;
    webserver ws1("ws1");
    webserver ws2("ws2");
    webserver ws3("ws3");

    request req1(" ", " ", 1, 'S');
    cout << "Hello, World!" << endl;
}