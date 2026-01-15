#include <jack/jack.h>
#include <iostream>
#include <vector>
#include <cmath>

jack_port_t *input_ports[4];
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


int process(jack_nframes_t nframes, void *arg) {
    float *in1 = (float *)jack_port_get_buffer(input_ports[0], nframes);
    float *in2 = (float *)jack_port_get_buffer(input_ports[1], nframes);
    float *in3 = (float *)jack_port_get_buffer(input_ports[2], nframes);
    float *in4 = (float *)jack_port_get_buffer(input_ports[3], nframes);


    
    float *out_left = (float *)jack_port_get_buffer(output_ports[0], nframes);
    float *out_right = (float *)jack_port_get_buffer(output_ports[1], nframes);

    for (jack_nframes_t i = 0; i < nframes; i++) {
        float p1 = fx(in1[i], v1_preset);
        float p2 = fx(in2[i], v2_preset);
        float p3 = fx(in3[i], v3_preset);
        float p4 = fx(in4[i], v4_preset);
        out_left[i] = p1*v1_left + p2*v2_left + p3*v3_left + p4*v4_left;
        out_right[i] = p1*v1_right + p2*v2_right + p3*v3_right + p4*v4_right;

        if (out_left[i] > 1.0f) out_left[i] = 1.0f;
        if (out_left[i] < -1.0f) out_left[i] = -1.0f;
        
        if (out_right[i] > 1.0f) out_right[i] = 1.0f;
        if (out_right[i] < -1.0f) out_right[i] = -1.0f;
        
    }

    return 0;
}

int main() {
    client = jack_client_open("mixeur", JackNullOption, NULL);
    if (!client) {
        std::cerr << "Erreur lors de l'ouverture du client JACK" << std::endl;
        return 1;
    }

    input_ports[0] = jack_port_register(client, "input1", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
    input_ports[1] = jack_port_register(client, "input2", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
    input_ports[2] = jack_port_register(client, "input3", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
    input_ports[3] = jack_port_register(client, "input4", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);

    output_ports[0] = jack_port_register(client, "output_left", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
    output_ports[1] = jack_port_register(client, "output_right", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

    jack_set_process_callback(client, process, NULL);
    
    // Activation du client
    if (jack_activate(client)) {
        std::cerr << "Impossible d'activer le client" << std::endl;
        return 1;
    }

    // Connexion automatique aux ports de sortie des instances de squareWave
    const char **ports;
    
    // Obtenir les ports disponibles pour les connexions
    ports = jack_get_ports(client, NULL, NULL, JackPortIsOutput);
    
    if (ports == NULL) {
        std::cerr << "Aucun port de sortie disponible" << std::endl;
        return 1;
    }

    // Connecter les ports d'entrée aux ports de sortie disponibles
    for (int i = 0; i < 4 && ports[i] != NULL; i++) {
        if (jack_connect(client, ports[i], jack_port_name(input_ports[i])) != 0) {
            std::cerr << "Erreur lors de la connexion des ports" << std::endl;
        }
    }



    if (jack_connect(client, jack_port_name(output_ports[0]), "system:playback_1") != 0) {
        std::cerr << "Impossible de connecter la sortie gauche.\n";
    }

    if (jack_connect(client, jack_port_name(output_ports[1]), "system:playback_2") != 0) {
        std::cerr << "Impossible de connecter la sortie droite.\n";
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
            }
        }
    }
    
    jack_client_close(client);
    return 0;
}


