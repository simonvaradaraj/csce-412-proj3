#include <iostream>
#include <string>
#include "request.cpp"

using namespace std;

class webserver {
public:
    webserver();
    webserver(string name);
    request getRequest();
    string getName();
    void processRequest(request req, int currentTime);
    void setName(string name);
    bool isDone(int currentTime);
private:
    request req;
    int start_time;
    string name;
};