//
// Created by Nour on 16/01/2023.
//

#ifndef INC_3IF_LOG_H
#define INC_3IF_LOG_H
#include <fstream>
#include <regex>

#include "Log_Utils.h"

typedef std::string Referer;
typedef std::string DocumentRequested;
typedef std::string RegexParser;

const enum returnCodes { OK = 200 , PREMANENT_REDIRECT = 301 , TEMPORARY_REDIRECT = 302 ,
        UNAUTHORIZED = 401 , FORBIDDEN = 403 , PAGE_NOT_FOUND = 404 , INTERNAL_SERVER_ERROR = 500 ,
        NOT_IMPLEMENTED = 501 , BAD_GATEWAY = 502 , SERVICE_UNAVAILABLE = 503 , GATEWAY_TIMEOUT = 504 };

class Log {
private:
    std::string ip;
    int heureConsultation;

    Referer longReferer;
    Referer shortReferer;
    DocumentRequested documentRequested;

    int returnCode;

public:
    Log( const std::string & );
    // Mode d'emploi :
    // Constructeur pour instancier un objet Log à partir d'une ligne de texte
    // Contrat :
    // La chaine de caractères doit suivre le bon format access_log

    ~Log();


    const std::string & getIp() const;
    // Mode d'emploi:
    //

    const Referer & getLongReferer() const;
    // Mode d'emploi :
    //

    const Referer & getShortReferer() const;
    // Mode d'emploi :
    //

    const DocumentRequested & getDocumentRequested() const;
    // Mode d'emploi :
    //

    const int & getHeureConsultation() const;
    // Mode d'emploi :
    //

    int getReturnCode() const;
    // Mode d'emploi :
    //



};


#endif //INC_3IF_LOG_H
