/*************************************************************************
                           Analog  -  description
                             -------------------
    début                : 17/01/2023
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER
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
#include "LogFile_Manager.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int Analog::Launch ( int & argcMain, char * * & argvMain )
// Algorithme :
//
{
    if ( argcMain < 2 )
    {
        // s'il n'y a pas assez d'arguments dans la ligne de commande
        cerr << "Il faut insérer le fichier log ainsi que son extension." << endl;
        cerr << "Usage : " << argvMain[0] << " [options] nomFichier.log" << endl;
        cerr << "Fermeture de l'application." << endl;
        return 1;
    }

    bool commandes [4] = { false }; // pour ne pas executer trois fois la meme commande
    string logFile = argvMain[ argcMain - 1 ]; // dernier argument est le fichier log
    int retour; // valeur de retour des fonctions appelees

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
            commandeE();
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
            cerr << "Option inconnue ou non valide : " << argvMain[i] << endl;
            cerr << "Usage : " << argvMain[0] << " [options] nomFichier.log" << endl;
            cerr << "Les options sont : -g, -e, -t heure, -u fichierConfig.txt" << endl;
            cerr << "Fermeture de l'application." << endl;
            return 1;
        }
    }

    // par defaut, afficher la liste des 10 documents les plus consultes
    // appel de la fonction qui execute l'application par defaut
    commandeDefaut();
    return 0;

} //----- Fin de Launch

const url & Analog::GetUrlUser ( ) const
// Algorithme :
//
{
    return urlUser;
} //----- Fin de GetUrlUser

//-------------------------------------------- Constructeurs - destructeur
Analog::Analog ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Analog>" << endl;
#endif
} //----- Fin de Analog


Analog::~Analog ( )
// Algorithme :
//
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
    // si jamais l'utilisateur ne rentre pas un nom de fichier
    if ( !( dotFile.find( ".dot" ) != string::npos ) )
    {
        cerr << "Il faut insérer le fichier dot ainsi que son extension." << endl;
        cerr << "Usage : -g nomFichier.dot" << endl;
        cerr << "Fermeture de l'application." << endl;
        return 1;
    }

    // appel de la fonction pour generer le fichier GraphViz
    return 0;
} //----- Fin de commandeG

void Analog::commandeE ( ) const
// Algorithme :
//
{
    // appel de la fonction pour exclure les fichiers image
} //----- Fin de commandeE

int Analog::commandeT ( const string & hour ) const
// Algorithme :
//
{
    // si jamais l'utilisateur ne rentre pas des chiffres
    if ( !all_of( hour.begin(), hour.end(), ::isdigit ) )
    {
        cerr << "Il faut insérer une heure (en numérique, entre 0 et 23)." << endl;
        cerr << "Usage : -t heure" << endl;
        cerr << "Fermeture de l'application." << endl;
        return 1;
    }

    int heure = stoi( hour );

    // si les heures ne sont pas correctes
    if ( heure < 0 || heure > 23 ) {
        cerr << "Il faut insérer une heure comprise entre 0 et 23." << endl;
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
        cerr << "Il faut insérer le fichier txt ainsi que son extension." << endl;
        cerr << "Usage : -u nomFichier.txt" << endl;
        cerr << "Fermeture de l'application." << endl;
        return 1;
    }

    // lecture du contenu du fichier de config
    ifstream configUrlStream ( fichierConfig );
    if ( !configUrlStream.good() )
    {
        cerr << "Le fichier de configuration URL n'existe pas." << endl;
        cerr << "Usage : -u nomFichier.txt" << endl;
        cerr << "Fermeture de l'application." << endl;
        return 1;
    }

    getline( configUrlStream, urlUser );

    // on verifie l'URL donnee par l'utilisateur dans le fichier
    if ( urlUser.empty() )
    {
        // execution par defaut du programme
        cout << "Le fichier de configuration URL est vide." << endl;
        cout << "Execution par défaut." << endl;
    }

    // else tout est okay on continue
    return 0;
} //----- Fin de commandeU

void Analog::commandeDefaut ( ) const
// Algorithme :
//
{
    // appel de la fonction pour afficher les documents les plus consultes
} //----- Fin de commandeDefaut