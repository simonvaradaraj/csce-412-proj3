#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <sstream>

#include "webserver.cpp"
#include "loadbalancer.cpp"
#include "request.cpp"

using namespace std;

// 10 servers
const int NUM_SERVERS = 10;

request generateRequest() {
    stringstream ipIn, ipOut;
    ipIn << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);
    ipOut << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);

    // range for task time is 1-10
    request req(ipIn.str(), ipOut.str(), (rand() % 10) + 1, (rand() % 2) == 0 ? 'P' : 'S');
    return req;
}

int main() {
    srand(time(NULL));
    loadbalancer balancer;


    // generate a full queue (usually servers * 100)
    for (int i = 0; i < (NUM_SERVERS * 100); i++) {
        request req = generateRequest();
        balancer.addRequest(req);
    }

    // Show the starting queue size.
    cout << "Initial queue size: " << balancer.getSize() << endl;


    webserver serverarray[NUM_SERVERS];
    for (int i = 0; i < NUM_SERVERS; i++) {
        stringstream name;
        name << "Server " << i+1;
        serverarray[i] = webserver(name.str());
        serverarray[i].processRequest(balancer.getRequest(), balancer.getSystemTime());
    }

    // Running for 10000 clock cycles 
    while (balancer.getSystemTime() < 10000) {
        // cout << "Time " << balancer.getSystemTime() << endl;
        int currentTime = balancer.getSystemTime();

        if (serverarray[currentTime % NUM_SERVERS].isDone(currentTime)) {
            request req = serverarray[currentTime % NUM_SERVERS].getRequest();
            if (req.jobType != ' ') {
                cout << "Time " << currentTime << ": " "Request from " << req.ipIn << " to " << req.ipOut << " of type " << req.jobType << " has been processed by " << serverarray[currentTime % NUM_SERVERS].getName() << endl;
                serverarray[currentTime % NUM_SERVERS].processRequest(balancer.getRequest(), balancer.getSystemTime());
            }
            else {
                serverarray[currentTime % NUM_SERVERS].processRequest(balancer.getRequest(), balancer.getSystemTime());
            }
        }

        //  add new requests at random times to simulate new requests after the initial full queue you set up.
        if ((rand() % 10) == 0) {
            request req = generateRequest();
            balancer.addRequest(req);
            // cout << "Queue size: " << balancer.getSize() << endl;
        }

        balancer.incTime();
    }

    // Show the starting queue size.
    cout << "Ending queue size: " << balancer.getSize() << endl;
}
