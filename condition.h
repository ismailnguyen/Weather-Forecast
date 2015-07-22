#ifndef CONDITION_H
#define CONDITION_H

#include <string>
using namespace std;

typedef struct {
    string description;
    string iconeAPI;       // Chemin de l'icône sur le serveur de google
    string iconeLocale;     // Chemin de l'icône locale
    float temperature;
    string humidite;
    string vent;

}ConditionActuelle;


typedef struct {
    string jour;
    string description;
    string iconeAPI;
    string iconeLocale;
    float temperatureMin;
    float temperatureMax;
}ConditionAVenir;

#endif // CONDITION_H
