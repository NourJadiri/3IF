/*************************************************************************
                           Log_Utils  -  gestion de fonctions basiques
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
    INTERNAL_SERVER_ERROR = 500,NOT_IMPLEMENTED = 501, BAD_GATEWAY = 502,
    SERVICE_UNAVAILABLE = 503, GATEWAY_TIMEOUT = 504 };

//------------------------------------------------------------------------
// Rôle de la librairie <Log_Utils>
// La librairie permet de gérer toutes les fonctions basiques qui sont
// notamment appelées lors des validations des conditions de chaque
// commande utilisée sur la ligne de commande.
// Elle permet notamment d'enlever la base d'une adresse URL d'un referer
// ou encore de verifier le code de retour d'un log, ainsi que de
// gérer la commande -e.
//------------------------------------------------------------------------

//-------------------------------------------------------------- Fonctions
bool isValidUrl ( const std::string & url );
// Mode d'emploi :
// verification avec du regex que le parametre url est bien une adresse URL
// sert surtout pour distinguer les referer '-' des referers "classiques"
// Contrat :
// l'url doit etre un string valide (non vide)

std::string getPathFromUrl ( const std::string & url );
// Mode d'emploi :
// extraction avec du regex du chemin du parametre url
// Contrat :
// l'url doit etre un string valide (non vide) et doit etre
// une adresse URL

std::string getBaseFromUrl ( const std::string & url );
// Mode d'emploi :
// extraction avec du regex du nom de domaine du parametre url
// Contrat :
// l'url doit etre un string valide (non vide) et doit etre
// une adresse URL

std::string getExtensionFromFile ( const std:: string & file );
// Mode d'emploi :
// recupere l'extension d'une adresse URL (utile pour la commande -e)
// Contrat :
// le file doit etre un string valide (non vide) et doit etre
// un nom de fichier/page/document

bool validExtension ( const std::string & file, const std::string & ext );
// Mode d'emploi :
// verification que le parametre file (nom de fichier) contient bien
// l'extension voulue (parametre ext)
// Contrat :
// file et ext doivent etre des strings valides (non vides) et doivent
// respectivement etre un nom de fichier et une extension

bool fileNotFound ( const std::string & logFile );
// Mode d'emploi :
// lorsque l'utilisateur rentre un nom de fichier et que ce fichier
// doit exister pour utiliser correctement une commande,
// verification que ce fichier de nom logFile existe
// Contrat :
// le logFile doit etre un string valide (non vide) et doit etre
// un nom de fichier

bool fileIsEmpty ( const std::string & logFile );
// Mode d'emploi :
// lorsque l'utilisateur rentre un nom de fichier et que ce fichier
// ne doit pas etre vide pour utiliser correctement une commande,
// verification que ce fichier de nom logfile n'est pas vide
// Contrat :
// le logFile doit etre un string valide (non vide) et doit etre
// un nom de fichier

bool connectionSuccess ( int returnCode );
// Mode d'emploi :
// comparaison entre les codes indiquant un succes de connexion
// (200, 206, 301, 302 ou 304), et le code de retour d'un log
// (le parametre returnCode)
// Contrat :
// returnCode doit etre un entier compris dans les codes de retour
// returnCodes

bool isExcluded ( const std::string & ext );
// Mode d'emploi :
// Recherche binaire pour verifier si l'extension passée en paramètre
// (l'extension d'un log) est une extension d'image / js / css
// Contrat :
// le string ext doit etre un string valide (non vide) et doit
// representer une extension
// le tableau des extensions a exclure doit être trié alphabétiquement

std::string removeParamsFromUrl( const std::string & url );
// Mode d'emploi :
// Enlève tout paramètre passé à l'url afin de pouvoir considérer
// deux pages dont l'url serait le même mais les paramètres différents
// comme la même entité
// Fonctionne sur les url en général et les chemins en particulier.
// Contrat :
//

#endif // LOG_UTILS_H