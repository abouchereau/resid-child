#include <iostream>
#include <cmath>
#include <vector>
#include <cstdint>
#include <unistd.h>

int main() {
    std::cout << "READY" << std::endl;
    while (true) { 
        std::vector<uint8_t> buffer(2);
        std::cin.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
        std::streamsize bytesRead = std::cin.gcount();
        if (bytesRead ==2 ) {
            int octet1 = static_cast<int>(buffer[0]);
            int octet2 = static_cast<int>(buffer[1]);
            std::cout << octet1 << " " << octet2 << " ";
            std::cout << std::endl;       
        }
    }    

    std::cout << "Flux terminé. Arrêt du programme." << std::endl;
    return 0;
}