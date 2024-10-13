#include "request.h"

using namespace std;

Request::Request(string ipIn, string ipOut, int time, char jobType) {
    this->ipIn = ipIn;
    this->ipOut = ipOut;
    this->time = time;
    this->jobType = jobType;
}