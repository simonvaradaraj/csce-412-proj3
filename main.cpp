#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include "webserver.cpp"
#include "loadbalancer.cpp"
#include "request.cpp"

using namespace std;

// Define thresholds for scaling up/down
const int INITIAL_NUM_SERVERS = 10;   
const int MIN_NUM_SERVERS = 4;   
const int REQUEST_BURST = 1000;   

// for shared access of resouroces
mutex queueMutex; 
mutex serverMutex;
// notifying the threads
atomic<bool> stopThreads(false);
condition_variable cv;

request generateRequest() {
    stringstream ipIn, ipOut;
    ipIn << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);
    ipOut << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);

    request req(ipIn.str(), ipOut.str(), (rand() % 10) + 1, (rand() % 2) == 0 ? 'P' : 'S');
    return req;
}

// function that will be running on each server thread
void serverThread(webserver& server, loadbalancer& balancer) {
    while (!stopThreads) {
        int currentTime = balancer.getSystemTime();

        // Lock to safely access the queue
        unique_lock<mutex> lock(queueMutex);

        if (server.isDone(currentTime)) {
            if (balancer.getSize() > 0) {
                request req = server.getRequest();
                if (req.jobType != ' ') {
                    cout << "Time " << currentTime << ": Request from " << req.ipIn << " to " << req.ipOut
                         << " of type " << req.jobType << " has been processed by " << server.getName() << endl;
                }
                // place a request if the server.getRequest() gives a valid response
                server.processRequest(balancer.getRequest(), balancer.getSystemTime());
            }
        }
    }
}

int main() {
    srand(time(NULL));
    loadbalancer balancer;

    // generate a full queue (usually servers * 100)
    for (int i = 0; i < INITIAL_NUM_SERVERS * 100; i++) {
        request req = generateRequest();
        balancer.addRequest(req);
    }

    // Show the starting queue size.
    cout << "Initial queue size: " << balancer.getSize() << endl;

    // Replacing with a vector so i can resize it
    vector<webserver> serverarray;

    // Start with the initial number of servers
    for (int i = 0; i < INITIAL_NUM_SERVERS; i++) {
        stringstream name;
        name << "Server " << i+1;
        webserver server(name.str());
        server.processRequest(balancer.getRequest(), balancer.getSystemTime());
        serverarray.push_back(server);
    }

    // Running for 10000 clock cycles
    while (balancer.getSystemTime() < 10000) {
        // cout << "Time " << balancer.getSystemTime() << endl;
        int currentTime = balancer.getSystemTime();

        // Check the current queue size
        int queueSize = balancer.getSize();
        int currentNumServers = serverarray.size();

        // Scaling up logic
        if (queueSize > currentNumServers * 10) {
            int newServers = currentNumServers;  // make the same amount of newservers as the existing ones
            for (int i = 0; i < newServers; i++) {
                stringstream name;
                name << "Server " << serverarray.size() + 1;
                webserver newServer(name.str());
                newServer.processRequest(balancer.getRequest(), balancer.getSystemTime());
                serverarray.push_back(newServer);
            }
            cout << "Time " << currentTime << ": Doubled servers to " << serverarray.size() << endl;
        }

        // scale down logic
        else if (queueSize < currentNumServers && currentNumServers > MIN_NUM_SERVERS) {
            serverarray.resize(currentNumServers / 2);
            cout << "Time " << currentTime << ": Halved servers to " << serverarray.size() << endl;
        }

        // Process each server
        for (long unsigned int i = 0; i < serverarray.size(); i++) {
            if (serverarray[i].isDone(currentTime)) {
                request req = serverarray[i].getRequest();
                if (req.jobType != ' ') {
                    cout << "Time " << currentTime << ": Request from " << req.ipIn << " to " << req.ipOut << " of type " << req.jobType << " has been processed by " << serverarray[i].getName() << endl;
                }
                serverarray[i].processRequest(balancer.getRequest(), balancer.getSystemTime());
            }
        }

        //  add new requests at random times to simulate new requests after the initial full queue you set up.
        if ((rand() % 10) == 0) {
            request req = generateRequest();
            balancer.addRequest(req);
            // cout << "Queue size: " << balancer.getSize() << endl;
            cout << "Time " << currentTime << ": Request from " << req.ipIn << " to " << req.ipOut << " of type " << req.jobType << " has been generated" << endl;
        }

        // Simulate a burst of requests at rare times
        if ((rand() % REQUEST_BURST) == 0) {
            cout << "Time " << currentTime << ": Request Burst has been generated" << endl;
             for (long unsigned int i = 0; i < REQUEST_BURST; i++) {
                request req = generateRequest();
                balancer.addRequest(req);
            }
        }
        balancer.incTime();
    }

    // Show the ending queue size
    cout << "Ending queue size: " << balancer.getSize() << endl;
}
