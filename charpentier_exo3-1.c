// Exercice 3-1 

// Écrire une nouvelle version du programme 1 afin que ce dernier crée un fils qui exécute la boucle
// infinie. Le père se mettra en attente quelques secondes (commande sleep) puis enverra le signal
// SIGHUP au fils. Que constatez-vous?


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


// Action effectuée lors de la réception du signal
void action_signal (int num) {
    if (num == SIGHUP) {
    printf("Signal SIGHUP reçu\n");
    exit(EXIT_SUCCESS);
    }
}

int signalhup() {

    struct sigaction action;
    action.sa_handler=action_signal; // action_signal sera appelée
    sigemptyset(&action.sa_mask); // Aucun signal n'est ignoré
    action.sa_flags=SA_RESTART ; // Compatibilité BSD
    // Modifie l'action pour le signal SIGHUP
    if(sigaction(SIGHUP,&action, NULL)==-1) {
        printf("Impossible d'appeler sigaction\n");
        exit(EXIT_FAILURE);
        }
    while(1) {
        printf(".\n"); sleep(1);
        }

}

int main(int argc, char *argv[]) {
    
    // Créer un fils
    pid_t pid = fork(); // si ce pid est 0, c'est le fils et sinon c'est le père
    
    if (pid==0) {
        // C'est le fils qui prend la suite (code copié de l'exo 1) :
        signalhup();
    }

    // Le père se met en attente
    else {
        sleep(2);
        // Le père envoie SIGHUP au fils
        kill(0, SIGHUP);
        wait(0);
          
    }
  
}