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
};