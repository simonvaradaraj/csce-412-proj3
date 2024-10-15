#ifndef LOADBALANCER_H
#include "loadbalancer.h"
#endif

loadbalancer::loadbalancer() { systemTime = 0; }
int loadbalancer::getSystemTime() { return systemTime; }
void loadbalancer::incTime() { systemTime++; }

void loadbalancer::addRequest(request req) {
    requests.push(req);
}

request loadbalancer::getRequest() {
    if (!requests.empty()) {
        request req = requests.front();
        requests.pop();
        return req;
    }
    return request();
}

int loadbalancer::getSize() { return requests.size(); }
bool loadbalancer::isEmpty() { return requests.empty(); }