#ifndef LOADBALANCER_H
#include "loadbalancer.h"
#endif

/**
 * @class loadbalancer
 * @brief A class representing a load balancer that manages and distributes requests.
 */

/**
 * @brief Constructs a new loadbalancer object, initializing the system time to 0.
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
    requests.push(req);
}

/**
 * @brief Fetches and removes the next request from the load balancer's queue.
 * 
 * @return request The next request in the queue. If the queue is empty, it returns an empty request.
 */
request loadbalancer::getRequest() {
    if (!requests.empty()) {
        request req = requests.front();
        requests.pop();
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
    return requests.size(); 
}

/**
 * @brief Checks if the load balancer's request queue is empty.
 * 
 * @return true If the queue is empty.
 * @return false If there are requests in the queue.
 */
bool loadbalancer::isEmpty() { 
    return requests.empty(); 
}
