#ifndef REQUEST_H
#include "request.h"
#endif

using namespace std;

/**
 * @class request
 * @brief A class representing a network request with input and output IPs, a time duration, and a job type.
 */

/**
 * @brief Default constructor for the request class.
 * 
 * This is a dummy constructor that initializes an empty request. 
 * It will not be used for actual request handling.
 */
request::request() {
    this->ipIn = "";
    this->ipOut = "";
    this->time = 0;
    this->jobType = ' ';
}

/**
 * @brief Constructs a new request with the specified parameters.
 * 
 * @param ipIn The input IP address for the request.
 * @param ipOut The output IP address for the request.
 * @param time The time required to process the request.
 * @param jobType The type of the job ('P' for processing, 'S' for streaming).
 */
request::request(string ipIn, string ipOut, int time, char jobType) {
    this->ipIn = ipIn;
    this->ipOut = ipOut;
    this->time = time;
    this->jobType = jobType;
}

/**
 * @brief Converts the request object into a string representation.
 * 
 * @return string A string describing the request with input IP, output IP, and job type.
 */
string request::toString() {
    return "Request from " + this->ipIn + " to " + this->ipOut + " of type " + this->jobType;
}
