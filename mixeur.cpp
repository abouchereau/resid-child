#include <jack/jack.h>
#include <iostream>
#include <vector>

jack_port_t *input_ports[3];
jack_port_t *output_ports[2];
jack_client_t *client;

float v1_left = 1.0f;
float v1_right = 1.0f;
float v2_left = 0.85f;
float v2_right = 0.15f;
float v3_left = 0.15f;
float v3_right = 0.85f;

int process(jack_nframes_t nframes, void *arg) {
    float *in1 = (float *)jack_port_get_buffer(input_ports[0], nframes);
    float *in2 = (float *)jack_port_get_buffer(input_ports[1], nframes);
    float *in3 = (float *)jack_port_get_buffer(input_ports[2], nframes);
    
    float *out_left = (float *)jack_port_get_buffer(output_ports[0], nframes);
    float *out_right = (float *)jack_port_get_buffer(output_ports[1], nframes);

    for (jack_nframes_t i = 0; i < nframes; i++) {
        out_left[i] = in1[i] * v1_left + in2[i] * v2_left + in3[i] * v3_left; // Mixage gauche
        out_right[i] = in1[i] * v1_right + in2[i] * v2_right + in3[i] * v3_right; // Mixage droite
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
    for (int i = 0; i < 3 && ports[i] != NULL; i++) {
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
            switch(octet1) {
                case 1: v1_left =  static_cast<float>(octet2)/255.0f;break;
                case 2: v1_right = static_cast<float>(octet2)/255.0f;break;
                case 3: v2_left =  static_cast<float>(octet2)/255.0f;break;
                case 4: v2_right = static_cast<float>(octet2)/255.0f;break;
                case 5: v3_left =  static_cast<float>(octet2)/255.0f;break;
                case 6: v3_right = static_cast<float>(octet2)/255.0f;break;
            }
        }
    }
    
    jack_client_close(client);
    return 0;
}