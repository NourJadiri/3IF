/*************************************************************************
                           Log  -  extraction des informations d'un log
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

//------------------------------------------------------------- Constantes
#define DEFAULT_URL_BASE "intranet-if.insa-lyon.fr"

//------------------------------------------------------------------ Types
typedef std::string Referer;
typedef std::string Cible;
typedef std::string Extension;

//------------------------------------------------------------------------
// Rôle de la classe <Log>
// Cette classe Log permet d'extraire toutes les informations contenues
// sur la ligne d'un log, et de les affecter aux attributs.
//------------------------------------------------------------------------

class Log
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    const std::string & GetIp ( ) const;
    // Mode d'emploi:
    // Renvoie l'adresse IP du log

    const Referer & GetLongReferer ( ) const;
    // Mode d'emploi :
    // Renvoie l'adresse du referer du log

    const Referer & GetShortReferer ( ) const;
    // Mode d'emploi :
    // Renvoie l'adresse du referer du log

    const Cible & GetCible ( ) const;
    // Mode d'emploi :
    // Renvoie l'adresse cible du log

    const int & GetHeureConsultation ( ) const;
    // Mode d'emploi :
    // Renvoie l'heure de consultation du log

    int GetReturnCode ( ) const;
    // Mode d'emploi :
    // Renvoie le code de retour du log

    const Extension & GetExtensionCible ( ) const;
    // Mode d'emploi :
    // Renvoie l'extension de la cible d'une ligne de log

    const Extension & GetExtensionReferer ( ) const;
    // Mode d'emploi :
    // Renvoie l'extension du referer d'une ligne de log


    //-------------------------------------------- Constructeurs - destructeur
    explicit Log ( const std::string & logLine, const Referer & baseRefererToDelete = DEFAULT_URL_BASE );
    // Mode d'emploi :
    // Constructeur pour instancier un objet Log à partir d'une ligne de texte
    // Contrat :
    // La chaîne de caractères doit suivre le bon format access_log
    // c'est-à-dire que le fichier de log doit suivre le modèle standard

    ~Log ( );
    // Mode d'emploi :
    // Destructeur de Log


//------------------------------------------------------------------ PRIVE

private:
//----------------------------------------------------- Attributs protégés
    std::string ip;
    int heureConsultation; // seulement l'heure (pas les minutes)

    // l'adresse URL en entier
    Referer longReferer;

    // l'adresse URL réduite au chemin de l'adresse si la base correspond à
    // celle voulue par l'utilisateur OU aàla base par défaut (intranet-if.insa-lyon.fr)
    // sinon, correspond à la base de l'adresse URL (nom de domaine seulement)
    Referer shortReferer;

    Cible cible;

    Extension extensionCible;
    Extension extensionReferer;

    int returnCode;
};

#endif // LOG_H