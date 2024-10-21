/**
 * @file loadbalancer.h
 * @brief Header file for the loadbalancer class.
 *
 * This file contains the declaration of the loadbalancer class, which is responsible for
 * managing incoming requests and simulating the system's operational time. The class
 * provides methods for adding requests to a queue, retrieving requests, and managing
 * the system time.
 *
 * @class loadbalancer
 * @brief A class representing a load balancer for handling requests.
 *
 * The loadbalancer class facilitates the management of requests in a queue, allowing 
 * for the addition and retrieval of requests. It also tracks the system time, enabling
 * operations that depend on time simulation. The class includes methods to check the 
 * size of the request queue and determine if it is empty.
 */

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <iostream>
#include <string>
#include <queue>
#include <mutex>
#include "request.h"

class loadbalancer {
public:
    loadbalancer();
    int getSystemTime();
    void incTime();
    void addRequest(request req);
    request getRequest();
    int getSize();
    bool isEmpty();
private:
    int systemTime;
    queue<request> requests;
    mutex queueMutex;
};

#endif