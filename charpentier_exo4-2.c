// Exercice 4-2

// Modifier le programme afin d’afficher à chaque réception du signal le PID du processus distant qui
// envoie le signal. Rajouter au programme la possibilité de rediriger le traitement de CTRL C pour écrire un message
// de fin.



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Action effectuée lors de la réception du signal
void action_signal (int num, siginfo_t *expediteur) {

    // int(exp);
    if (num == SIGUSR1) {
    printf("Signal SIGUSR1 reçu de %d\n", expediteur->si_pid);

    }
}

int main(int argc, char *argv[]) {
    struct sigaction action;
    action.sa_handler=action_signal; // warnings mais c'est pas grave
    sigemptyset(&action.sa_mask); // Aucun signal n'est ignoré
    action.sa_flags=SA_RESTART ; // Compatibilité BSD
    action.sa_flags=SA_SIGINFO ; // <---- /!\ 

    // Modifie l'action pour le signal SIGUSR1
    if(sigaction(SIGUSR1,&action, NULL)==-1) {
        printf("Impossible d'appeler sigaction\n");
        exit(EXIT_FAILURE);
        }
    while(1) {
        printf(".\n"); sleep(1);
        }
}