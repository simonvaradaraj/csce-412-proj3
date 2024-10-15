#ifndef REQUEST_H
#include "request.h"
#endif

using namespace std;

// dummy constructor that I will not be using
request::request() {
    this->ipIn = "";
    this->ipOut = "";
    this->time = 0;
    this->jobType = ' ';
}

request::request(string ipIn, string ipOut, int time, char jobType) {
    this->ipIn = ipIn;
    this->ipOut = ipOut;
    this->time = time;
    this->jobType = jobType;
}

string request::toString() {
    return "Request from " + this->ipIn + " to " + this->ipOut + " of type " + this->jobType;
}