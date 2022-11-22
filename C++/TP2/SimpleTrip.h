/*************************************************************************
                           SimpleTrip  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <SimpleTrip> (fichier SimpleTrip.h) ----------------
#if ! defined ( SimpleTrip_H )
#define SimpleTrip_H

//--------------------------------------------------- Interfaces utilisées
#include "Trip.h"
#include <cstring>
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <SimpleTrip>
//
//
//------------------------------------------------------------------------

class SimpleTrip : public Trip
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Display ( ostream & os ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    friend ostream& operator<<(ostream& os, const SimpleTrip & aSimpleTrip);
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    SimpleTrip (const char* aStart, const char* aEnd, const char* aTransportation);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~SimpleTrip ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    char* transportation;
};

//-------------------------------- Autres définitions dépendantes de <SimpleTrip>

#endif // SimpleTrip_H
