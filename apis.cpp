
#include <rtaudio/RtAudio.h>

//g++ -o apis apis.cpp -lrtaudio

int main() {
    std::vector<RtAudio::Api> apis;
    RtAudio::getCompiledApi(apis);

    std::cout << "APIs compilées disponibles :\n";
    for (auto api : apis) {
        std::cout << RtAudio::getApiName(api) << std::endl;
    }
}