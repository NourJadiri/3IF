/*************************************************************************
                           ComposedTrip  -  Objet d'un trajet composé
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
// La classe ComposedTrip hérite publiquement de Trip et contient une List
// de SimpleTrips
// Un trajet composé est un trajet dont la ville d'arrivée d'un trajet doit
// correspondre à la ville de départ du trajet suivant
//------------------------------------------------------------------------

class ComposedTrip : public Trip
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    virtual void Display ( ) const;
    // Mode d'emploi :
    // Parcours de la List des SimpleTrip composants un ComposedTrip
    // pour les afficher un à un sur la sortie standard avec leurs
    // caractéristiques (villes d'arrivée, de départ, et transport)

    void AddSimpleTrip ( SimpleTrip const * newSTrip );
    // Mode d'emploi :
    // Ajout d'un SimpleTrip newSTrip à la List des trajets qui composent le
    // ComposedTrip
    // newSTrip est un pointeur sur le SimpleTrip à ajouter, et sera copié
    // en profondeur

//-------------------------------------------- Constructeurs - destructeur
    ComposedTrip ( );
    // Mode d'emploi :
    // Constructeur d'un ComposedTrip avec une List de SimpleTrips vide
    // Allocation de mémoire pour les chaines de caractères

    ComposedTrip( List const & list );
    // Mode d'emploi :
    // Constructeur d'un ComposedTrip à partir d'une List de SimpleTrips
    // list est une référence sur la List de SimpleTrips passée en paramètres
    // Recopie en profondeur les SimpleTrips composant list
    // avec une allocation de mémoire pour les chaines de caractères
    // Contrat :
    // La List list est non vide


    virtual ~ComposedTrip ( );
    // Mode d'emploi :
    // Libération de la mémoire allouée dans le tas pour les chaines de caractères
    // par héritage

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    List trips;

};

#endif // COMPOSEDTRIP_H