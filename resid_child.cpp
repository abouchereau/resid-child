#include <iostream>
#include <cmath>
#include <vector>
#include <rtaudio/RtAudio.h>
#include <resid/sid.h>
#include <cstdint>
#include <unistd.h>


SID sid_chip;
unsigned int sample_rate = 44100;
unsigned int buffer_size = 512;
unsigned int frame_count = 0;
double clock_accumulator = 0.0;
// Callback audio pour RtAudio
int audioCallback(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
                  double streamTime, RtAudioStreamStatus status, void* userData) {
    float* buffer = static_cast<float*>(outputBuffer);
    
   double clocks_per_sample = 985248.0 / 44100.0; // Fréquence d'horloge / Fréquence d'échantillonnage

    for (unsigned int i = 0; i < nBufferFrames; ++i) {

        clock_accumulator += clocks_per_sample;
        while (clock_accumulator >= 1.0) {
            sid_chip.clock();  // Simuler un cycle d'horloge du SID
            clock_accumulator -= 1.0;
        }
        short sid_output = sid_chip.output(); 
        float sample = static_cast<float>(sid_output) / 32768.0f;
        buffer[i] = sample;
    }

    return 0;
}


int main() {
    try {
        RtAudio audio;
        if (audio.getDeviceCount() < 1) {
            throw std::runtime_error("Aucun périphérique audio trouvé.");
        }

        sid_chip.set_sampling_parameters(985248.0, SAMPLE_RESAMPLE_INTERPOLATE, 44100.0,  -1.0, 0.97);  // Fréquence d'échantillonnage

        // Configurer RtAudio
        RtAudio::StreamParameters outputParams;
        outputParams.deviceId = audio.getDefaultOutputDevice();
        outputParams.nChannels = 2;
        outputParams.firstChannel = 0;

        RtAudio::StreamOptions options;
        options.flags = RTAUDIO_SCHEDULE_REALTIME;
        options.flags = RTAUDIO_NONINTERLEAVED;

        // Démarrer le flux audio
        audio.openStream(&outputParams, nullptr, RTAUDIO_FLOAT32, sample_rate,
                         &buffer_size, &audioCallback, nullptr);
        audio.startStream();


        std::cout << "READY" << std::endl;

        while (true) { 
            std::vector<uint8_t> buffer(2);
            std::cin.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
            std::streamsize bytesRead = std::cin.gcount();
            if (bytesRead == 0 && std::cin.eof()) {
                std::cout.flush();
                break;
            }
            if (bytesRead > 0) {
                for (std::streamsize i = 0; i < bytesRead; i+=2) {
                    int octet1 = static_cast<int>(buffer[i]);
                    int octet2 = static_cast<int>(buffer[i+1]);
                    sid_chip.write(octet1, octet2);  
                    /*std::cout << octet1 << " " << octet2 << " ";
                    std::cout << std::endl;;
                    std::cout.flush();*/
                }                       
            }
        }
        
        audio.stopStream();
        audio.closeStream();
    } catch (RtAudioErrorType e) {
        std::cerr << "Erreur RtAudio : "  << std::endl;
        return 1;
    } catch (std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }
        std::cout << "Flux terminé. Arrêt du programme." << std::endl;
    return 0;
}