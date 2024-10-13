#include "request.h"

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