/**
 * @file webserver.h
 * @brief Header file for the webserver class.
 *
 * This file contains the declaration of the webserver class, which is responsible for 
 * handling incoming requests and managing server state. It includes methods for processing 
 * requests, tracking server name and start time, and determining when the server has 
 * completed its tasks.
 *
 * @class webserver
 * @brief A class representing a web server.
 *
 * The webserver class provides functionality to handle requests, manage server state,
 * and maintain the server's identity through its name. The class allows for processing
 * requests and checking the server's operational status based on the current time.
 */
#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <iostream>
#include <string>
#include "request.h"

using namespace std;

class webserver {
public:
    webserver();
    webserver(string name);
    request getRequest();
    int getStartTime();
    string getName();
    void processRequest(request req, int currentTime);
    void setName(string name);
    bool isDone(int currentTime);
private:
    request req;
    int start_time;
    string name;
};

#endif