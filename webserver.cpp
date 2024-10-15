#ifndef WEB_SERVER_H
#include "webserver.h"
#endif

using namespace std;

webserver::webserver() {
    this->name = "default";
    this->start_time = 0;
}

webserver::webserver(string name) {
    this->name = name;
    this->start_time = 0;
}

request webserver::getRequest() { return req; }
string webserver::getName() { return name; }

void webserver::processRequest(request req, int currentTime) {
    this->req = req;
    this->start_time = currentTime;
}

void webserver::setName(string name) { this->name = name; }
bool webserver::isDone(int currentTime) { return (currentTime >= (start_time + req.time)); }
