//
// Created by Nour on 16/01/2023.
//

#ifndef INC_3IF_LOG_H
#define INC_3IF_LOG_H
#include <fstream>
#include <regex>

typedef std::string Referer;
typedef std::string DocumentRequested;
typedef std::string RegexParser;

class Log {
private:
    std::string ip;

    Referer referer;

private:
    DocumentRequested documentRequested;

    std::regex logFormat;


public:
    Log( const std::string & );
    // Mode d'emploi :
    // Constructeur pour instancier un objet Log à partir d'une ligne de texte
    // Contrat :
    // La chaine de caractères doit suivre le bon format access_log

    ~Log();

    const std::string &getIp() const;
    // Mode d'emploi:
    //

    const Referer &getReferer() const;
    // Mode d'emploi :
    //

    const DocumentRequested &getDocumentRequested() const;
    // Mode d'emploi :
    //

};


#endif //INC_3IF_LOG_H
