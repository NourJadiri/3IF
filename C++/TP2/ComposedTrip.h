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

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

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
    void Display ( std::ostream & os ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    friend std::ostream& operator<< ( std::ostream & os, const ComposedTrip & aComposedTrip );
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

    virtual ~ComposedTrip ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    List trips;

};

//-------------------------------- Autres définitions dépendantes de <ComposedTrip>

#endif // COMPOSEDTRIP_H
