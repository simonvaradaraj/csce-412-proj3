#pragma once

#include <iostream>
#include <string>
#include <queue>
#include "request.cpp"

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