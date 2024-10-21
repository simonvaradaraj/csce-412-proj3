#ifndef WEB_SERVER_H
#include "webserver.h"
#endif

using namespace std;

/**
 * @class webserver
 * @brief Represents a web server that processes network requests.
 */

/**
 * @brief Default constructor for creating a webserver object.
 * 
 * Initializes the server with a default name ("default"), a start time of 0, and an empty request.
 */
webserver::webserver() {
    this->name = "default";
    this->start_time = 0;
    this->req = request();  // Initialize with an empty request
}

/**
 * @brief Constructs a new webserver object with a specified name.
 * 
 * @param name The name of the web server.
 */
webserver::webserver(string name) {
    this->name = name;
    this->start_time = 0;
    this->req = request();  // Initialize with an empty request
}

/**
 * @brief Gets the current request being processed by the web server.
 * 
 * @return request The request object being processed.
 */
request webserver::getRequest() { 
    return req; 
}

/**
 * @brief Gets the start time of the current request.
 * 
 * @return int The start time of the current request being processed by the server.
 */
int webserver::getStartTime() { 
    return start_time; 
}

/**
 * @brief Gets the name of the web server.
 * 
 * @return string The name of the server.
 */
string webserver::getName() { 
    return name; 
}

/**
 * @brief Processes a new request on the web server, updating the start time.
 * 
 * @param req The request to be processed.
 * @param currentTime The current time when the request starts being processed.
 */
void webserver::processRequest(request req, int currentTime) {
    this->req = req;
    this->start_time = currentTime;
}

/**
 * @brief Sets the name of the web server.
 * 
 * @param name The new name of the server.
 */
void webserver::setName(string name) { 
    this->name = name; 
}

/**
 * @brief Checks if the current request has been processed.
 * 
 * @param currentTime The current system time.
 * @return true If the request has been completed.
 * @return false If the request is still being processed.
 */
bool webserver::isDone(int currentTime) { 
    return (currentTime >= (start_time + req.time)); 
}
