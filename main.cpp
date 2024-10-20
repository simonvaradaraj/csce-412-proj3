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
const int CLOCK_CYCLES = 10000;
const int MAX_TASK_TIME = 10;

// for shared access of resouroces
mutex queueMutex; 
mutex serverMutex;
mutex coutMutex;
// notifying the threads
atomic<bool> stopThreads(false);
condition_variable cv;

request generateRequest() {
    stringstream ipIn, ipOut;
    ipIn << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);
    ipOut << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);

    request req(ipIn.str(), ipOut.str(), (rand() % MAX_TASK_TIME) + 1, (rand() % 2) == 0 ? 'P' : 'S');
    return req;
}

// function that will be running on each server thread
void serverThread(webserver& server, loadbalancer& balancer) {
    while (!stopThreads) {
        int currentTime = balancer.getSystemTime();
        // Lock to safely access the queue
        unique_lock<mutex> lock(queueMutex);

        if (server.isDone(currentTime)) {
            if (!balancer.isEmpty()) {
                request req = server.getRequest();
                if (req.jobType != ' ') {
                    lock_guard<mutex> outputLock(coutMutex);
                    // execution, processing, assignment, etc.
                    cout <<  "Request from " << req.ipIn << " to " << req.ipOut << " of type " << req.jobType << " has been processed by " << server.getName() << endl;
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

    // Basic Logs
    /*
        1. Show the starting queue size.
        2. Show the ending queue size. (At the bottom with End Status)
        3. List your range for task times.
    */
    {
        lock_guard<mutex> outputLock(coutMutex);
        cout << "----------------------- START STATUS -----------------------" << endl;
        cout << "Clock Cycles: " << CLOCK_CYCLES << endl;
        cout << "Number of intial servers: " << INITIAL_NUM_SERVERS << endl;
        cout << "Starting queue size: " << balancer.getSize() << endl;
        cout << "Range for Task Times: 1 - " << MAX_TASK_TIME << endl;
        cout << "Random requests have a 1/10 chance to generate" << endl;
        cout << "Request Bursts have " << REQUEST_BURST << " requests and has a 1/1000 chance" << endl;
        cout << "------------------------------------------------------------" << endl;
    }

    vector<webserver> serverarray;
    // added a vector for the server threads too
    vector<thread> serverThreads;

    // Start with the initial number of servers
    for (int i = 0; i < INITIAL_NUM_SERVERS; i++) {
        stringstream name;
        name << "Server " << i+1;
        webserver server(name.str());
        server.processRequest(balancer.getRequest(), balancer.getSystemTime());
        serverarray.push_back(server);
        serverThreads.push_back(thread(serverThread, ref(serverarray[i]), ref(balancer)));
    }

    // Running for 10000 clock cycles
    while (balancer.getSystemTime() < CLOCK_CYCLES) {
        // cout << "Time " << balancer.getSystemTime() << endl;

        // Check the current queue size
        int queueSize = balancer.getSize();
        int currentNumServers = serverarray.size();

        // Scaling up logic
        if (queueSize > currentNumServers * 10) {
            int newServers = currentNumServers;  // make the same amount of newservers as the existing ones
            {
                lock_guard<mutex> guard(serverMutex);
                stopThreads = true;  // Signal threads to stop
                for (thread &t : serverThreads) {
                    if (t.joinable()) {
                        t.join();  // Wait for all threads to finish
                    }
                }
                // Reset the stop flag and resize server array
                stopThreads = false;
                serverThreads.clear();
                // Add new servers
                for (int i = 0; i < newServers; i++) {
                    stringstream name;
                    name << "Server " << serverarray.size() + 1;
                    webserver newServer(name.str());
                    newServer.processRequest(balancer.getRequest(), balancer.getSystemTime());
                    serverarray.push_back(newServer);
                }
                // Relaunch threads
                for (webserver &server : serverarray) {
                    serverThreads.push_back(thread(serverThread, ref(server), ref(balancer)));
                }
            }
            {
                lock_guard<mutex> outputLock(coutMutex);
                // show the dynamic change in number of servers
                cout << "Doubled servers to " << serverarray.size() << endl;
            }
        }

        // scale down logic
        else if (queueSize < currentNumServers && currentNumServers > MIN_NUM_SERVERS) {
            {
                lock_guard<mutex> guard(serverMutex);
                stopThreads = true;
                for (thread &t : serverThreads) {
                    if (t.joinable()) {
                        t.join();  // finish the threads
                    }
                }
                // chopping the array in half
                stopThreads = false;
                serverThreads.clear();
                serverarray.resize(currentNumServers / 2);
                // start up the threads after resizing
                for (webserver &server : serverarray) {
                    serverThreads.push_back(thread(serverThread, ref(server), ref(balancer)));
                }
            }
            {
                lock_guard<mutex> outputLock(coutMutex);
                // show the dynamic change in number of servers
                cout << "Halved servers to " << serverarray.size() << endl;
            }
        }
        //  add new requests at random times to simulate new requests after the initial full queue you set up.
        if ((rand() % 10) == 0) {
            request req = generateRequest();
            balancer.addRequest(req);
            // cout << "Queue size: " << balancer.getSize() << endl;
            {
                lock_guard<mutex> outputLock(coutMutex);
                // randomness in request generation
                cout << "Request from " << req.ipIn << " to " << req.ipOut << " of type " << req.jobType << " has been generated" << endl;
            }
        }

        // Simulate a burst of requests at rare times
        if ((rand() % REQUEST_BURST) == 0) {
            {
                lock_guard<mutex> outputLock(coutMutex);
                // randomness in request generation
                cout << "Request Burst has been generated" << endl;
            }
            for (long unsigned int i = 0; i < REQUEST_BURST; i++) {
                request req = generateRequest();
                balancer.addRequest(req);
            }
        }
        balancer.incTime();
    }
    stopThreads = true;
    // join the threads one last time
    for (thread& t : serverThreads) {
        if (t.joinable()) {
            t.join();
        }
    }
    {
        lock_guard<mutex> outputLock(coutMutex);
        cout << "----------------------- END STATUS -----------------------" << endl;
        // remaining requests in queue
        cout << "Ending queue size: " << balancer.getSize() << endl;
        // active servers, inactive servers
        cout << "Server Statuses: " << endl;
        for (long unsigned int i = 0; i < serverarray.size(); i++) {
            if (serverarray[i].getRequest().jobType != ' ') { cout << serverarray[i].getName() << ": Active" << endl;}
            else { cout << serverarray[i].getName() << ": Inactive" << endl;}
        }
        // rejected/discarded requests later
        cout << "------------------------------------------------------------" << endl;
    }
}
