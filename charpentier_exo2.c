// Exercice 2

// Écrire un programme qui puisse envoyer le signal SIGHUP au programme de l’exercice 1. On
// cherchera le PID du programme de l’exercice 1 (avec la commande ps) et on lancera le programme
// de l’exercice 2 de la façon suivante: ./exo2 PID.

// Penser à la fonction atoi pour traduire de ASCII en integer


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


int main(int argc, char *argv[]) {
    int pid = atoi(argv[1]);
    // ARGUMENTS ÉCRITS PAR L'UTILISATEUR LORS DE L'APPEL EN LIGNE DE COMMANDE !!! DEDIOU !!!
    // argv[0] : nom du programme
    // exec : recouvrir un processus avec un autre programme qui existe déjà et que l'on met dedans
    // le premier sait le nom de l'autre puis il y met des paramètres
    // voir le cours C
    // argc : donne le nombre d'éléments de la ligne de commandes
    // argv : valeurs dans ces éléments
    kill(pid, SIGHUP);

}
