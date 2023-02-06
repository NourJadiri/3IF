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
#include <algorithm>
#include <regex>
#include <list>

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

#endif // LOG_UTILS_H