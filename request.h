#include <iostream>
#include <string>

using namespace std;

class Request {
public:
    Request(string ipIn, string ipOut, int time, char jobType);
    string ipIn;
    string ipOut;
    int time;
    char jobType;
};