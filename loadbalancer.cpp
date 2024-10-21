#ifndef LOADBALANCER_H
#include "loadbalancer.h"
#endif

#include <mutex>

/**
 * @class loadbalancer
 * @brief A class representing a load balancer that manages and distributes requests.
 */

loadbalancer::loadbalancer() {
    systemTime = 0;
}

/**
 * @brief Gets the current system time of the load balancer.
 * 
 * @return int The current system time.
 */
int loadbalancer::getSystemTime() {
    return systemTime;
}

/**
 * @brief Increments the system time of the load balancer by 1.
 */
void loadbalancer::incTime() {
    systemTime++;
}

/**
 * @brief Adds a new request to the load balancer's queue.
 * 
 * @param req The request object to be added to the queue.
 */
void loadbalancer::addRequest(request req) {
    std::lock_guard<std::mutex> lock(queueMutex); // Lock the mutex
    requests.push(req); // Safely add the request
}

/**
 * @brief Fetches and removes the next request from the load balancer's queue.
 * 
 * @return request The next request in the queue. If the queue is empty, it returns an empty request.
 */
request loadbalancer::getRequest() {
    std::lock_guard<std::mutex> lock(queueMutex); // Lock the mutex
    if (!requests.empty()) {
        request req = requests.front();
        requests.pop(); // Safely pop the request
        return req;
    }
    return request(); // Return an empty request if queue is empty.
}

/**
 * @brief Gets the number of requests currently in the load balancer's queue.
 * 
 * @return int The number of requests in the queue.
 */
int loadbalancer::getSize() {
    return requests.size(); // Safely return the size
}

/**
 * @brief Checks if the load balancer's request queue is empty.
 * 
 * @return true If the queue is empty.
 * @return false If there are requests in the queue.
 */
bool loadbalancer::isEmpty() {
    return requests.empty(); // Safely check if the queue is empty
}
