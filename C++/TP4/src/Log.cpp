/*************************************************************************
                           Log  -  description
                             -------------------
    début                : 16/01/2023
    copyright            : (C) 2023 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Log> (fichier Log.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Log.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
const string & Log::GetIp ( ) const
{
    return ip;
} //----- Fin de GetIp

const Referer & Log::GetLongReferer ( ) const
{
    return longReferer;
} //----- Fin de GetLongReferer

const Cible & Log::GetCible ( ) const
{
    return cible;
} //----- Fin de GetCible

const int & Log::GetHeureConsultation ( ) const
{
    return heureConsultation;
} //----- Fin de GetHeureConsultation

const Referer & Log::GetShortReferer ( ) const
{
    return shortReferer;
} //----- Fin de GetShortReferer

int Log::GetReturnCode ( ) const
{
    return returnCode;
} //----- Fin de GetReturnCode

const Extension & Log::GetExtension ( ) const
{
    return extension;
} //----- Fin de GetExtension


//-------------------------------------------- Constructeurs - destructeur
// TODO : il manque un default case dans le switch + initialisation de heureConsultation et codeRetour
Log::Log ( const string & logLine )
// Algorithme :
// On capture les differents elements du log grace à du regex
// On repartit ces elements en plusieurs groupes de capture
// On affecte les valeurs qui nous interessent aux attributs de notre classe.
{
#ifdef MAP
    cout << "Appel au constructeur de <Log>" << endl;
#endif
    // On utilisera le regex ici pour capturer les éléments qui composent un log
    std::regex logFormat("(\\S+) (\\S+) (\\S+) \\[([^:]+):(\\d+):(\\d+):(\\d+) ([^\\]]+)\\] \"(\\S+) (.*?) (\\S+)\" (\\S+) (\\S+) \"(\\S+)\" ");
    smatch matches;

    if ( regex_search( logLine , matches , logFormat ) )
    {
        // Le 1er element du groupe de capture est l'IP de l'utilisateur
        ip = matches.str(1);

        // Le 5e element correspond a l'heure
        heureConsultation = stoi(matches.str(5));

        // Le 10e element est l'url de la page demandee
        cible = matches.str(10);

        // On stock l'extension du fichier aussi
        extension = getExtensionFromFile(cible);

        // le 12e element correspond au code de retour
        returnCode = stoi(matches.str(12));

        // Le 14e element correspond au longReferer
        longReferer = matches.str(14);

        // On extrait le chemin court du shortReferer si celui ci suit un schéma d'url valide
        // Sinon le short referer sera une copie du longReferer
        if (!isValidUrl(longReferer))
        {
            shortReferer = longReferer;
        } else if (getBaseFromUrl(longReferer) == "intranet-if.insa-lyon.fr")
        {
            shortReferer = getPathFromUrl(longReferer);
        } else
        {
            shortReferer = getBaseFromUrl(longReferer);
        }
    }
} //----- Fin de Log

// TODO : a modifier
Log::~Log ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Log>" << endl;
#endif
} //----- Fin de ~Log


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
