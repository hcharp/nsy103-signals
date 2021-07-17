// Exercice 4-2

// Modifier le programme afin d’afficher à chaque réception du signal le PID du processus distant qui
// envoie le signal. Rajouter au programme la possibilité de rediriger le traitement de CTRL C pour écrire un message
// de fin.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


// Action effectuée lors de la réception du signal
void handle_ctrl_c (int sig) {
    printf("Signal SIGUSR1 reçu de %d\n", sig);
}


int main(int argc, char* argv[]) {
    struct sigaction sa;
    sa.sa_handler=&handle_ctrl_c; // warnings mais c'est pas grave
    sa.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &sa, NULL);

    for (int i = 0; i < 1000; i++)
    {
        printf("Hélène a tjs raison !\n");
        sleep(2);
    }
    
}