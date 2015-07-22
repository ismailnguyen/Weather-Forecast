#ifndef FONCTION_H
#define FONCTION_H

#include <pthread.h>
#include <signal.h>
#include <unistd.h>


void threadRecherche();
void gestionnaireSIGUSR1(int);


#endif // FONCTION_H
