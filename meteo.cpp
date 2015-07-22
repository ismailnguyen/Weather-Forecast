#include "meteo.h"

#ifdef __unix__
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
#elif _WIN32 || _WIN64
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
#endif

#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

// Initialisation des attributs de cette manière uniquement dans le constructeur
Meteo::Meteo()
{

#ifdef _WIN32 || _WIN64
       WSADATA wsa;
       int err = WSAStartup(MAKEWORD(2, 0), &wsa);
       if(err < 0)
       {
           // Gestion des erreurs ...
           printf ("Echec sur WSAStartup !\n");
           return 0;
       }
#endif

}

void Meteo::rechercher()
{
    // Supression des résultats précédents
    m_villeObtenue.clear();
    m_paysObtenu.clear();
    m_conditionAVenir.clear();

    int retour;

    /***** Préparation du nom de la ville : les espaces sont remplacés par le caractère HTML correspondant *****/
    retour = this->preparerNomVille();
    if(retour != 0)
            return;


    /***** Récupération du fichier XML sur le serveur de l'API *****/
    retour = this->telechargerCodeXML();
    if(retour != 0)
        return;

    /***** Extraction du code XML ******/
    retour = this->extraireDonneesXML();
    if(retour != 0)
        return ;

    /***** Récupération des icônes sur le serveur de l'API si nécessaire *****/
    retour = this->telechargerIcones();
    if(retour != 0 )
        return ;


}

int Meteo::preparerNomVille()
{
    // Préparation de la ville (on remplace tous les caractères ' ' (espaces) par des '_')
    int positionEspace = 0;
    while ( (positionEspace = m_villeDemandee.find(' ', positionEspace)) != string::npos )
    {
        m_villeDemandee.replace(positionEspace, 1, "_");
    }
#ifdef MONDEBUG
    cout << endl;
    cout << "Ville demandée après préparation : " << m_villeDemandee << endl;
#endif
    return 0;

}

int Meteo::telechargerCodeXML()
{
    // Déclaration de la socket TCP Cliente -> serveur API
    int socketClienteAPI;
    // Création de la socket TCP
    socketClienteAPI = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(socketClienteAPI == -1)
    {
        m_etat = ERR_SOCK_CREATE;
        cout << endl << "ERR_SOCK_CREATE" << endl;
        return -1;
    }
    // Recherche de l'adresse IP du serveur de l'API
    char * hostName = "api.wunderground.com";
    struct hostent * host = NULL;
    host = gethostbyname(hostName);
    if(host == NULL)
    {
        cout << "Nom de domaine introuvable..." << endl;
        m_etat = ERR_SOCK_DOMAIN;
        return -1;
    }
    // Connexion au serveur
    struct sockaddr_in serveurAPIWeather;
    serveurAPIWeather.sin_family = AF_INET;
    serveurAPIWeather.sin_addr.s_addr = *(u_long *) host->h_addr;
    serveurAPIWeather.sin_port = htons(80);

    int resultat = connect(socketClienteAPI, (const struct sockaddr *)
    &serveurAPIWeather, sizeof(serveurAPIWeather));
    if(resultat != 0)
    {
        m_etat = ERR_SOCK_CONNECT;
        cout << endl << "ERR_SOCK_CONNECT" << endl;
        return -1;
    }

    // Emission de la requête HTTP de récupération du fichier XML et test
    string requete = "GET /api/889e077d2a8b9fe5/geolookup/conditions/forecast/lang:FR/q/"+m_villeDemandee+".xml HTTP/1.1\r\nHost: api.wunderground.com\r\nX-Target-URI: http://api.wunderground.com\r\nConnection: Keep-Alive\r\n\r\n";
    resultat = send(socketClienteAPI, requete.c_str(), requete.length(), 0);
    if(resultat != requete.length())
    {
        m_etat = ERR_SOCK_SEND;
        cout << endl << "ERR_SOCK_SEND" << endl;
        return -1;
    }
    // Réception du fichier XML
    string codeXML = "";

    char bufferReception[3000];

    int nbLectureRecv = 0;

    int nbOctetsLus = 0;

    int nbOctetsEnteteHTTP = 0;

    int contentLength = 0;

    do
    {

        resultat = recv(socketClienteAPI, bufferReception, 3000, 0);

        nbOctetsLus += resultat;

        nbLectureRecv++;


#ifdef MONDEBUG

        cout << "Taille de la trame reçue : " << resultat << endl;

        cout << "Taille totale : " << nbOctetsLus << endl;

#endif

        if(resultat > 0)

            codeXML.append(bufferReception, resultat);

        if(nbLectureRecv == 1)

        {

            // recherche de "Content-Lenght"

            string strToFind = "Content-Length: ";

            int pos = codeXML.find(strToFind) + strToFind.length();

            while(codeXML[pos]>='0' && codeXML[pos]<='9')

            {

                contentLength = contentLength * 10 + (codeXML[pos] - '0');

                pos++;

            }

            cout << "Content-Length : " << contentLength << " octets." << endl;

            // recherche de la fin de l'entête HTTP

            strToFind = "\r\n\r\n";

            nbOctetsEnteteHTTP = codeXML.find(strToFind) + strToFind.length();

            cout << "Taille de l'entête HTTP : " << nbOctetsEnteteHTTP << " octets" << endl;

        }


#ifdef MONDEBUG

        //cout << "Resultat : " << resultat << endl;

        //cout << "Message recu : " << codeXML << endl;

#endif


    }while( ((nbOctetsLus-nbOctetsEnteteHTTP) < contentLength) && (resultat > 0) );

        if(codeXML.length() <= 0)
        {
            m_etat = ERR_SOCK_RECV;
            cout << endl << "ERR_SOCK_RECV" << endl;
            return -1;
        }

    m_XMLDescription.setCode(codeXML);
    return 0;

}


int Meteo::extraireDonneesXML()
{
    // On vérifie que la balise ouvrante et fermante 'response' est bien présente
    vector<XML> balises = m_XMLDescription.extraireBalises("response");
    if(balises.size() != 1)
    {
        m_etat = ERR_XML_RESPONSE;
        return -1;
    }


    m_XMLDescription = balises[0];

    // Récupération des villes obtenues si plusieurs choix sont possibles
    balises = m_XMLDescription.extraireBalises("results");
    if(balises.size() == 1)
    {
        cout << "Erreur de nom de ville" << endl;
        m_villeObtenue = balises[0].extraireDonnees("city");
        m_paysObtenu = balises[0].extraireDonnees("country_name");
        m_etat = OK_XML_CITIES;
        return 1;
    }

    // Récupération de l'observation courante
    vector<XML> courant = m_XMLDescription.extraireBalises("current_observation");
    if(courant.size() != 1)
    {
        m_etat = ERR_XML_CURRENT;
        return -1;
    }
    vector<XML> lieu = courant[0].extraireBalises("display_location");
    if(lieu.size() != 1)
    {
        m_etat = ERR_XML_LOCATION;
        return -1;
    }
    m_villeObtenue = lieu[0].extraireDonnees("city");
    m_paysObtenu = lieu[0].extraireDonnees("state_name");

    // Extraction des données des conditions courantes :
    m_conditionActuelle.description = courant[0].extraireDonnees("weather")[0];
    m_conditionActuelle.humidite = courant[0].extraireDonnees("relative_humidity")[0];
    m_conditionActuelle.iconeAPI = courant[0].extraireDonnees("icon_url")[0];
    m_conditionActuelle.iconeLocale = "images/" + extraireNomFichier(m_conditionActuelle.iconeAPI);

    stringstream ss;
    ss << courant[0].extraireDonnees("temp_c")[0];
    ss >> m_conditionActuelle.temperature;
    m_conditionActuelle.vent = courant[0].extraireDonnees("wind_kph")[0] + "km.h-1 (" + courant[0].extraireDonnees("wind_dir")[0] + ")";

    // Récupération des prévisions
    vector<XML> previsionTextuelle = m_XMLDescription.extraireBalises("simpleforecast");
    if(previsionTextuelle.size() != 1) // Pas de prévision météo
    {
        m_etat = ERR_XML_SIMPLEFORECAST;
        return -1;
    }

    vector<XML> prevision = previsionTextuelle[0].extraireBalises("forecastday");
    cout << "Nombre de prevision : " << prevision.size() << endl;

    for(int i = 0 ; i < prevision.size() ; i++)
    {
        ConditionAVenir c;
        c.jour = prevision[i].extraireDonnees("day")[0] + "/" + prevision[i].extraireDonnees("month")[0] + "/" + prevision[i].extraireDonnees("year")[0];
        c.description = prevision[i].extraireDonnees("conditions")[0];
        c.iconeAPI = prevision[i].extraireDonnees("icon_url")[0];
        c.iconeLocale = "images/" + extraireNomFichier(c.iconeAPI);

        stringstream smin;

        smin << prevision[i].extraireBalises("low")[0].extraireDonnees("celsius")[0];
        cout << "smin : " << smin.str() << endl;
        smin >> c.temperatureMin;
        stringstream smax;
        smax << prevision[i].extraireBalises("high")[0].extraireDonnees("celsius")[0];
        smax >> c.temperatureMax;

        cout << "Temperature min : " << c.temperatureMin << endl << "Temperature max : " << c.temperatureMax << endl;

        m_conditionAVenir.push_back(c);
    }

    m_etat = OK_XML_FORECAST;
    return 0;

}


int Meteo::telechargerIcones()
{
    /***** Récupération des icônes si nécessaire *****/
    // Vérification de la présence des icônes dans le répertoire et téléchargement sinon.
    cout << m_conditionAVenir.size() << endl;
    string cheminIconeAPI;
    string cheminIconeLocale;

    string requete;
    int resultat;
    char bufferReception[3000];

    for(int j=0 ; j <= m_conditionAVenir.size() ; j++)
    {
        //cout << "Coucou" << endl;
        if(j == m_conditionAVenir.size() )
        {
            cheminIconeAPI = m_conditionActuelle.iconeAPI;
            cheminIconeLocale = m_conditionActuelle.iconeLocale;
        }
        else
        {
            cheminIconeAPI = m_conditionAVenir[j].iconeAPI;
            cheminIconeLocale = m_conditionAVenir[j].iconeLocale;
        }
        cout << "Chemin de l'icone : " << cheminIconeAPI << endl;
        ifstream iconeLecture(cheminIconeLocale.c_str(), ios_base::in | ios_base::binary);

        if(!iconeLecture.is_open())
        {

            // Création de la socket de connexion au serveur Image
            int debutNomServeur =  cheminIconeAPI.find("http://") + 7;
            int finNomServeur = cheminIconeAPI.find("/", debutNomServeur);
            string nomServeur = cheminIconeAPI.substr(debutNomServeur, finNomServeur-debutNomServeur);

            int socketClienteIcone = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if(socketClienteIcone == -1)
            {
                cout << "Creation de la socket impossible... " << endl;
                return -1;
            }
#ifdef MONDEBUG
            cout <<"Création de la socket : OK" << endl;
#endif

            // Recherche de l'adresse IP du serveur de Google
            //char * hostName = nomServeur.c_str();
            cout << "Nom du domaine : " << nomServeur << endl;
            struct hostent * host = NULL;
            host = gethostbyname(nomServeur.c_str());
            if(host == NULL)
            {
                cout << "Nom de domaine  introuvable..." << endl;
                return -2;
            }

            // Connexion au serveur et test
            struct sockaddr_in serveurIcone;
            serveurIcone.sin_family = AF_INET;
            serveurIcone.sin_addr.s_addr = *(u_long *) host->h_addr;
            //serveurGoogleAPI.sin_addr.in_addr.s_addr = inet_addr("173.194.67.94");
            serveurIcone.sin_port = htons(80);
#ifdef MONDEBUG
            cout << "Adresse IP de " << nomServeur.c_str() << " : " << inet_ntoa(serveurIcone.sin_addr) << endl;
#endif
            int resultat = connect(socketClienteIcone, (const struct sockaddr *) &serveurIcone, sizeof(serveurIcone));
            if(resultat != 0)
                return -2;
#ifdef MONDEBUG
            cout << "Connexion à " << nomServeur.c_str() << " : OK" << endl;
#endif

            // Emission de la requête HTTP de récupération du fichier XML et test
            string requete = "GET " + cheminIconeAPI.substr(finNomServeur, cheminIconeAPI.length()-finNomServeur) + " HTTP/1.1\r\nHost: " + nomServeur + "\r\n\r\n";
            cout << "Requete : " << requete << endl;
            resultat = send(socketClienteIcone, requete.c_str(), requete.length(), 0);
            if(resultat != requete.length())
                return -3;

            char bufferReception[3000];
            resultat = recv(socketClienteIcone, bufferReception, 3000, 0);
            //cout << "Taille de l'image : " << resultat << endl << bufferReception << endl;
            string codeImage(bufferReception, resultat);
            //cout << "Taille de la string : " << codeImage.size() << endl;
            if(codeImage.find("HTTP/1.1 200 OK") >= 0)
            {
                // Récupération de la taille du fichier
                int positionContentLength = codeImage.find("Content-Length: ");
                int positionFinContentLength = codeImage.find("\r\n", positionContentLength);
                stringstream ss (codeImage.substr(positionContentLength+16, positionFinContentLength-positionContentLength-16));
                int taille;
                ss >> taille;
                cout << "Content-Length : " << taille << endl;
                int finEntete = codeImage.find("\r\n\r\n");
                //cout << "Fin entete : " << finEntete << endl;
                //cout << bufferReception[finEntete+4] << endl;
                ofstream iconeEcriture(cheminIconeLocale.c_str(), ios_base::out | ios_base::binary);
                iconeEcriture.write(&(bufferReception[finEntete+4]), resultat-finEntete-4);
                int tailleActuelle = resultat-finEntete-4;
                cout << "Taille actuelle : " << tailleActuelle << endl;
                while(tailleActuelle < taille)
                {
                    resultat = recv(socketClienteIcone, bufferReception, 3000, 0);
                    iconeEcriture.write(bufferReception, resultat);
                    tailleActuelle += resultat;
                }
                iconeEcriture.close();


                #ifdef __unix__
                    resultat = close(socketClienteIcone);
                #elif _WIN32 || _WIN64
                    resultat = closesocket(socketClienteIcone);
                    WSACleanup();
                #endif

            }

        }
        iconeLecture.close();
    }


    // Fermeture de la socket et test


    return 0;

}


string Meteo::extraireNomFichier(string chemin)
{
    int lastSlash = chemin.find_last_of("/");
    return chemin.substr(lastSlash+1, chemin.length()-lastSlash-1);
}


