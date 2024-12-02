#include <iostream>
#include <cmath>
#include <vector>
#include <rtaudio/RtAudio.h>
#include <resid/sid.h>
#include <cstdint>
#include <unistd.h>


SID sid_chip1;
SID sid_chip2;
SID sid_chip3;
unsigned int sample_rate = 44100;
unsigned int buffer_size = 1024;
unsigned int frame_count = 0;
double clock_accumulator = 0.0;
float panLeft1 = 1.0;
float panRight1 = 1.0;
float panLeft2 = 1.0;
float panRight2 = 1.0;
float panLeft3 = 1.0;
float panRight3 = 1.0;


// Callback audio pour RtAudio
int audioCallback(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
                  double streamTime, RtAudioStreamStatus status, void* userData) {
    float* buffer = static_cast<float*>(outputBuffer);
    
   double clocks_per_sample = 985248.0 / 44100.0; // Fréquence d'horloge / Fréquence d'échantillonnage

    for (unsigned int i = 0; i < nBufferFrames; ++i) {

        clock_accumulator += clocks_per_sample;
        while (clock_accumulator >= 1.0) {
            sid_chip1.clock();
            sid_chip2.clock();
            sid_chip3.clock();
            clock_accumulator -= 1.0;
        }
        short sid_output1 = sid_chip1.output(); 
        short sid_output2 = sid_chip2.output(); 
        short sid_output3 = sid_chip3.output(); 
        float sample1 = static_cast<float>(sid_output1) / 32768.0f;
        float sample2 = static_cast<float>(sid_output2) / 32768.0f;
        float sample3 = static_cast<float>(sid_output3) / 32768.0f;

        float sampleLeft = 0.5*((sample1 * panLeft1) + (sample2 * panLeft2) + (sample3 * panLeft3));
        float sampleRight = 0.5*((sample1 * panRight1) + (sample2 * panRight2) + (sample3 * panRight3));

        buffer[i*2] = std::max(-1.0f, std::min(sampleLeft, 1.0f));
        buffer[i*2+1] = std::max(-1.0f, std::min(sampleRight, 1.0f));
    }

    return 0;
}


int main() {
    try {
        RtAudio::Api api = RtAudio::UNIX_JACK;
        RtAudio audio(api);
        
        if (audio.getDeviceCount() < 1) {
            throw std::runtime_error("Aucun périphérique audio trouvé.");
        }
        std::cout << "API actuelle utilisée : " << RtAudio::getApiName(audio.getCurrentApi()) << std::endl;

        sid_chip1.set_sampling_parameters(985248.0, SAMPLE_RESAMPLE_INTERPOLATE, 44100.0,  -1.0, 0.97);  // Fréquence d'échantillonnage
        sid_chip2.set_sampling_parameters(985248.0, SAMPLE_RESAMPLE_INTERPOLATE, 44100.0,  -1.0, 0.97);  // Fréquence d'échantillonnage
        sid_chip3.set_sampling_parameters(985248.0, SAMPLE_RESAMPLE_INTERPOLATE, 44100.0,  -1.0, 0.97);  // Fréquence d'échantillonnage

        // Configurer RtAudio
        RtAudio::StreamParameters outputParams;
        outputParams.deviceId = audio.getDefaultOutputDevice();
        outputParams.nChannels = 2;
        outputParams.firstChannel = 0;

        RtAudio::StreamOptions options;
       /* options.flags = RTAUDIO_SCHEDULE_REALTIME;
        options.flags = RTAUDIO_NONINTERLEAVED;
        options.flags = RTAUDIO_MINIMIZE_LATENCY;*/

        // Démarrer le flux audio
        audio.openStream(&outputParams, nullptr, RTAUDIO_FLOAT32, sample_rate,
                         &buffer_size, &audioCallback, nullptr);
        audio.startStream();


        std::cout << "READY" << std::endl;

        while (true) { 
            std::vector<uint8_t> buffer(2);
            std::cin.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
            std::streamsize bytesRead = std::cin.gcount();
            if (bytesRead ==2) {
                int octet1 = static_cast<int>(buffer[0]);
                int octet2 = static_cast<int>(buffer[1]);

                if (octet1>=21 && octet1<=24) {//filtres : toutes voix
                    sid_chip1.write(octet1, octet2);  
                    sid_chip2.write(octet1, octet2);  
                    sid_chip3.write(octet1, octet2);  
                }


                if (octet1>=0 && octet1<=6) {
                    sid_chip1.write(octet1, octet2);   
                }
                else if (octet1>=7 && octet1<=13) {
                    sid_chip2.write(octet1, octet2);   
                }
                else if (octet1>=14 && octet1<=20) {
                    sid_chip3.write(octet1, octet2);   
                }
                else if (octet1 == 32) {
                    panLeft1 = static_cast<float>(octet2)/255.0;
                }
                else if (octet1 == 33) {
                    panRight1 = static_cast<float>(octet2)/255.0;
                }
                else if (octet1 == 34) {
                    panLeft2 = static_cast<float>(octet2)/255.0;
                }
                else if (octet1 == 35) {
                    panRight2 = static_cast<float>(octet2)/255.0;
                }
                else if (octet1 == 36) {
                    panLeft3 = static_cast<float>(octet2)/255.0;
                }
                else if (octet1 == 37) {
                    panRight3 = static_cast<float>(octet2)/255.0;
                }
                std::cout << octet1 << " " << octet2 << " ";
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