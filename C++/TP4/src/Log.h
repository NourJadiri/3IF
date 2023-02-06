/*************************************************************************
                           Log  -  description
                             -------------------
    début                : 16/01/2023
    copyright            : (C) 2023 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Log> (fichier Log.h) ----------------
#if ! defined ( LOG_H )
#define LOG_H

//--------------------------------------------------- Interfaces utilisées
#include <fstream>
#include <regex>
#include "Log_Utils.h"

//------------------------------------------------------------------ Types
typedef std::string Referer;
typedef std::string Cible;
typedef std::string Extension;
typedef std::string RegexParser;

enum options { DEFAULT, G, E, T, U };

enum returnCodes { OK = 200, PREMANENT_REDIRECT = 301, TEMPORARY_REDIRECT = 302,
    UNAUTHORIZED = 401, FORBIDDEN = 403, PAGE_NOT_FOUND = 404, INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501, BAD_GATEWAY = 502, SERVICE_UNAVAILABLE = 503, GATEWAY_TIMEOUT = 504 };

//------------------------------------------------------------------------
// Rôle de la classe <Log>
//
//
//------------------------------------------------------------------------

class Log
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void initDefaut ( std::smatch & matches );
    // Mode d'emploi:
    //
    // Contrat :
    //

    const std::string & GetIp ( ) const;
    // Mode d'emploi:
    //
    // Contrat :
    //

    const Referer & GetLongReferer ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    const Referer & GetShortReferer ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    const Cible & GetCible ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    const int & GetHeureConsultation ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    int GetReturnCode ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    const Extension & GetExtension ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

//-------------------------------------------- Constructeurs - destructeur
    Log ( const std::string & logLine, int command = DEFAULT );
    // Mode d'emploi :
    // Constructeur pour instancier un objet Log à partir d'une ligne de texte
    // Contrat :
    // La chaine de caractères doit suivre le bon format access_log

    ~Log ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

private:
//----------------------------------------------------- Attributs protégés
    std::string ip;
    int heureConsultation;

    Referer longReferer;
    Referer shortReferer;
    Cible cible;

    Extension extension;

    int returnCode;
};

#endif // LOG_H