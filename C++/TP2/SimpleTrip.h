/*************************************************************************
                           SimpleTrip  -  Objet d'un trajet simple
                             -------------------
    début                : 22/11/2022
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER,
                                        Vincent VOIGTLÄNDER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
                           vincent.voigtlander@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <SimpleTrip> (fichier SimpleTrip.h) ----------------
#if ! defined ( SIMPLETRIP_H )
#define SIMPLETRIP_H

//--------------------------------------------------- Interfaces utilisées
#include "Trip.h"
#include <cstring>

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
    void Display ( std::ostream & os ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    friend std::ostream& operator<< ( std::ostream& os, const SimpleTrip & aSimpleTrip );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    SimpleTrip ( const char* aStart, const char* aEnd, const char* aTransportation );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~SimpleTrip ( ); ///////////// pourquoi un destructeur en virtual??
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

#endif // SIMPLETRIP_H
