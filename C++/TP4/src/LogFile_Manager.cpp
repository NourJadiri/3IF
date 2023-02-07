/*************************************************************************
                           LogFile_Manager  -  description
                             -------------------
    début                : 17/01/2023
    copyright            : (C) 2023 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <LogFile_Manager> (fichier LogFile_Manager.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <memory>
using namespace std;

//------------------------------------------------------ Include personnel
#include "LogFile_Manager.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void LogFile_Manager::Init ( const bool * commandes, int temps, const string & url )
// Algorithme :
// parcours de chaque log du fichier de log
// filtrage de ces logs en fonction des commandes demandees par l'utilisateur
// sur la ligne de commande
{
    string line;

    // Parcours du fichier de logs
    while ( getline ( logFile, line ) )
    {
        // Extraction des informations de chaque ligne de log
        auto temp = make_shared < Log > ( line, url );

        // si la connexion n'a pas ete etablie on passe au log suivant
        if ( !connectionSuccess( temp->GetReturnCode() ) )
        {
            continue;
        }
        // si -e et que temp a une extension a exclure, on passe au log suivant
        if ( commandes[ E ] && isExcluded( temp->GetExtension() ) )
        {
            continue;
        }
        // si -t et que temp a un temps de consultation qui n'est pas dans la plage horaire, on passe au log suivant
        if ( commandes[ T ] && ( temp->GetHeureConsultation() < temps || temp->GetHeureConsultation() > temps + 1 ) )
        {
            continue;
        }
/*
        // Si -u et que le referer n'a pas l'url de base qui est demandée dans le fichier de configuration
        if ( commandes[ U ] && getBaseFromUrl( temp->GetLongReferer() ) != url )
        {
            continue;
        }*/

        // sinon on importe le log
        logs.push_back( temp );
    }
} //----- Fin de Init

const vector < shared_ptr < Log > > & LogFile_Manager::GetLogs ( ) const
{
    return logs;
} //----- Fin de GetLogs


//------------------------------------------------- Surcharge d'opérateurs
ostream & operator << ( ostream & os, LogFile_Manager & l )
// Algorithme :
//
{
    for ( auto & i : l.logs )
    {
        os << i->GetShortReferer() << " -> " << i->GetCible() << endl;
    }
    return os;
} //----- Fin de operator <<


//-------------------------------------------- Constructeurs - destructeur
LogFile_Manager::LogFile_Manager ( )
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <LogFile_Manager>" << endl;
#endif
} //----- Fin de LogFile_Manager (constructeur par defaut)

LogFile_Manager::LogFile_Manager ( const string & pathToFile )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur paramétré de <LogFile_Manager>" << endl;
#endif
    logFile.open( pathToFile );
} //----- Fin de LogFile_Manager (constructeur parametre)

LogFile_Manager :: ~LogFile_Manager ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <LogFile_Manager>" << endl;
#endif
}//----- Fin de ~LogFile_Manager