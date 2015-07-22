#include "xml.h"
#include <iostream>
using namespace std;

XML::XML(string code) : m_code(code)
{
}

vector<XML> XML::extraireBalises(string nomElement) const
{
    vector<XML> balises;
    int position = 0, positionBaliseOuvrante, positionBaliseFermante;
    string baliseOuvrante = "<" + nomElement;
    //cout << "Extraction de " << baliseOuvrante << endl;
    while ( (positionBaliseOuvrante = m_code.find(baliseOuvrante, position)) != string::npos)
    {
        //cout << "Position balise ouvrante : " << positionBaliseOuvrante << endl;
        // Recherche s'il s'agit d'une balise vide
        positionBaliseFermante = m_code.find(">",positionBaliseOuvrante);
        if(m_code[positionBaliseFermante-1] != '/') // Ce n'est pas une balise vide
        {
            string baliseFermante = "</" + nomElement + ">";
            positionBaliseFermante = m_code.find(baliseFermante, positionBaliseOuvrante) + baliseFermante.length();

        }
        //cout << "Position balise fermante : " << positionBaliseFermante << endl;
        if(positionBaliseFermante <= positionBaliseOuvrante)
        {
            position = positionBaliseOuvrante + 1;
        }
        else
        {
            XML xml(m_code.substr(positionBaliseOuvrante, positionBaliseFermante-positionBaliseOuvrante));
            balises.push_back(xml);
            //cout << "Code XML : " << xml.getCode() << endl;
            position = positionBaliseFermante;
        }
    }
    return balises;
}


vector<string> XML::extraireDonnees(string nomElement, string nomAttribut )
{
    vector<string> donnees;
    int position = 0, positionFinBaliseOuvrante, positionBaliseOuvrante, positionBaliseFermante;
    string baliseOuvrante = "<" + nomElement;
    while ( (positionBaliseOuvrante = m_code.find(baliseOuvrante, position)) != string::npos)
    {
        // Si ce n'est pas un attribut, on renvoit le contenu entre la balise ouvrante et la balise fermante
        if(nomAttribut == "")
        {
            positionFinBaliseOuvrante = m_code.find(">",positionBaliseOuvrante);
            if(m_code[positionFinBaliseOuvrante-1] != '/') // Ce n'est pas une balise vide
            {
                baliseOuvrante = m_code.substr(positionBaliseOuvrante, positionFinBaliseOuvrante-positionBaliseOuvrante+1);
                string baliseFermante = "</" + nomElement + ">";
                positionBaliseFermante = m_code.find(baliseFermante, positionBaliseOuvrante) /*+ baliseFermante.length()*/;
                string donnee = m_code.substr(positionFinBaliseOuvrante+1, positionBaliseFermante-1-positionFinBaliseOuvrante);
                donnees.push_back(donnee);
                position = positionBaliseFermante;
            }
        }
        else
        {
            nomAttribut += "=\"";
            positionBaliseFermante = m_code.find(">",positionBaliseOuvrante);
            int positionAttribut = m_code.find(nomAttribut,positionBaliseOuvrante);
            if( (positionAttribut != string::npos) && (positionAttribut < positionBaliseFermante) )
            {
                int positionFinAttribut = m_code.find("\"",positionAttribut+nomAttribut.length());
                string donnee = m_code.substr(positionAttribut+nomAttribut.length(), positionFinAttribut-positionAttribut-nomAttribut.length());
                donnees.push_back(donnee);
                position = positionBaliseFermante;
            }
        }
    }
    return donnees;
}

const XML & XML::operator =(const XML & xml)
{
    this->m_code = xml.getCode();
    return *this;
}

