/*************************************************************************
                           Trip  -  SOMETHINGXXXXXXXXXX
                             -------------------
    début                : 22/11/2022
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER,
                                        Vincent VOIGTLÄNDER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
                           vincent.voigtlander@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Trip> (fichier Trip.h) ----------------
#if ! defined ( TRIP_H )
#define TRIP_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <cstring>

//------------------------------------------------------------------ Types
enum types { VIRTUAL, SIMPLE_TRIP, COMPOSED_TRIP };

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
    virtual void Display ( ) const = 0;
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual char* GetStart ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual char* GetEnd ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual int GetType ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs
    virtual bool operator == ( const Trip & aTrip ) const;
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

    explicit Trip ( const char* start, const char* end );
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
//----------------------------------------------------- Attributs protégés
    char* start;
    char* end;
    int type;

};

#endif //TRIP_H
