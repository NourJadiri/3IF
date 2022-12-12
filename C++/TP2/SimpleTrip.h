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
// La classe SimpleTrip hérite publiquement de Trip et un SimpleTrip, par
// rapport à un Trip quelconque, contient un moyen de transport.
// Il contient donc par héritage une ville de départ start et d'arrivée end
// Un trajet simple a pour attribut spécifique son moyen de transport
// transportation, qui est donc une chaine de caractères
//------------------------------------------------------------------------

class SimpleTrip : public Trip
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    virtual void Display ( ) const;
    // Mode d'emploi :
    // Affichage sur la sortie standard des attributs d'un SimpleTrip,
    // c'est-à-dire de ses villes de départ et d'arrivée et de son moyen de
    // transport


    char * GetTransport ( ) const;
    // Mode d'emploi :
    // Renvoie un pointeur sur la chaine de caractères du moyen de transport
    // du SimpleTrip

//-------------------------------------------- Constructeurs - destructeur
    SimpleTrip ( const char * aStart = nullptr, const char * aEnd = nullptr, const char * aTransportation = nullptr );
    // Mode d'emploi :
    // Constructeur d'un SimpleTrip à partir d'une copie en profondeur des
    // trois caractéristiques d'un trajet simple
    // le moyen de transport est copié en profondeur dans ce constructeur
    // les villes de départ et arrivée sont copiées en profondeur grâce à l'appel
    // du constructeur de Trip (héritage)
    // Contrat :
    // les chaines de caractères sont valides (pas d'espaces et pas plus de
    // 64 caractères)

    virtual ~SimpleTrip ( );
    // Mode d'emploi :
    // Suppression de la zone mémoire allouée dynamiquement pour le moyen
    // de transport
    // Par héritage, les zones mémoire des villes de départ et arrivée sont
    // supprimées lors de l'appel au destructeur de Trip

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    char * transportation;

};

#endif // SIMPLETRIP_H