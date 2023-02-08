/*************************************************************************
                           Log  -  extraction des informations d'un log
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
Log::Log ( const string & logLine, const string & url )
// Algorithme :
// Capture des differents elements du log grace à du regex
// Repartition de ces elements en plusieurs groupes de capture
// Affectation des valeurs necessaires aux attributs de la classe.
{
#ifdef MAP
    cout << "Appel au constructeur de <Log>" << endl;
#endif
    // Utilisation du regex pour capturer les elements qui composent un log
    regex logFormat( "(\\S+) (\\S+) (\\S+) \\[([^:]+):(\\d+):(\\d+):(\\d+) ([^\\]]+)\\] \"(\\S+) (.*?) (\\S+)\" (\\S+) (\\S+) \"(\\S+)\" " );
    smatch matches;

    // si l'utilisateur a donne une base d'url a supprimer depuis un fichier de configuration
    if ( !url.empty() )
    {
        baseRefererToDelete = url;
    }

    if ( regex_search( logLine, matches, logFormat ) )
    {
        // Le 1er element du groupe de capture est l'IP de l'utilisateur
        ip = matches.str( 1 );

        // Le 5e element correspond a l'heure
        heureConsultation = stoi( matches.str( 5 ) );

        // Le 10e element est l'url de la page demandee
        cible = removeParamsFromUrl( matches.str( 10 ) );

        // On stock l'extension du fichier
        extension = getExtensionFromFile( cible );

        // le 12e element correspond au code de retour
        returnCode = stoi( matches.str( 12 ) );

        // Le 14e element correspond au longReferer
        longReferer = matches.str( 14 );

        // Extraction du chemin court du shortReferer si celui-ci suit un schema d'url valide
        // Sinon le short referer sera une copie du longReferer
        if ( !isValidUrl( longReferer ) )
        {
            shortReferer = longReferer;
        }
        else if ( getBaseFromUrl( longReferer ) == baseRefererToDelete )
        {
            shortReferer = getPathFromUrl( longReferer );
        }
        else
        {
            shortReferer = getBaseFromUrl( longReferer );
        }
    }
} //----- Fin de Log

Log::~Log ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Log>" << endl;
#endif
} //----- Fin de ~Log