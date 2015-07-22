#ifndef METEO_H
#define METEO_H

//#define MONDEBUG

#include "condition.h"
#include "xml.h"
#include <string>
using namespace std;

class Meteo
{
public:

    typedef enum {OK_XML_CITIES=0, OK_XML_FORECAST, ERR_SOCK_CREATE,
                  ERR_SOCK_DOMAIN, ERR_SOCK_CONNECT, ERR_SOCK_SEND,
                  ERR_SOCK_RECV, ERR_XML_RESPONSE, ERR_XML_CURRENT,
                  ERR_XML_LOCATION, ERR_XML_SIMPLEFORECAST } Etat;

    Meteo();
    void rechercher();

    // Méthodes d'accès
    inline vector<string> getVilleObtenue() const {return m_villeObtenue;}
    inline vector<string> getPaysObtenu() const {return m_paysObtenu;}
    inline const XML & getXMLDescription() const  {return m_XMLDescription;}
    inline ConditionActuelle getConditionActuelle() const {return m_conditionActuelle;}
    inline ConditionAVenir getConditionAVenir(int jour) {return m_conditionAVenir[jour];}
    inline int getNombrePrevision() {return m_conditionAVenir.size(); }
    inline Etat getEtat() const {return m_etat;}
    inline void setVilleDemandee(string villeDemandee) {m_villeDemandee = villeDemandee;}

private:
    // La ville de la recherche
    string m_villeDemandee;
    // La ou les villes obtenues et le ou les pays respectifs
    vector<string> m_villeObtenue;
    vector<string> m_paysObtenu;
    // La description XML de la météo de la ville
    XML m_XMLDescription;
    // Les conditions actuelles et les prévisions
    ConditionActuelle m_conditionActuelle;
    vector<ConditionAVenir> m_conditionAVenir;

    // Indique l'état de la recherche
    Etat m_etat;

    // Extraction du nom du fichier à partir de son chemin
    string extraireNomFichier(string chemin);
    // Récupération du fichier XML
    int telechargerCodeXML();
    // Extraction des données XML
    int extraireDonneesXML();
    // Récupération des icônes si necessaire
    int telechargerIcones();
    // Préparation du nom de la ville
    int preparerNomVille();

};

#endif // PREVISIONMETEO_H
