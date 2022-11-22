/*************************************************************************
                           Trip  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Trip> (fichier Trip.h) ----------------
#if ! defined ( Trip_H )
#define Trip_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Trip>
//
//
//------------------------------------------------------------------------

class Trip
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

    char* GetStart ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    char* GetEnd ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual void Display ( );
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    Trip & operator = ( const Trip & unTrip );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Trip ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Trip ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    char* start;
    char* end;
};

//-------------------------------- Autres définitions dépendantes de <Trip>

#endif // Trip_H
