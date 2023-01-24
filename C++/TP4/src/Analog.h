/*************************************************************************
                           Analog  -  description
                             -------------------
    début                : 17/01/2023
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Analog> (fichier Analog.h) ----------------
#if ! defined ( ANALOG_H )
#define ANALOG_H

//--------------------------------------------------- Interfaces utilisées
#include "Graph.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef std::string url;
enum options { G, E, T, U };

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

    void commandeE ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    int commandeT ( const string & hour ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    int commandeU ( const string & fichierConfig );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void commandeDefaut ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    int verifFichierLog ( const string & logFile, const string & mainArg ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

//----------------------------------------------------- Attributs protégés
    url urlUser;
};

//-------------------------------- Autres définitions dépendantes de <Analog>

#endif // ANALOG_H