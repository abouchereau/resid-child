
#include <iostream>
#include <string>
using namespace std;

double BUFFER = 128.0;
double SAMPLE_RATE = 44100.0;


// defining main with arguments
int main(int argc, char* argv[]) {

    if (argc>1) {
        SAMPLE_RATE = stod(argv[1]);
    }

    if(argc>2) {
        BUFFER = stod(argv[2]);
    }

    std::cout << SAMPLE_RATE << " < SAMPLE_RATE ";
    std::cout << BUFFER << " < BUFFER ";
    return 0;
};