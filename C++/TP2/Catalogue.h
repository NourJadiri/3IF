/*************************************************************************
                           Catalogue  -  description
                             -------------------
    début                : 22/11/2022
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER,
                                        Vincent VOIGTLÄNDER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
                           vincent.voigtlander@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------------
#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H

//--------------------------------------------------- Interfaces utilisées
#include "List.h"

//------------------------------------------------------------------------
// Rôle de la classe <Catalogue>
// La classe Catalogue fait le lien entre l'utilisateur final et le modèle
// de données. Elle contient une liste de Trajets (trajets)
// Elle propose trois types de services à l'utilisateur :
// - Affichage du catalogue : Affiche tous les trajets enregistrés dans le
//   catalogue
// - Ajout de trajets : Permet à l'utilisateur de saisir de nouveaux
//   trajets avec ou sans escales (TrajetSimple ou TrajetCompose) à
//   ajouter au catalogue
// - Recherche de parcours : Permet à l'utilisateur de rechercher les
//   parcours (séquences ordonnées de trajets) correspondant à un voyage
//   d'une ville donnée à une autre ville donnée
//------------------------------------------------------------------------

class Catalogue
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Launch ( );
    // Mode d'emploi :
    // Menu de l'interface utilisateur sur la sortie standard, qui lui
    // propose plusieurs options, tant qu'il ne choisit pas de quitter
    // Contrat :
    // il faut entrer un CHIFFRE (ce qui est géré par les exceptions si on
    // utilise la librairie limits)

//-------------------------------------------- Constructeurs - destructeur
    Catalogue ( );
    // Mode d'emploi :
    // Construction d'un catalogue avec une liste vide de trajets

    virtual ~Catalogue ( );
    // Mode d'emploi :
    // Destructeur du catalogue

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    virtual void display ( ) const;
    // Mode d'emploi :
    // Affichage du catalogue en appelant la fonction de la classe List

    void add ( );
    // Mode d'emploi :
    // Ajout d'un SimpleTrip ou d'un ComposedTrip si l'utilisateur le décide
    // à la liste de Trips
    // Contrat :
    // L'utilisateur doit respecter les consignes qui s'affichent
    // c'est-à-dire ne pas mettre d'espaces. On suppose également
    // que les chaines de caractères entrées font moins de 64 caractères

    void fetch ( ) const;
    // Mode d'emploi :
    // Recherche du trajet demandé par l'utilisateur entre deux villes
    // Le trajet donné à l'utilisateur, s'il existe, sera soit un trajet
    // simple, soit un trajet composé
    // Contrat :
    // L'utilisateur ne doit pas rentrer d'espaces, et les chaines de caractères
    // entrées font moins de 64 caractères

//----------------------------------------------------- Attributs protégés
    List tripList;

};

#endif // CATALOGUE_H