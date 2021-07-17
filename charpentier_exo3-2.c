// Exercice 3-2 

// Puis faire l’inverse, c’est-à-dire que le père crée un fils puis exécute la boucle infinie et le fils se
// met en attente quelques secondes et envoie le signal SIGHUP.
// Que constatez-vous?


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
    
    if (pid!=0) {
        // C'est le père qui prend la suite (code copié de l'exo 1) :
        signalhup();
    }

    // Le père se met en attente
    else {
        pid_t parentid = getppid();
        sleep(5);
        // Le fils envoie SIGHUP au père
        kill(parentid, SIGHUP);
        // wait(0); // impossible pour un fils !
        // attention : lorsqu'un fils tue son père, on ne sait plus ce qu'il fait derrière
        // dangereux dans le cas de prog sur avion, drone, etc...
        // envoie des informations qui ne seront pas reçues
        // (zombie)
        // attention proc père et fils : il ne faut jamais qu'un processus soit ORPHELIN !
          
    }
  
}