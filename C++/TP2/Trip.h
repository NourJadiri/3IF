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
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void Display ( );
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    SimpleTrip & operator = ( const SimpleTrip & aSimpleTrip );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    SimpleTrip (char* aStart, char* aEnd, char* aTransportation);
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
