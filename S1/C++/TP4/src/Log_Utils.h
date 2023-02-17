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
// Elle permet en particulier d'enlever la base d'une adresse URL d'un referer
// ou encore de vérifier le code de retour d'un log, ainsi que de
// gérer la commande -e.
//------------------------------------------------------------------------

//-------------------------------------------------------------- Fonctions
bool isValidUrl ( const std::string & url );
// Mode d'emploi :
// vérification avec du regex que le paramètre url est bien une adresse URL
// sert surtout pour distinguer les referer '-' des referers "classiques"
// Contrat :
// l'url doit être un string valide (non vide)

std::string getPathFromUrl ( const std::string & url );
// Mode d'emploi :
// extraction avec du regex du chemin du paramètre url
// Contrat :
// l'url doit être un string valide (non vide) et doit être
// une adresse URL

std::string getBaseFromUrl ( const std::string & url );
// Mode d'emploi :
// extraction avec du regex du nom de domaine du paramètre url
// Contrat :
// l'url doit être un string valide (non vide) et doit être
// une adresse URL

std::string removeParamsFromUrl ( const std::string & url );
// Mode d'emploi :
// supprime tout paramètre passé à l'url afin de pouvoir considérer
// deux pages avec la même base mais avec des paramètres distincts,
// comme étant une seule et unique entité
// Fonctionne sur les url en géneral et les chemins en particulier.
// Contrat :
// le string url doit être un string valide (non vide) et doit
// représenter une adresse url

std::string getExtensionFromFile ( const std:: string & file );
// Mode d'emploi :
// recupère l'extension d'une adresse URL (utile pour la commande -e)
// Contrat :
// le file doit être un string valide (non vide) et doit être
// un nom de fichier / page / document

bool validExtension ( const std::string & file, const std::string & ext );
// Mode d'emploi :
// vérification que le paramètre file (nom de fichier) contient bien
// l'extension voulue (paramètre ext)
// Contrat :
// file et ext doivent être des strings valides (non vides) et doivent
// respectivement être un nom de fichier et une extension

bool fileNotFound ( const std::string & logFile );
// Mode d'emploi :
// lorsque l'utilisateur rentre un nom de fichier et que ce fichier
// doit exister pour utiliser correctement une commande,
// vérification que ce fichier de nom logFile existe
// Contrat :
// le logFile doit être un string valide (non vide) et doit être
// un nom de fichier

bool fileIsEmpty ( const std::string & logFile );
// Mode d'emploi :
// vérification que, lorsque l'utilisateur rentre un nom de fichier,
// il ne doit pas être vide pour utiliser correctement une commande,
// vérification que ce fichier de nom logfile n'est pas vide
// Contrat :
// le logFile doit être un string valide (non vide) et doit être
// un nom de fichier

bool connectionSuccess ( int returnCode );
// Mode d'emploi :
// comparaison entre les codes indiquant un succès de connexion
// (200, 206, 301, 302 ou 304), et le code de retour d'un log
// (le paramètre returnCode)
// Contrat :
// returnCode doit être un entier compris dans les codes de retour
// returnCodes

bool isExcluded ( const std::string & ext );
// Mode d'emploi :
// Recherche binaire pour vérifier si l'extension passée en paramètre
// (l'extension d'un log) est une extension d'image / js / css
// Contrat :
// le string ext doit être un string valide (non vide) et doit
// représenter une extension
// le tableau des extensions à exclure doit être trié alphabétiquement

#endif // LOG_UTILS_H