/*************************************************************************
                           ComposedTrip  -  Objet d'un trajet compose
                             -------------------
    début                : 22/11/2022
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER,
                                        Vincent VOIGTLÄNDER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
                           vincent.voigtlander@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <ComposedTrip> (fichier ComposedTrip.h) ----------------
#if ! defined ( COMPOSEDTRIP_H )
#define COMPOSEDTRIP_H

//--------------------------------------------------- Interfaces utilisées
#include "Trip.h"
#include "List.h"

//------------------------------------------------------------------------
// Rôle de la classe <ComposedTrip>
//
//
//------------------------------------------------------------------------

class ComposedTrip : public Trip
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Display ( ) const override;
    // Mode d'emploi :
    //
    // Contrat :
    //

    void AddSimpleTrip (SimpleTrip * newSTrip);
    // Mode d'emploi :
    //
    // Contrat :
    //

//-------------------------------------------- Constructeurs - destructeur
    ComposedTrip ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    explicit ComposedTrip( List & list );
    // Mode d'emploi :
    //
    // Contrat :
    //

    ~ComposedTrip ( ) override;
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    List trips;

};

#endif // COMPOSEDTRIP_H
