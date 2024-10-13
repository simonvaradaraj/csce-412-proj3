#include "loadbalancer.h"

loadbalancer::loadbalancer() { systemTime = 0; }
int loadbalancer::getSystemTime() { return systemTime; }
void loadbalancer::incTime() { systemTime++; }

void loadbalancer::addRequest(request req) {
    requests.push(req);
    incTime();
}

request loadbalancer::getRequest() {
    incTime();
    if (!requests.empty()) {
        request req = requests.front();
        requests.pop();
        return req;
    }
}

bool loadbalancer::isEmpty() { return requests.empty(); }