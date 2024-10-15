#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <iostream>
#include <string>
#include <queue>
#include "request.h"

class loadbalancer {
public:
    loadbalancer();
    int getSystemTime();
    void incTime();
    void addRequest(request req);
    request getRequest();
    bool isEmpty();
private:
    int systemTime;
    queue<request> requests;
};

#endif