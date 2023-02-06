/*************************************************************************
                           Log_Utils  -  description
                             -------------------
    début                : 17/01/2023
    copyright            : (C) 2023 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la librairie <Log_Utils> (fichier Log_Utils.h) ----------------
#if ! defined ( LOG_UTILS_H )
#define LOG_UTILS_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <array>
#include <algorithm>
#include <regex>
#include <list>

//------------------------------------------------------------------ Types
enum options { DEFAULT, G, E, T, U };

enum returnCodes { OK = 200, PARTIAL_CONTENT = 206,
    PREMANENT_REDIRECT = 301, TEMPORARY_REDIRECT = 302, NOT_MODIFIED = 304,
    UNAUTHORIZED = 401, FORBIDDEN = 403, PAGE_NOT_FOUND = 404, METHOD_NOT_ALLOWED = 405,
    INTERNAL_SERVER_ERROR = 500,NOT_IMPLEMENTED = 501, BAD_GATEWAY = 502, SERVICE_UNAVAILABLE = 503,
    GATEWAY_TIMEOUT = 504 };

//------------------------------------------------------------------------
// Rôle de la librairie <Log_Utils>
//
//
//
//------------------------------------------------------------------------

//-------------------------------------------------------------- Fonctions
bool isValidUrl ( const std::string & url );
// Mode d'emploi :
//
// Contrat :
//

std::string getPathFromUrl ( const std::string & url );
// Mode d'emploi :
//
// Contrat :
//

std::string getBaseFromUrl ( const std::string & url );
// Mode d'emploi :
//
// Contrat :
//

bool validExtension ( const std::string & file, const std::string & ext );
// Mode d'emploi :
//
// Contrat :
//

bool fileNotFound ( const std::string & logFile );
// Mode d'emploi :
//
// Contrat :
//

bool fileIsEmpty ( const std::string & logFile );
// Mode d'emploi :
//
// Contrat :
//

std::string getExtensionFromFile ( const std:: string & file );
// Mode d'emploi :
//
// Contrat :
//

bool connectionSuccess ( int returnCode );
// Mode d'emploi :
// La fonction retourne true si le code de retour fait partie des codes
// indiquant un succès de connexion (200, 206, 302, 304...)
// Contrat :
//

bool isExcluded ( const std::string & ext );
// Mode d'emploi :
// La fonction utilise une recherche binaire pour vérifier si l'extension passée en paramètre
// est une extension d'image / js / css
// Contrat :
// Le string passé en paramètre est une extension
// Le tableau d'extensions à exclure est trié par ordre alphabétique

#endif // LOG_UTILS_H