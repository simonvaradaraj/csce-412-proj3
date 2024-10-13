#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <sstream>

#include "webserver.h"
#include "loadbalancer.h"
#include "request.h"

using namespace std;

const int MAX_REQUESTS = 5;

request generateRequest() {
    stringstream ipIn, ipOut;
    ipIn << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);
    ipOut << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);
    request req(ipIn.str(), ipOut.str(), (rand() % 10) + 1, (rand() % 2) == 0 ? 'P' : 'S');
}

int main()
{
    // loadbalancer lb;
    
}