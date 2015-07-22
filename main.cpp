#include <QtGui/QApplication>
#include "dialog.h"
#include "meteo.h"
#include "fonction.h"
#include <stdio.h>
#include <iostream>
#include "fonction.h"
#include <string.h>

using namespace std;
Dialog * ptr_w;
Meteo * m ;

int numThreadPrincipale = pthread_self();

int main(int argc, char *argv[])
{

     m = new Meteo ;

    if( signal(SIGUSR1, gestionnaireSIGUSR1) == SIG_ERR)
    {
        cout << "Impossible de mettre en place le gestionnaire..." << endl;
        return -1;
    }

    QApplication a(argc, argv);
    Dialog w;



    w.show();
    ptr_w = &w ;

    return a.exec();
}

void threadRecherche()
{
    m->rechercher();

    pthread_kill(numThreadPrincipale, SIGUSR1);

    pthread_exit(NULL);

}


void gestionnaireSIGUSR1(int)
{
    cout << "Réception d'un signal SIGUSR1..." << endl;
    ptr_w->afficherMeteo();
}
