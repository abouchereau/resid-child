#include <jack/jack.h>
#include <iostream>
#include <vector>
#include <cmath>

jack_port_t *input_ports[3];
jack_port_t *output_ports[2];
jack_client_t *client;

float v1_left = 1.0f;
float v1_right = 1.0f;
float v2_left = 0.85f;
float v2_right = 0.15f;
float v3_left = 0.15f;
float v3_right = 0.85f;
float v4_left = 1.0f;
float v4_right = 1.0f;

int v1_preset = 0;
int v2_preset = 0;
int v3_preset = 0;
int v4_preset = 0;

int FACTOR_DELAY = 4;

float v1_sc = 1.0f;
float v2_sc = 1.0f;
float v3_sc = 1.0f;

float v1_calc_sidechain[10] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
float v2_calc_sidechain[10] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
float v3_calc_sidechain[10] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};

float v1_min_sidechain = 0.5f;
float v2_min_sidechain = 0.25f;
float v3_min_sidechain = 0.5f;

int v1_curve_sidechain = 3;
int v2_curve_sidechain = 3;
int v3_curve_sidechain = 3;

jack_nframes_t sampleRate = 0;
jack_nframes_t sidechain_elapsed_samples = 0;
bool sidechain_active = false;
int sidechain_iterate = -1;

float* delayBuffer = nullptr;
jack_nframes_t delaySize = 0;
jack_nframes_t writePos = 0;
jack_nframes_t delaySamples = 0;
float feedback = 0.35f;



// 1.0 = neutre, 2.0 = plus de saturation
float soft_clip(float x, float drive) {
    x = x * drive;
    if (x > 1.0f) return 1.0f;
    if (x < -1.0f) return -1.0f;
    return x - (x * x * x) / 3.0f;  // courbe douce
}

//saturate(sample, 1.5f, 0.0f);  // drive 1.5, symétrique
//saturate(sample, 2.0f, 0.1f);  // un peu asymétrique, plus chaud
//saturate(x, 1.3f, 0.0f);  //juste assez pour adoucir les bords du carré
//saturate(x, 1.8f, 0.05f);
float saturate(float x, float drive, float bias) {
    // Ajoute un bias (optionnel) pour simuler un étage asymétrique
    float z = (x + bias) * drive;
    // Courbe tanh pour saturation douce
    float y = tanhf(z);
    // Normalisation de la sortie
    return y / tanhf(drive);
}

float fx(float x, int num) {
    switch(num) {
        case 0 : return x;
        case 1 : return soft_clip(x, 1.0f);
        case 2 : return soft_clip(x, 1.5f);
        case 3 : return soft_clip(x, 2.0f);
        case 4 : return saturate(x, 1.5f, 0.0f);
        case 5 : return saturate(x, 2.0f, 0.1f);
        case 6 : return saturate(x, 1.3f, 0.0f);
        case 7 : return saturate(x, 1.8f, 0.05f);
        default: return x; // par défaut, pas de traitement
    }
}

void start_sidechain() {
    sidechain_elapsed_samples = -1;
    sidechain_active = true;
    sidechain_iterate = -1;
}



void compute_v1_calc_sidechain() {
    for (int i = 0; i < 10; ++i) {
        //calcul le sidechain à appliquer tous les 20ms 
        v1_calc_sidechain[i] = v1_min_sidechain + (1.0f - v1_min_sidechain) * (1 - std::exp(-v1_curve_sidechain * i * 20.0f  / static_cast<float>(200)));
    }
}

void compute_v2_calc_sidechain() {
    for (int i = 0; i < 10; ++i) {
        //calcul le sidechain à appliquer tous les 20ms 
        v2_calc_sidechain[i] = v2_min_sidechain + (1.0f - v2_min_sidechain) * (1 - std::exp(-v2_curve_sidechain * i * 20.0f / static_cast<float>(200)));
    }
}

void compute_v3_calc_sidechain() {
    for (int i = 0; i < 10; ++i) {
        //calcul le sidechain à appliquer tous les 20ms 
        v3_calc_sidechain[i] = v3_min_sidechain + (1.0f - v3_min_sidechain) * (1 - std::exp(-v3_curve_sidechain * i * 20.0f  / static_cast<float>(200)));
    }
}

int process(jack_nframes_t nframes, void *arg) {
    float *in1 = (float *)jack_port_get_buffer(input_ports[0], nframes);
    float *in2 = (float *)jack_port_get_buffer(input_ports[1], nframes);
    float *in3 = (float *)jack_port_get_buffer(input_ports[2], nframes);

    float *out_left  = (float *)jack_port_get_buffer(output_ports[0], nframes);
    float *out_right = (float *)jack_port_get_buffer(output_ports[1], nframes);

    for (jack_nframes_t i = 0; i < nframes; i++) {

        // --- Voix dry ---
        float dry = fx(in1[i], v1_preset);
        float p2  = fx(in2[i], v2_preset);
        float p3  = fx(in3[i], v3_preset);

        // --- Lecture delay ---
        jack_nframes_t readPos = (writePos + delaySize - delaySamples) % delaySize;

        float delayed = delayBuffer[readPos];

        // --- Écriture delay (avec feedback) ---
        delayBuffer[writePos] = dry + delayed * feedback;

        writePos = (writePos + 1) % delaySize;

        float p4 = delayed;//fx(delayed, v4_preset);

        if (sidechain_active) {
            sidechain_elapsed_samples++;
            //TODO calculer le 882 en fonction du sample rate pour que ça soit plus universel
            if (sidechain_elapsed_samples % 882 == 0) {
                sidechain_iterate++;
                if (sidechain_iterate >= 10) {
                    sidechain_active = false;
                    v1_sc = 1.0f;
                    v2_sc = 1.0f;
                    v3_sc = 1.0f;
                }
            } else {
                if (sidechain_iterate >= 0 && sidechain_iterate < 10) {
                    v1_sc = v1_calc_sidechain[sidechain_iterate];
                    v2_sc = v2_calc_sidechain[sidechain_iterate];
                    v3_sc = v3_calc_sidechain[sidechain_iterate];
                }
            }
        }

        // --- Mix ---
        float left =
            dry * v1_left * v1_sc +
            p2  * v2_left * v2_sc +
            p3  * v3_left * v3_sc +
            p4  * v4_left * v1_sc;

        float right =
            dry * v1_right * v1_sc +
            p2  * v2_right * v2_sc +
            p3  * v3_right * v3_sc +
            p4  * v4_right * v1_sc;

        // --- Clamp ---
        out_left[i]  = std::max(-1.0f, std::min(1.0f, left));
        out_right[i] = std::max(-1.0f, std::min(1.0f, right));
    }

    return 0;
}


int main() {
    client = jack_client_open("mixeur", JackNullOption, NULL);
    if (!client) {
        std::cout << "Erreur lors de l'ouverture du client JACK" << std::endl;
        return 1;
    }

 
    input_ports[0] = jack_port_register(client, "input1", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
    input_ports[1] = jack_port_register(client, "input2", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
    input_ports[2] = jack_port_register(client, "input3", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
    //input_ports[3] = jack_port_register(client, "input4", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);

    output_ports[0] = jack_port_register(client, "output_left", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
    output_ports[1] = jack_port_register(client, "output_right", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

    jack_set_process_callback(client, process, NULL);

    sampleRate = jack_get_sample_rate(client);
    delaySamples = (sampleRate * 300) / 1000;
    delaySize = sampleRate * 2;
    delayBuffer = new float[delaySize];
    std::fill(delayBuffer, delayBuffer + delaySize, 0.0f);

    // ---- MAINTENANT seulement ----
    if (jack_activate(client)) {
        std::cout << "Impossible d'activer le client" << std::endl;
        return 1;
    }

   // Connexion automatique aux ports de sortie des instances de squareWave
    const char **ports;

    // Obtenir les ports disponibles pour les connexions
    ports = jack_get_ports(client, NULL, NULL, JackPortIsOutput);
    
    if (ports == NULL) {
        std::cout << "Aucun port de sortie disponible" << std::endl;
        return 1;
    }
    // Connecter les ports d'entrée aux ports de sortie disponibles
    for (int i = 0; i < 3 && ports[i] != NULL; i++) {
        if (jack_connect(client, ports[i], jack_port_name(input_ports[i])) != 0) {
            std::cout << "Erreur lors de la connexion des ports" << std::endl;
        }
    }


    if (jack_connect(client, jack_port_name(output_ports[0]), "system:playback_1") != 0) {
        std::cout << "Impossible de connecter la sortie gauche.\n";
    }

    if (jack_connect(client, jack_port_name(output_ports[1]), "system:playback_2") != 0) {
        std::cout << "Impossible de connecter la sortie droite.\n";
    }
    
    std::cout << "READY" << std::endl;

    while (true) { 
        std::vector<uint8_t> buffer(2);
        std::cin.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
        std::streamsize bytesRead = std::cin.gcount();
        if (bytesRead ==2) {
            int octet1 = static_cast<int>(buffer[0]);
            int octet2 = static_cast<int>(buffer[1]); 
        //    std::cout << octet1 << ":" << octet2 << ", ";
            switch(octet1) {
                case 1: v1_left =  static_cast<float>(octet2)/255.0f;break;
                case 2: v1_right = static_cast<float>(octet2)/255.0f;break;
                case 3: v2_left =  static_cast<float>(octet2)/255.0f;break;
                case 4: v2_right = static_cast<float>(octet2)/255.0f;break;
                case 5: v3_left =  static_cast<float>(octet2)/255.0f;break;
                case 6: v3_right = static_cast<float>(octet2)/255.0f;break;
                case 7: v4_left =  static_cast<float>(octet2)/255.0f;break;
                case 8: v4_right = static_cast<float>(octet2)/255.0f;break;
                case 9 : v1_preset = static_cast<int>(octet2);break;
                case 10 : v2_preset = static_cast<int>(octet2);break;
                case 11 : v3_preset = static_cast<int>(octet2);break;
                case 12 : v4_preset = static_cast<int>(octet2);break;
                case 13: delaySamples = (jack_get_sample_rate(client) * octet2 * FACTOR_DELAY) / 1000; break;
                case 14: start_sidechain(); break;
                case 15: v1_min_sidechain = static_cast<float>(octet2) / 100.0f;compute_v1_calc_sidechain(); break;
                case 16: v2_min_sidechain = static_cast<float>(octet2) / 100.0f;compute_v2_calc_sidechain(); break;
                case 17: v3_min_sidechain = static_cast<float>(octet2) / 100.0f;compute_v3_calc_sidechain(); break;
                case 18: v1_curve_sidechain = static_cast<int>(octet2);compute_v1_calc_sidechain(); break;
                case 19: v2_curve_sidechain = static_cast<int>(octet2);compute_v2_calc_sidechain(); break;
                case 20: v3_curve_sidechain = static_cast<int>(octet2);compute_v3_calc_sidechain(); break;
            }
        }
    }
    
    jack_client_close(client);
    return 0;
}


