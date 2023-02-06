/*************************************************************************
                           Log  -  description
                             -------------------
    début                : Mardi 17 janvier 2023
    copyright            : (C) 2023 par Marie Roulier - Nour Eljadiri
    e-mail               : marie.roulier@insa-lyon.fr
                           mohamed-nour.eljadiri@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Log> (fichier Log.cpp) ------------

//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
//------------------------------------------------------ Include personnel
#include "Log.h"
using namespace std;

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

const string & Log::getIp() const
{
    return ip;
}

const Referer & Log::getLongReferer() const
{
    return longReferer;
}

const Cible & Log::getCible() const
{
    return cible;
}

const int & Log::getHeureConsultation() const
{
    return heureConsultation;
}

const Referer & Log::getShortReferer() const
{
    return shortReferer;
}

int Log::getReturnCode() const
{
    return returnCode;
}

const Extension & Log::GetExtension() const
// Algorithme :
//
{
    return extension;
}



//------------------------------------------------- Surcharge d'opérateurs



//-------------------------------------------- Constructeurs - destructeur

Log::Log( const string & logLine , int command )
// Algorithme :
// On capture les différents éléments du log grâce à du regex
// On répartit ces éléments en plusieurs groupes de capture
// On affecte les valeurs qui nous interessent aux attributs de notre classe.
{
    // On utilisera le regex ici pour capturer les éléments qui composent un log
    std::regex logFormat("(\\S+) (\\S+) (\\S+) \\[([^:]+):(\\d+):(\\d+):(\\d+) ([^\\]]+)\\] \"(\\S+) (.*?) (\\S+)\" (\\S+) (\\S+) \"(\\S+)\" ");
    smatch matches;

    if( regex_search( logLine.begin(), logLine.end(), matches, logFormat ) )
    {
        switch ( command )
        {
            case DEFAULT:
                initDefaut( matches );
                break;
            case E:

            break;
        }

    }
}

void Log::initDefaut ( smatch & matches )
{
    // Le premier élément du groupe de capture est l'ip de l'utilisateur
    ip = matches.str(1);

    // Le 5e élément correspond
    heureConsultation = stoi( matches.str(5) );

    // Le 8e éléments est l'url de la page requested
    cible = matches.str(10);

    returnCode = stoi( matches.str(12) );

    // Le 12e élément correspond au longReferer
    longReferer = matches.str(14);

    // On extrait le chemin court du shortReferer si celui ci suit un schéma d'url valide
    // Sinon le short referer sera une copie du longReferer
    if ( !isValidUrl( longReferer) )
    {
        shortReferer = longReferer;
    }
    else if ( getBaseFromUrl( longReferer ) == "intranet-if.insa-lyon.fr" )
    {
        shortReferer = getPathFromUrl( longReferer );
    }
    else
    {
        shortReferer = getBaseFromUrl( longReferer );
    }
}


Log::~Log() = default;
//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

