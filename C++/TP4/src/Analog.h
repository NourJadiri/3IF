/*************************************************************************
                           Analog  -  description
                             -------------------
    début                : 17/01/2023
    copyright            : (C) 2023 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Analog> (fichier Analog.h) ----------------
#if ! defined ( ANALOG_H )
#define ANALOG_H

//--------------------------------------------------- Interfaces utilisées
#include "Graph.h"

//------------------------------------------------------------------ Types
typedef std::string url;

//------------------------------------------------------------------------
// Rôle de la classe <Analog>
//
//
//------------------------------------------------------------------------

class Analog
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    int Launch ( int & argcMain, char * * & argvMain );
    // Mode d'emploi :
    //
    // Contrat :
    //

    const url & GetUrlUser ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

//-------------------------------------------- Constructeurs - destructeur
    Analog ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    ~Analog ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    int commandeG ( const string & dotFile ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    void commandeE ( const string & ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    static int commandeT ( const string & hour ) ;
    // Mode d'emploi :
    //
    // Contrat :
    //

    int commandeU ( const string & fichierConfig );
    // Mode d'emploi :
    //
    // Contrat :
    //

    static void commandeDefaut ( const string & );
    // Mode d'emploi :
    //
    // Contrat :
    //

    static int verifFichierLog ( const string & logFile, const string & mainArg ) ;
    // Mode d'emploi :
    //
    // Contrat :
    //

//----------------------------------------------------- Attributs protégés
    url urlUser;
    LogFile_Manager logs;
    Graph graph;
};

#endif // ANALOG_H