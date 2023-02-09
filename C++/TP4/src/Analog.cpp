/*************************************************************************
                           Analog - interface utilisateur & appels fonctions
                             -------------------
    début                : 17/01/2023
    copyright            : (C) 2023 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Analog> (fichier Analog.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Analog.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int Analog::Launch ( int & argcMain, char * * & argvMain )
// Algorithme :
// Parcours de chaque argument de la ligne de commande et garde en mémoire
// quelle commande à été utilisée.
// Pour chaque commande, vérification des bonnes entrées correspondantes
{
    // le premier argument est le nom du programme
    string mainArg = argvMain[0];

    if ( argcMain < 2 )
    {
        // s'il n'y a pas assez d'arguments dans la ligne de commande
        cerr << endl << "An existing log file and its extension must be entered." << endl;
        cerr << "Usage: " << mainArg << " [options] fileName.log" << endl;
        cerr << "Stop." << endl;
        return 1;
    }

    // le dernier argument est le fichier log
    string path = argvMain[ argcMain - 1 ];

    string fichierConfig;

    // valeur de retour des fonctions appelées
    int retour = 0;

    // vérification des conditions relatives à l'utilisation de l'application en géneral
    retour = verifFichierLog( path, mainArg );
    if ( retour )
    {
        return retour;
    }

    for ( int i = 1; i < argcMain - 1; i++ )
    {
        if ( string( argvMain[i] ) == "-g" && !commandes[ G ] )
        {
            // option -g : génerer fichier GraphViz
            commandes[ G ] = true;
            // stockage du fichier dans lequel génerer le graph
            dotFile = argvMain[ ++i ];
            // vérification que toutes les conditions relatives à l'utilisation de -g sont OK
            retour = checkG( );
        }
        else if ( string( argvMain[ i ] ) == "-e" && !commandes[ E ] )
        {
            // option -e : exclure les fichiers images
            commandes[ E ] = true;
            // filtrage extension, donc pas une utilisation par défaut
            commandes[ DEFAULT ] = false;
        }
        else if ( string( argvMain[ i ] ) == "-t" && !commandes[ T ] )
        {
            // option -t : seulement considérer les hits dans un intervalle de temps
            commandes[ T ] = true;
            // filtrage horaire, donc pas une utilisation par défaut
            commandes[ DEFAULT ] = false;
            // stockage de la plage horaire
            heure = argvMain[ ++i ];
            // vérification que toutes les conditions relatives à l'utilisation de -t sont OK
            retour = checkT( );
        }
        else if ( string( argvMain[ i ] ) == "-u" && !commandes[ U ] )
        {
            // option -u : pour donner le fichier de l'url
            commandes[ U ] = true;
            // filtrage URL, donc pas une utilisation par défaut
            commandes[ DEFAULT ] = false;
            fichierConfig = argvMain[ ++i ];
            // vérification que toutes les conditions relatives à l'utilisation de -u sont OK
            retour = checkU( fichierConfig );
        }
        else
        {
            // option inconnue / non valide
            cerr << endl << "Unknown or invalid option: " << argvMain[i] << endl;
            cerr << "Usage: " << argvMain[0] << " [options] fileName.log" << endl;
            cerr << "Options are: -g, -e, -t hour, -u configFile.txt" << endl;
            cerr << "Stop." << endl;
            retour = 1;
        }
        // s'il y a eu un problème à un moment (mauvaise utilisation d'une commande par exemple)
        if ( retour )
        {
            return retour;
        }
    }

    // si toutes les conditions des commandes sont respectées

    // filtrage des logs du fichier en fonction des commandes entrées
    logs = make_shared < Connections > ( path );
    logs->Init( commandes, stoi( heure ), urlUser );

    // géneration du graph après filtrage des logs
    if ( commandes[ G ] )
    {
        executeG();
    }

    // affichage sur la console des avertissements et autres messages si besoin
    displayHeading();

    // affichage du top 10 sur la console (surcharge opérateur <<)
    cout << * logs ;

    return retour;
} //----- Fin de Launch

const bool * Analog::GetCommandes ( ) const
{
    return commandes;
} //----- Fin de GetCommandes

const string & Analog::GetHeure ( ) const
{
    return heure;
} //----- Fin de GetHeure

const url & Analog::GetUrlUser ( ) const
{
    return urlUser;
} //----- Fin de GetUrlUser

const shared_ptr < Connections > & Analog::GetLogs ( ) const
{
    return logs;
} //----- Fin de GetLogs

const unique_ptr < Graph > & Analog::GetGraph ( ) const
{
    return graph;
} //----- Fin de GetGraph


//-------------------------------------------- Constructeurs - destructeur
Analog::Analog ( )
{
#ifdef MAP
    cout << "Appel au constructeur de <Analog>" << endl;
#endif
} //----- Fin de Analog

Analog::~Analog ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Analog>" << endl;
#endif
} //----- Fin de ~Analog


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
int Analog::checkG ( )
// Algorithme :
// Vérification que la commande a bien été utilisée
// Donc vérification qu'il y a un nom de fichier .dot
// S'il existe déjà et est non vide, demande à l'utilisateur s'il souhaite
// en écraser le contenu ou alors choisir un autre fichier .dot
{
    // si jamais l'utilisateur ne rentre pas un nom de fichier, ou pas un fichier .dot
    if ( !validExtension ( dotFile, "dot" ) )
    {
        cerr << "Usage: -g fileName.dot" << endl;
        cerr << "Stop." << endl;
        return 1;
    }

    // si le fichier est déjà existant et non vide, demander à l'utilisateur s'il
    // souhaite poursuivre l'opération et donc écraser le contenu du fichier
    ifstream fileStream;
    fileStream.open( dotFile.c_str() );

    if ( fileStream.good() && fileStream.peek() != ifstream::traits_type::eof() )
    {
        char choice;
        cout << endl << "The file " << dotFile << " already exists and is not empty." << endl;
        cout << "Do you wish to overwrite its contents? [y/n]" << endl;

        for ( ; ; )
        {
            cin >> choice;

            if (choice == 'y')
            {
                cout << endl << "The contents of the file " << dotFile << " will be overwritten." << endl;
                break;
            }
            else if (choice == 'n')
            {
                cout << endl << "Please enter another .dot file name." << endl;

                cin >> dotFile;

                return checkG(); // on répète le même processus avec le nouveau fichier
            }
            else
            {
                cout << endl << "Please enter a valid option (y/n)." << endl;
            }
        }
    }
    fileStream.close();
    return 0;
} //----- Fin de checkG

int Analog::checkT ( )
// Algorithme :
// Vérification que la commande a bien été utilisée
// Donc vérification qu'il y a une heure donnée
// et qu'elle est valide (entier compris entre 0 et 23 inclus)
{
    // si jamais l'utilisateur ne rentre pas des chiffres (entiers ou non)
    if ( !all_of( heure.begin(), heure.end(), ::isdigit ) )
    {
        cerr << endl << "An hour must be entered (integer, between 0 and 23 both included)." << endl;
        cerr << "Usage: -t hour" << endl;
        cerr << "Stop." << endl;
        return 1;
    }

    int hour = stoi( heure );

    // si les heures ne sont pas correctes
    if ( hour < 0 || hour > 23 ) {
        cerr << endl << "An hour between 0 and 23 both included must be entered." << endl;
        cerr << "Usage: -t hour" << endl;
        cerr << "Stop." << endl;
        return 1;
    }

    return 0;
} //----- Fin de checkT

int Analog::checkU ( const string & fichierConfig )
// Algorithme :
// Vérification que la commande a bien été utilisée
// Donc vérification qu'il y a un nom de fichier .txt et qu'il existe
// Si le fichier est vide, exécution par défaut de l'application
// Sinon, prise en compte de l'URL donnée par l'utilisateur
{
    // si jamais l'utilisateur ne rentre pas un nom de fichier correct
    if ( fichierConfig.find( ".txt" ) == string::npos )
    {
        cerr << endl << "A txt file and its extension must be entered." << endl;
        cerr << "Usage: -u fileName.txt" << endl;
        cerr << "Stop." << endl;
        return 1;
    }

    // lecture du contenu du fichier de config
    ifstream configUrlStream ( fichierConfig );
    if ( !configUrlStream.good() )
    {
        cerr << endl << "The URL configuration file does not exist." << endl;
        cerr << "Usage: -u fileName.txt" << endl;
        cerr << "Stop." << endl;
        return 1;
    }

    getline( configUrlStream, urlUser );

    // vérification de l'URL donnée par l'utilisateur dans le fichier
    // si elle est vide, utilisation de la base d'url par défaut
    if ( urlUser.empty() )
    {
        // exécution par défaut du programme
        cout << endl << "The URL configuration file is empty." << endl;
        cout << "Default URL-base will be used." << endl;

        urlUser = DEFAULT_URL_BASE;
    }
    // else tout est okay on continue

    return 0;
} //----- Fin de checkU

int Analog::verifFichierLog ( const string & logFile, const string & mainArg )
// Algorithme :
// Vérification que le programme a bien été utilisé
// donc vérification que l'utilisateur a bien donné un fichier .log, qui existe, et non vide
{
    // vérification de la validité du fichier mis en paramètre
    if ( !validExtension( logFile, "log" ) || fileNotFound( logFile ) || fileIsEmpty( logFile ) )
    {
        cerr << "Usage: " << mainArg << " [options] fileName.log" << endl;
        cerr << "Stop." << endl;
        return 1;
    }
    return 0;
} //----- Fin de verifFichierLog

void Analog::executeG ( )
// Algorithme :
// appel à la fonction pour générer le graph des logs
{
    // creation du graph (noeuds et arcs)
    graph = make_unique < Graph > ( logs );

    // écriture dans le fichier dot
    generateDotFile( );
} //----- Fin de executeG

void Analog::displayHeading ( ) const
// Algorithme :
// affichage des messages correspondant aux différentes commandes utilisées
{
    cout << endl << "Top 10 of most accessed targets:" << endl;
    if ( commandes[ E ] )
    {
        cout << "/!\\ Warning: no image, css or javascript targets have been taken into account /!\\" << endl;
    }
    if ( commandes[ T ] )
    {
        int hour = stoi( heure );
        cout << "/!\\ Warning: only hits between " << hour << "h and " << ( hour + 1 ) << "h have been taken into account /!\\" << endl;
    }
    if ( commandes[ U ] )
    {
        cout << "/!\\ Warning: only hits coming from referers with an URL-base \"" << urlUser << "\" have been processed /!\\" << endl;
    }
} //----- Fin de displayHeading

void Analog::generateDotFile ( )
// Algorithme :
// génération du graph dans le fichier donné par l'utilisateur
{
    ofstream dotFileStream;
    dotFileStream.open ( dotFile );
    cout << endl << "Dot-file " << dotFile << " generated" << endl;

    dotFileStream << "digraph {" << endl;
    // initialisation des noeuds et de leur nom
    for ( auto const & vertex : graph->GetVertice() )
    {
        dotFileStream << "\tnode" << vertex.second->GetId();
        dotFileStream << " [label=\"" << vertex.first << "\"];" << endl;
    }

    // établissement des liens entre deux noeuds
    for ( auto const & edge : graph->GetEdges() )
    {
        dotFileStream << "\tnode" << edge.first.first << " -> " << "node" << edge.first.second;
        dotFileStream << " [label=\"" << edge.second << "\"];"<< endl;
    }
    dotFileStream << "}";
} //----- Fin de generateDotFile