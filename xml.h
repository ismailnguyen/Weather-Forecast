#ifndef XML_H
#define XML_H

#include <string>
#include <vector>
using namespace std;

class XML
{
public:
    XML(string code = "");
    void setCode(string code) {m_code = code;}
    string getCode() const {return m_code;}
    vector<XML> extraireBalises(string nomElement) const;
    vector<string> extraireDonnees(string nomElement, string nomAttribut = "");
    const XML & operator=(const XML & xml);

private:
    string m_code;
};

#endif // XML_H
