#include <jack/jack.h>
#include <cmath>
#include <iostream>
#include <resid/sid.h>
#include <vector>
#include <cstdint>
#include <unistd.h>
#include <string>
using namespace std;

jack_port_t *output_port;
jack_client_t *client;

SID sid_chip;

//paramètres par défaut
double NB_CLOCKS_PER_SECOND = 985248.0;//PAL // 1022727.0 //NTSC
double SAMPLE_FRAME = 44100.0;
double BUFFER = 128.0;

double NB_CLOCKS = NB_CLOCKS_PER_SECOND / SAMPLE_FRAME;//22.34122..

double accumulator = 0.0;

//nframes == buffer (128, ...1024)
int process(jack_nframes_t nframes, void *arg) {
    float *buffer = (float *)jack_port_get_buffer(output_port, nframes);
    
    for (jack_nframes_t i = 0; i < nframes; i++) {
        accumulator += NB_CLOCKS;
        while(accumulator>=1.0) {//des fois 22, des fois 23
            sid_chip.clock();            
            accumulator -= 1.0;
        }

        short sid_output = sid_chip.output(); 
        float sample = static_cast<float>(sid_output) / 32768.0f;
        buffer[i] = sample;
    }
    return 0;
}


int main(int argc, char* argv[]) {

    if (argc>1) {
        SAMPLE_FRAME = stod(argv[1]);
    }

    if(argc>2) {
        BUFFER = stod(argv[2]);
    }

    if(argc>3) {
        NB_CLOCKS_PER_SECOND = stod(argv[3]);
    }

    NB_CLOCKS = NB_CLOCKS_PER_SECOND / SAMPLE_FRAME;

    client = jack_client_open("sidVoice", JackNullOption, NULL);
    if (!client) {
        std::cerr << "Erreur lors de l'ouverture du client JACK" << std::endl;
        return 1;
    }

    sid_chip.set_sampling_parameters(NB_CLOCKS_PER_SECOND, SAMPLE_FAST, SAMPLE_FRAME,  -1.0, 0.97);  // Fréquence d'échantillonnage
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


//TODO essayer avec d'autres Sample PARAMETES


/*
Dans la bibliothèque ReSID, le paramètre sampling_method détermine la manière dont l'émulation du son est échantillonnée pour générer des blocs audio à un taux d'échantillonnage spécifique (par exemple, 44,1 kHz ou 48 kHz). Voici une explication détaillée des options disponibles, ainsi que leur impact sur les performances et la qualité sonore.
1. SAMPLE_FAST

    Description :
        C'est la méthode la plus simple et la plus rapide.
        Elle génère des échantillons en prenant l'état instantané du signal audio émulé à intervalles fixes.
        Aucune interpolation ou traitement supplémentaire n'est appliqué.

    Avantages :
        Très rapide et peu gourmand en ressources CPU.
        Idéal pour les systèmes à faible performance ou lorsqu'une qualité sonore élevée n'est pas nécessaire.

    Inconvénients :
        La qualité audio peut être médiocre, avec des artefacts audibles, en particulier à des fréquences d'échantillonnage faibles.

2. SAMPLE_INTERPOLATE

    Description :
        Applique une interpolation linéaire entre les échantillons.
        Améliore la qualité sonore par rapport à SAMPLE_FAST.

    Avantages :
        Meilleure qualité sonore que SAMPLE_FAST.
        Toujours relativement rapide.

    Inconvénients :
        La qualité reste limitée par l'algorithme d'interpolation linéaire, ce qui peut laisser des artefacts perceptibles pour des sons complexes.

3. SAMPLE_RESAMPLE_INTERPOLATE

    Description :
        Utilise un algorithme avancé de rééchantillonnage avec interpolation linéaire.
        Adapte les échantillons du SID (cadencés à l'horloge du C64) à la fréquence d'échantillonnage spécifiée (par exemple, 44,1 kHz).

    Avantages :
        Significativement meilleure qualité audio que les deux méthodes précédentes.
        Diminue les artefacts audibles, surtout à des fréquences d'échantillonnage modernes.

    Inconvénients :
        Plus exigeant en termes de performances CPU que SAMPLE_FAST ou SAMPLE_INTERPOLATE.

4. SAMPLE_RESAMPLE_FAST

    Description :
        Utilise un rééchantillonnage rapide sans interpolation avancée.
        Un compromis entre la simplicité de SAMPLE_FAST et la qualité de SAMPLE_RESAMPLE_INTERPOLATE.

    Avantages :
        Plus rapide que SAMPLE_RESAMPLE_INTERPOLATE.
        Bonne qualité sonore pour des configurations nécessitant un compromis entre qualité et performances.

    Inconvénients :
        Qualité sonore inférieure à SAMPLE_RESAMPLE_INTERPOLATE pour les sons complexes.*/


