#include <jack/jack.h>
#include <cmath>
#include <iostream>
#include <resid/sid.h>
#include <vector>
#include <cstdint>
#include <unistd.h>

jack_port_t *output_port;
jack_client_t *client;

SID sid_chip;
double clock_accumulator = 0.0;


int process(jack_nframes_t nframes, void *arg) {
    float *buffer = (float *)jack_port_get_buffer(output_port, nframes);

    double clocks_per_sample = 985248.0 / 44100.0; // Fréquence d'horloge / Fréquence d'échantillonnage

    for (jack_nframes_t i = 0; i < nframes; i++) {
        clock_accumulator += clocks_per_sample;
        while (clock_accumulator >= 1.0) {
            sid_chip.clock(); 
            clock_accumulator -= 1.0;
        }
        short sid_output = sid_chip.output(); 
        float sample = static_cast<float>(sid_output) / 32768.0f;
        buffer[i] = sample;
    }
    return 0;
}

int main() {
    client = jack_client_open("sidVoice", JackNullOption, NULL);
    if (!client) {
        std::cerr << "Erreur lors de l'ouverture du client JACK" << std::endl;
        return 1;
    }

    sid_chip.set_sampling_parameters(985248.0, SAMPLE_RESAMPLE_INTERPOLATE, 44100.0,  -1.0, 0.97);  // Fréquence d'échantillonnage
    output_port = jack_port_register(client, "sidVoice", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
    jack_set_process_callback(client, process, NULL);
    jack_activate(client);   
    
    std::cout << "READY" << std::endl;

    while (true) { 
        std::vector<uint8_t> buffer(2);
        std::cin.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
        std::streamsize bytesRead = std::cin.gcount();
        if (bytesRead ==2) {
            int octet1 = static_cast<int>(buffer[0]);
            int octet2 = static_cast<int>(buffer[1]);
            sid_chip.write(octet1, octet2);  
            //std::cout << octet1 << " " << octet2 << " ";
        }
    }

    jack_client_close(client);
    return 0;
}
