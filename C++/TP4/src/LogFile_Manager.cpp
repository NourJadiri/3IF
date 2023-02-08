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
void LogFile_Manager::Init (const bool * commandes, int heure, const string & url )
// Algorithme :
// parcours de chaque log du fichier de log
// filtrage de ces logs en fonction des commandes demandees par l'utilisateur
// sur la ligne de commande
{
    string line;

    // Parcours du fichier de logs
    while ( getline ( logFile, line ) )
    {
        // pour eviter une possible segfault si le fichier a des lignes vides
        if ( line.empty() )
        {
            continue;
        }

        // Extraction des informations de chaque ligne de log
        auto temp = make_shared < Log > ( line );

        // si la connexion n'a pas ete etablie on passe au log suivant
        if ( !connectionSuccess( temp->GetReturnCode() ) )
        {
            continue;
        }

        // si -t et que temp a un heure de consultation qui n'est pas dans la plage horaire, on passe au log suivant
        if ( commandes[ T ] && (temp->GetHeureConsultation() != heure ) )
        {
            // on suppose que le fichier de log a bien ete ecrit chronologiquement,
            // donc si un log depasse le maximum de l'intervalle, alors il n'est pas necessaire
            // de parcourir le reste du fichier
            if ( temp->GetHeureConsultation() > heure )
            {
                break;
            }
            continue;
        }

        // si -e et que temp a une extension a exclure, on passe au log suivant
        if ( commandes[ E ] &&
             ( isExcluded( temp->GetExtensionCible() ) || isExcluded( temp->GetExtensionReferer() ) ) )
        {
            continue;
        }

        // si -g, alors on commence à alimenter le vector de logs ( il ne servira que pour la création du graph )
        if ( commandes[ G ] )
        {
            logs.push_back( temp );
        }

        // Si -u et que le referer n'a pas l'url de base qui est demandée dans le fichier de configuration
        if ( commandes[ U ] && getBaseFromUrl( temp->GetLongReferer() ) != url )
        {
            continue;
        }

        // Par défaut, si aucun problème n'est rencontré, on update la map qui contient les hits
        hitTable[ temp->GetCible() ] += 1;
    }

    top10Logs = Top10Logs();
} //----- Fin de Init

const vector < shared_ptr < Log > > & LogFile_Manager::GetLogs ( ) const
{
    return logs;
} //----- Fin de GetLogs

list < pair < Cible , int > > LogFile_Manager::Top10Logs ( )
// Algorithme :
// generation de la list des 10 documents les plus consultes
{
    list < pair < Cible, int > > top10;

    // parcours de tous les noeuds dont on dispose
    for ( auto const & hit : hitTable )
    {
        insertSorted( top10, pair < Cible, int >( hit.first, hit.second ) );

        // si la list contient plus de 10 documents, enleve le dernier
        // qui contient donc le moins de hits
        if ( top10.size() > 10 )
        {
            top10.pop_back();
        }
    }
    return top10;
} //----- Fin de Top10Logs


//------------------------------------------------- Surcharge d'opérateurs
ostream & operator << ( ostream & os, LogFile_Manager & l )
// Algorithme :
//
{
    if ( l.top10Logs.empty( ) )
    {
        os << "/!\\ Warning: no target has been found /!\\" << endl;
    }
    else if ( l.top10Logs.size( ) < 10 )
    {
        os << "/!\\ Warning: less than 10 targets have been found /!\\" << endl;
    }
    os << endl;

    for ( auto const & aLog : l.top10Logs )
    {
        os << aLog.first << " (" << aLog.second << ( ( aLog.second == 1 ) ? " hit)" : " hits)" ) << endl;
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

void insertSorted ( list < pair < Cible, int > > & list, const pair < Cible, int > & value )
// Algorithme :
//
{
    auto comp = [ ] ( const pair < Cible, int > & a, const pair < Cible, int > & b )
    {
        return  b.second != a.second ? b.second < a.second : b.first > a.first;
    };
    auto it = lower_bound( list.begin(), list.end(), value, comp );
    list.insert( it, value );
} //----- Fin de insertSorted