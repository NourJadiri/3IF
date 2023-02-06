/*************************************************************************
                           Analog  -  interface utilisateur & appels
                             -------------------
    début                : 17/01/2023
    copyright            : (C) 2023 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Analog> (fichier Analog.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Analog.h"
#include "LogFile_Manager.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int Analog::Launch ( int & argcMain, char * * & argvMain )
// Algorithme :
//
{
    string mainArg = argvMain[0];

    if ( argcMain < 2 )
    {
        // s'il n'y a pas assez d'arguments dans la ligne de commande
        cerr << endl << "Il faut insérer le fichier log ainsi que son extension." << endl;
        cerr << "Usage : " << mainArg << " [options] nomFichier.log" << endl;
        cerr << "Fermeture de l'application." << endl;
        return 1;
    }

    // pour ne pas executer plusieurs fois la meme commande
    bool commandes [5] = { false };

    // le dernier argument est le fichier log
    string path = argvMain[argcMain - 1];

    // valeur de retour des fonctions appelees
    int retour;

    for ( int i = 1; i < argcMain - 1; i++ )
    {
        if ( string( argvMain[i] ) == "-g" && !commandes[G] )
        {
            // option -g : generer fichier GraphViz
            commandes[G] = true;
            string dotfile = argvMain[ ++i ];

            // appel de la fonction qui execute la commande -g
            retour = commandeG( dotfile );

            // si erreur lors de l'execution de la commande
            if ( retour )
            {
                return retour;
            }
        }
        else if ( string( argvMain[ i ] ) == "-e" && !commandes[E] )
        {
            // option -e : exclure les fichiers images
            commandes[E] = true;

            // appel de la fonction qui execute la commande -e
            retour = commandeE ( path );

            if ( retour )
            {
                return retour;
            }
        }
        else if ( string( argvMain[ i ] ) == "-t" && !commandes[T] )
        {
            // option -t : seulement considerer hits dans un intervalle de temps
            commandes[T] = true;
            string hour = argvMain[ ++i ];

            // appel de la fonction qui execute la commande -t
            retour = commandeT( hour );

            // si erreur lors de l'execution de la commande
            if ( retour )
            {
                return retour;
            }
        }
        else if ( string( argvMain[ i ] ) == "-u" && !commandes[U] )
        {
            // option -u : pour donner le fichier de l'url
            commandes[U] = true;
            string fichierConfig = argvMain[ ++i ];

            // appel de la fonction qui execute la commande -u
            retour = commandeU( fichierConfig );

            // si erreur lors de l'execution de la commande
            if ( retour )
            {
                return retour;
            }
        }
        else
        {
            // option inconnue / non valide
            cerr << endl << "Option inconnue ou non valide : " << argvMain[i] << endl;
            cerr << "Usage : " << argvMain[0] << " [options] nomFichier.log" << endl;
            cerr << "Les options sont : -g, -e, -t heure, -u fichierConfig.txt" << endl;
            cerr << "Fermeture de l'application." << endl;
            return 1;
        }
    }

    retour = verifFichierLog( path, mainArg );
    if ( retour )
    {
        return retour;
    }

    // par defaut, afficher la liste des 10 documents les plus consultes
    // appel de la fonction qui execute l'application par defaut
    if ( !commandes[E] && !commandes[G] && !commandes[T] && !commandes[U])
    {
        commandeDefaut( path );
    }

    return 0;

} //----- Fin de Launch

const url & Analog::GetUrlUser ( ) const
{
    return urlUser;
} //----- Fin de GetUrlUser


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
int Analog::commandeG ( const string & dotFile ) const
// Algorithme :
//
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

                return commandeG( newFile ); // on répète le meme processus avec le nouveau fichier
            }
            else
            {
                cout << endl << "Merci de rentrer une option valide (y/n)." << endl;
            }
        }
    }

    fileStream.close();

    ofstream dotFileStream;
    dotFileStream.open( dotFile.c_str() );

    // appel de la fonction pour generer le fichier GraphViz

    dotFileStream.close();
    return 0;
} //----- Fin de commandeG

int Analog::commandeE ( const string & file ) const
// Algorithme :
//
{

    cout << endl << "Top 10 of most accessed targets:" << endl;
    cout << "/!\\ Warning: no image, css or javascript targets have been taken into account /!\\"<< endl << endl;

    // appel de la fonction pour exclure les fichiers image
    Graph g( file , E );

    cout << g;

    return 0;
} //----- Fin de commandeE

int Analog::commandeT ( const string & hour )
// Algorithme :
//
{
    // si jamais l'utilisateur ne rentre pas des chiffres
    if ( !all_of( hour.begin(), hour.end(), ::isdigit ) )
    {
        cerr << endl << "Il faut insérer une heure (en numérique, entre 0 et 23, inclus)." << endl;
        cerr << "Usage : -t heure" << endl;
        cerr << "Fermeture de l'application." << endl;
        return 1;
    }

    int heure = stoi( hour );

    // si les heures ne sont pas correctes
    if ( heure < 0 || heure > 23 ) {
        cerr << endl << "Il faut insérer une heure comprise entre 0 et 23." << endl;
        cerr << "Usage : -t heure" << endl;
        cerr << "Fermeture de l'application." << endl;
        return 1;
    }


    // appel de la fonction pour filtrer les hits par intervalle de temps
    return 0;
} //----- Fin de commandeT

int Analog::commandeU ( const string & fichierConfig )
// Algorithme :
//
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
} //----- Fin de commandeU

int Analog::commandeDefaut ( const string & file )
// Algorithme :
//
{
    cout << endl << "Top 10 of most accessed targets:" << endl << endl;
    Graph g( file , DEFAULT );

    cout << g;

    return 0;
} //----- Fin de Top10Logs

int Analog::verifFichierLog ( const string & logFile, const string & mainArg )
// Algorithme :
//
{
    // vérification de la validité du fichier mis en paramètre
    if ( fileNotFound( logFile ) || !validExtension( logFile , "log" ) || fileIsEmpty( logFile ) )
    {
        cerr << "Usage : " << mainArg << " nomFichier.log" << endl;
        cerr << "Fermeture de l'application." << endl;
        return 1;
    }

    return 0;
} //----- Fin de verifFichierLog