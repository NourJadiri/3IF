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

    char* GetTransport() const;

    void Display ( ) const override;
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    SimpleTrip ( const char* aStart = nullptr, const char* aEnd = nullptr, const char* aTransportation = nullptr );
    // Mode d'emploi :
    //
    // Contrat :

    ~SimpleTrip ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    char* transportation{};
};

#endif // SIMPLETRIP_H
