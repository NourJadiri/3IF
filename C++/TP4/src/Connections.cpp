/*************************************************************************
                           Connections  -  historique des demandes
                             -------------------
    début                : 17/01/2023
    copyright            : (C) 2023 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Connections> (fichier Connections.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <memory>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Connections.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Connections::Init ( const bool * commandes, int heure, const string & url )
// Algorithme :
// parcours de chaque log du fichier de log
// filtrage de ces logs en fonction des commandes demandées par l'utilisateur
// sur la ligne de commande
{
    string line;

    // Parcours du fichier de logs
    while ( getline ( logFile, line ) )
    {
        // pour éviter une possible segfault si le fichier a des lignes vides
        if ( line.empty() )
        {
            continue;
        }

        // Extraction des informations de chaque ligne de log
        unique_ptr < Log > temp = make_unique < Log > ( line );

        // si la connexion n'a pas été établie, passe au log suivant
        if ( !connectionSuccess( temp->GetReturnCode() ) )
        {
            continue;
        }

        // si -t et que temp a une heure de consultation qui n'est pas dans la plage horaire, passe au log suivant
        if ( commandes[ T ] && ( temp->GetHeureConsultation() != heure ) )
        {
            continue;
        }

        // si -e et que temp a une extension à exclure, passe au log suivant
        if ( commandes[ E ] &&
             ( isExcluded( temp->GetExtensionCible() ) || isExcluded( temp->GetExtensionReferer() ) ) )
        {
            continue;
        }


        // Si -u et que le referer n'a pas l'url de base qui est demandée dans le fichier de configuration
        if ( commandes[ U ] && getBaseFromUrl( temp->GetLongReferer() ) != url )
        {
            continue;
        }

        // Si aucun problème n'est survenu, on update la map qui contient les hits
        if ( temp->GetCible() == "/" ) // la cible correspond à / donc à la page d'accueil
        {
            hitTable[ url + "/" ] += 1;
        }
        else
        {
            hitTable[ temp->GetCible() ] += 1;
        }

        // si -g, insertion dans le vector de logs (il ne servira que pour la création du graph)
        if ( commandes[ G ] )
        {
            logs.push_back( std::move( temp ) );
        }
    }

    // On initialise le top 10 des pages les plus visitées à la fin de l'initialisation
    top10Logs = Top10Logs();
} //----- Fin de Init

const vector < unique_ptr < Log > > & Connections::GetLogs ( ) const
{
    return logs;
} //----- Fin de GetLogs

list < pair < Cible, int > > Connections::Top10Logs ( )
// Algorithme :
// génération de la list des 10 documents les plus consultés
// Insertion des éléments de manière triée dans la list (appel à insertSorted)
{
    list < pair < Cible, int > > top10;

    // parcours de tous les noeuds
    for ( auto const & hit : hitTable )
    {
        insertSorted( top10, pair < Cible, int > ( hit.first, hit.second ) );

        // si la list contient plus de 10 documents, enlève le dernier
        // qui contient donc le moins de hits
        if ( top10.size() > 10 )
        {
            top10.pop_back();
        }
    }
    return top10;
} //----- Fin de Top10Logs


//------------------------------------------- Autres fonctions dépendantes
void insertSorted ( list < pair < Cible, int > > & list, const pair < Cible, int > & value )
// Algorithme :
// création d'une fonction locale comp qui définit la relation d'ordre entre les éléments de la list
// Appel à la fonction comp pour itérer dans la list et insérer des éléments en suivant cette
// relation d'ordre.
{
    // Tri selon le nombre de hits, puis par ordre alphabétique
    auto comp = [ ] ( const pair < Cible, int > & a, const pair < Cible, int > & b )
    {
        return  b.second != a.second ? b.second < a.second : b.first > a.first;
    };

    // création d'un insertIterator qui se place à la première position et vérifie l'ordre d'insertion
    auto it = lower_bound( list.begin(), list.end(), value, comp );

    // insertion dans la list
    list.insert( it, value );
} //----- Fin de insertSorted


//------------------------------------------------- Surcharge d'opérateurs
ostream & operator << ( ostream & os, Connections & l )
// Algorithme :
// Affiche les éventuels warnings levés durant l'exécution de l'application
// Parcours de la list du top 10 et affichage des informations utiles (nomCible, nombreConsulations)
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
Connections::Connections ( )
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <Connections>" << endl;
#endif
} //----- Fin de Connections (constructeur par défaut)

Connections::Connections ( const string & pathToFile )
// Algorithme :
// ouvre le stream d'entrée à partir duquel les logs seront importés
{
#ifdef MAP
    cout << "Appel au constructeur paramétré de <Connections>" << endl;
#endif
    logFile.open( pathToFile );
} //----- Fin de Connections (constructeur paramétré)

Connections :: ~Connections ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Connections>" << endl;
#endif
}//----- Fin de ~Connections