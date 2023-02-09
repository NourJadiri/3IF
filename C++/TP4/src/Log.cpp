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

const Extension & Log::GetExtensionCible ( ) const
{
    return extensionCible;
} //----- Fin de GetExtension

const Extension & Log::GetExtensionReferer ( ) const
{
    return extensionReferer;
} //----- Fin de GetExtension


//-------------------------------------------- Constructeurs - destructeur
Log::Log ( const string & logLine, const Referer & baseRefererToDelete )
// Algorithme :
// Capture des différents éléments du log grâce à du regex
// Répartition de ces éléments en plusieurs groupes de capture
// Affectation des valeurs nécessaires aux attributs de la classe.
{
#ifdef MAP
    cout << "Appel au constructeur de <Log>" << endl;
#endif
    // Utilisation du regex pour capturer les éléments qui composent un log
    regex logFormat( "(\\S+) (\\S+) (\\S+) \\[([^:]+):(\\d+):(\\d+):(\\d+) ([^\\]]+)\\] \"(\\S+) (.*?) (\\S+)\" (\\S+) (\\S+) \"(\\S+)\" " );
    smatch matches;

    if ( regex_search( logLine, matches, logFormat ) )
    {
        // Le 1er élément du groupe de capture est l'IP de l'utilisateur
        ip = matches.str( 1 );

        // Le 5e élément correspond à l'heure
        heureConsultation = stoi( matches.str( 5 ) );

        // Le 10e élément est l'url de la page demandée
        cible = removeParamsFromUrl( matches.str( 10 ) );

        // l'extension du fichier cible
        extensionCible = getExtensionFromFile(cible );

        // le 12e élément correspond au code de retour
        returnCode = stoi( matches.str( 12 ) );

        // Le 14e élément correspond au longReferer
        longReferer = matches.str( 14 );

        // Extraction du chemin court du shortReferer si celui-ci suit un schéma d'url valide
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

        // l'extension du referer
        extensionReferer = getExtensionFromFile ( getPathFromUrl( longReferer ) );
    }
} //----- Fin de Log

Log::~Log ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Log>" << endl;
#endif
} //----- Fin de ~Log