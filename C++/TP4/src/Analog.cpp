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
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Analog.h"
//#include "LogFile_Manager.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int Analog::Launch ( int & argcMain, char * * & argvMain )
// Algorithme :
// Parcours de chaque argument de la ligne de commande et garde en memoire
// quelle commande a ete utilisee.
// Pour chaque commande, verification des bonnes entrees correspondantes
{
    // le premier argument est le nom du programme
    string mainArg = argvMain[0];

    if ( argcMain < 2 )
    {
        // s'il n'y a pas assez d'arguments dans la ligne de commande
        cerr << endl << "Il faut insérer le fichier log ainsi que son extension." << endl;
        cerr << "Usage : " << mainArg << " [options] nomFichier.log" << endl;
        cerr << "Fermeture de l'application." << endl;
        return 1;
    }

    // le dernier argument est le fichier log
    string path = argvMain[argcMain - 1];
    string dotfile;
    string hour = "0";
    string fichierConfig;

    // valeur de retour des fonctions appelees
    int retour = 0;

    // on verifie que toutes les conditions relatives a l'utilisation de l'application en general sont OK
    retour = verifFichierLog( path, mainArg );
    if ( retour )
    {
        return retour;
    }

    for ( int i = 1; i < argcMain - 1; i++ )
    {
        if ( string( argvMain[i] ) == "-g" && !commandes[ G ] )
        {
            // option -g : generer fichier GraphViz
            commandes[ G ] = true;
            // stockage du fichier dans lequel generer le graph
            dotfile = argvMain[ ++i ];
            // on verifie que toutes les conditions relatives a l'utilisation de -g sont OK
            retour = checkG( dotfile );
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
            // option -t : seulement considerer hits dans un intervalle de temps
            commandes[ T ] = true;
            // filtrage horaire, donc pas une utilisation par défaut
            commandes[ DEFAULT ] = false;
            // stockage de la plage horaire
            hour = argvMain[ ++i ];
            // on verifie que toutes les conditions relatives a l'utilisation de -t sont OK
            retour = checkT( hour );
        }
        else if ( string( argvMain[ i ] ) == "-u" && !commandes[ U ] )
        {
            // option -u : pour donner le fichier de l'url
            commandes[ U ] = true;
            // filtrage URL, donc pas une utilisation par défaut
            commandes[ DEFAULT ] = false;
            fichierConfig = argvMain[ ++i ];
            // on verifie que toutes les conditions relatives a l'utilisation de -u sont OK
            retour = checkU( fichierConfig );
        }
        else
        {
            // option inconnue / non valide
            cerr << endl << "Option inconnue ou non valide : " << argvMain[i] << endl;
            cerr << "Usage : " << argvMain[0] << " [options] nomFichier.log" << endl;
            cerr << "Les options sont : -g, -e, -t heure, -u fichierConfig.txt" << endl;
            cerr << "Fermeture de l'application." << endl;
            retour = 1;
        }
        // s'il y a eu un probleme a un moment (mauvaise utilisation d'une commande par exemple)
        if ( retour )
        {
            return retour;
        }
    }


    // si toutes les conditions des commandes sont respectees

    // filtrage des logs du fichier en fonction des commandes entrees
    logs = make_shared < LogFile_Manager > ( path );
    logs->Init( commandes, stoi( hour ), urlUser );

    // generation du graph apres filtrage des logs
    if ( commandes[ G ] )
    {
        executeG( dotfile );
    }

    // affichage sur la console des avertissements et autres messages si besoin
    displayHeading();

    // affichage du top 10 sur la console (surcharge operateur <<)
    cout << *logs ;

    return 0;
} //----- Fin de Launch

const bool * Analog::GetCommandes ( ) const
{
    return commandes;
} //----- Fin de GetCommandes

const int & Analog::GetHeure ( ) const
{
    return heure;
} //----- Fin de GetHeure

const url & Analog::GetUrlUser ( ) const
{
    return urlUser;
} //----- Fin de GetUrlUser

const shared_ptr < LogFile_Manager > & Analog::GetLogs ( ) const
{
    return logs;
} //----- Fin de GetLogs

const shared_ptr < Graph > & Analog::GetGraph ( ) const
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
int Analog::checkG ( const string & dotFile )
// Algorithme :
// Verification que la commande a bien ete utilisee
// Donc verification qu'il y a un nom de fichier .dot
// S'il existe deja et est non vide, demande a l'utilisateur s'il souhaite
// en ecraser le contenu ou alors choisir un autre fichier .dot
{
    // si jamais l'utilisateur ne rentre pas un nom de fichier, ou pas un fichier .dot
    if ( !validExtension ( dotFile , "dot") )
    {
        cerr << "Usage : -g nomFichier.dot" << endl;
        cerr << "Fermeture de l'application." << endl;
        return 1;
    }

    // si le fichier est deja existant et non vide, demander a l'utilisateur s'il
    // souhaite poursuivre l'operation et donc ecraser le contenu du fichier
    ifstream fileStream;
    fileStream.open( dotFile.c_str() );

    if ( fileStream.good() && fileStream.peek() != ifstream::traits_type::eof() )
    {
        char choice;
        cout << endl << "Le fichier " << dotFile << " existe déjà et n'est pas vide." << endl;
        cout << "Souhaitez-vous écraser son contenu ? [y/n]" << endl;

        for ( ; ; )
        {
            cin >> choice;

            if (choice == 'y')
            {
                cout << endl << "Le contenu du fichier " << dotFile << " va être écrasé." << endl;
                break;
            }
            else if (choice == 'n')
            {
                cout << endl << "Merci d'entrer un autre nom de fichier .dot." << endl;

                string newFile;
                cin >> newFile;

                return checkG(newFile); // on répète le meme processus avec le nouveau fichier
            }
            else
            {
                cout << endl << "Merci de rentrer une option valide (y/n)." << endl;
            }
        }
    }
    fileStream.close();
    return 0;
} //----- Fin de checkG

int Analog::checkT ( const string & hour )
// Algorithme :
// Verification que la commande a bien ete utilisee
// Donc verification qu'il y a une heure donnee
// et qu'elle est valide (entier compris entre 0 et 23 inclus)
{
    // si jamais l'utilisateur ne rentre pas des chiffres (entiers ou non)
    if ( !all_of( hour.begin(), hour.end(), ::isdigit ) )
    {
        cerr << endl << "Il faut insérer une heure (entier en numérique, entre 0 et 23, inclus)." << endl;
        cerr << "Usage : -t heure" << endl;
        cerr << "Fermeture de l'application." << endl;
        return 1;
    }

    heure = stoi( hour );

    // si les heures ne sont pas correctes
    if ( heure < 0 || heure > 23 ) {
        cerr << endl << "Il faut insérer une heure comprise entre 0 et 23." << endl;
        cerr << "Usage : -t heure" << endl;
        cerr << "Fermeture de l'application." << endl;
        return 1;
    }

    return 0;
} //----- Fin de checkT

int Analog::checkU ( const string & fichierConfig )
// Algorithme :
// Verification que la commande a bien ete utilisee
// Donc verification qu'il y a un nom de fichier .txt et qu'il existe
// Si le fichier est vide, execution par defaut de l'application
// Sinon, prise en compte de l'URL donnee par l'utilisateur
{
    // si jamais l'utilisateur ne rentre pas un nom de fichier correct
    if ( !( fichierConfig.find( ".txt" ) != string::npos ) )
    {
        cerr << endl << "Il faut insérer le fichier txt ainsi que son extension." << endl;
        cerr << "Usage : -u nomFichier.txt" << endl;
        cerr << "Fermeture de l'application." << endl;
        return 1;
    }

    // lecture du contenu du fichier de config
    ifstream configUrlStream ( fichierConfig );
    if ( !configUrlStream.good() )
    {
        cerr << endl << "Le fichier de configuration URL n'existe pas." << endl;
        cerr << "Usage : -u nomFichier.txt" << endl;
        cerr << "Fermeture de l'application." << endl;
        return 1;
    }

    getline( configUrlStream, urlUser );

    // on verifie l'URL donnee par l'utilisateur dans le fichier
    if ( urlUser.empty() )
    {
        // execution par defaut du programme
        cout << endl << "Le fichier de configuration URL est vide." << endl;
        cout << "Execution par défaut." << endl;
    }
    // else tout est okay on continue

    return 0;
} //----- Fin de checkU

int Analog::verifFichierLog ( const string & logFile, const string & mainArg )
// Algorithme :
// Verification que le programme a bien ete utilise
// donc verification que l'utilisateur a bien donne un fichier .log, qui existe, et non vide
{
    // verification de la validite du fichier mis en parametre
    if ( !validExtension( logFile, "log" ) || fileNotFound( logFile ) || fileIsEmpty( logFile ) )
    {
        cerr << "Usage : " << mainArg << " nomFichier.log" << endl;
        cerr << "Fermeture de l'application." << endl;
        return 1;
    }
    return 0;
} //----- Fin de verifFichierLog

void Analog::executeG ( const string & dotFile )
// Algorithme :
// appel a la fonction pour generer le graph des logs
{
    // creation du graph (noeuds et arcs)
    graph = make_shared < Graph > ( logs );

    ofstream dotFileStream = generateDotFile( dotFile );
} //----- Fin de executeG

void Analog::displayHeading ( ) const
{
    cout << endl << "Top 10 of most accessed targets:" << endl;
    if ( commandes[ E ] )
    {
        cout << "/!\\ Warning: no image, css or javascript targets have been taken into account /!\\" << endl;
    }
    if ( commandes[ T ] )
    {
        cout << "/!\\ Warning: only hits between " << heure << "h and " << ( heure + 1 ) << "h have been taken into account /!\\" << endl;
    }
    if ( commandes[ U ] )
    {
        cout << "/!\\ Warning: only hits coming from referers with an URL-base \"" << urlUser << "\" have been processed /!\\" << endl;
    }
} //----- Fin de displayHeading

ofstream Analog::generateDotFile ( const string & path )
// Algorithme :
// generation du graph dans le fichier donne par l'utilisateur
{
    ofstream dotFile;
    dotFile.open ( path );

    cout << endl;
    cout << "Dot-file " << path << " generated" << endl;

    dotFile << "digraph {" << endl;

    // initialisation des noeuds et de leur nom
    for ( auto const & vertex : graph->GetVertice() )
    {
        dotFile << "\tnode" << vertex.second->GetId();
        dotFile << " [label=\"" << vertex.first << "\"];" << endl;
    }

    // etablissement des liens entre deux noeuds
    for ( auto const & edge : graph->GetEdges() )
    {
        dotFile << "\tnode" << edge.first.second << " -> " << "node" << edge.first.first;
        dotFile << " [label=\"" << edge.second << "\"];"<< endl;
    }

    dotFile << "}";

    return dotFile;
} //----- Fin de generateDotFile