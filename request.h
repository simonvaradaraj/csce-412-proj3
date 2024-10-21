/**
 * @file request.h
 * @brief Header file for the request class.
 *
 * This file contains the declaration of the request class, which represents an incoming 
 * request with associated attributes. The class provides methods for initializing a 
 * request and converting its data to a string representation.
 *
 * @class request
 * @brief A class representing an incoming request.
 *
 * The request class encapsulates the details of a network request, including the input 
 * and output IP addresses, the time associated with the request, and the type of job 
 * it represents. It provides a constructor for initializing these attributes and a 
 * method for converting the request data into a human-readable string format.
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <string>

using namespace std;

class request {
public:
    request();
    request(string ipIn, string ipOut, int time, char jobType);
    string ipIn;
    string ipOut;
    int time;
    char jobType;
    string toString();
};

#endif