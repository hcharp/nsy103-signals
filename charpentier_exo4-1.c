// Exercice 4-1

// Écrire un programme qui redirige le traitement de SIGUSR1, affiche un message à chaque réception
// du signal par un autre processus et permet de s’arrêter en tapant CTRL C.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Action effectuée lors de la réception du signal
void action_signal (int num) { 
    if (num == SIGUSR1) {
    printf("Signal SIGUSR1 reçu\n");
    exit(EXIT_SUCCESS); //<-- si commenté, il ne se quitte pas, mais affiche juste le msg :-)
    }
}

int main(int argc, char *argv[]) {
    struct sigaction action;
    action.sa_handler=action_signal; // action_signal sera appelée
    sigemptyset(&action.sa_mask); // Aucun signal n'est ignoré
    action.sa_flags=SA_RESTART ; // Compatibilité BSD

    // Modifie l'action pour le signal SIGUSR1
    if(sigaction(SIGUSR1,&action, NULL)==-1) {
        printf("Impossible d'appeler sigaction\n");
        exit(EXIT_FAILURE);
        }


    while(1) {
        printf(".\n"); sleep(1);
        }
}