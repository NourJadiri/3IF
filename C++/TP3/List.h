/*************************************************************************
                           List - Structure de données qui gère les Trips
                             -------------------
    début                : 22/11/2022
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <List> (fichier List.h) ----------------
#if ! defined ( LIST_H )
#define LIST_H

//--------------------------------------------------- Interfaces utilisées
#include "Node.h"

//------------------------------------------------------------- Constantes
#define DEFAULT_LIST_SIZE 0

//------------------------------------------------------------------------
// Rôle de la classe <List>
// Structure de données qui permet de gérer les trajets Trips,
// sans distinction de leur nature, donc qu'ils soient simples ou composés.
// Correspond à une liste simplement chaînée
// List a pour attributs un pointeur sur le premier élément qui est un Node
// et le nombre d'éléments qu'elle contient (donc sa taille size)
//------------------------------------------------------------------------

class List : public Node
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Display ( ) const;
    // Mode d'emploi :
    // Affichage de tous les Trips repertories, en faisant la distinction
    // entre les Composed et les Simple Trips
    // Contrat :
    // la List est non nulle (vérifiée dans le Catalogue)

    void AddTrip ( Trip const * aTrip );
    // Mode d'emploi :
    // Ajoute un Trip en fin de liste pour une liste attribuée à un
    // ComposedTrip, puisqu'on ne veut pas ordonner les SimpleTrip qui
    // composent ce ComposedTrip
    // Contrat :
    // aTrip est un Trip qui remplit les conditions
    // (villes de départ, arrivée, transport : chaines de caractères
    // sans espaces et de moins de 64 caractères de long)

    void AddTripSorted ( Trip const * aTrip );
    // Mode d'emploi :
    // Ajout du Trip pointé par aTrip à la List des Trips
    // Ajout au bon endroit par rapport au tri alphabétique
    // Contrat :
    // aTrip est un Trip qui remplit les conditions
    // (villes de départ, arrivée, transport : chaines de caractères
    // sans espaces et de moins de 64 caractères de long)

    void FetchTrip ( char const * start, char const * end ) const;
    // Mode d'emploi :
    // Comparaison des chaines de caractères en paramètres avec les
    // attributs des Trips pour déterminer si un Trip de start à end
    // existe dans notre List
    // Contrat :
    // Les chaînes de caractères respectent les conditions nécessaires
    // (pas d'espace et moins de 64 caractères)

    bool FetchTripAdvanced ( char const * start, char const * end, Trip * * storedTrips, bool found = false,
                             unsigned int i = 0, bool suite = false ) const;
    // Mode d'emploi :
    // Recherche avancée donc appel récursif afin de trouver une composition de trajets, simple ou composés
    // pour pouvoir répondre à la requete de l'utilisateur
    // start et end représentent respectivement les chaines de caractères des villes de départ et d'arrivée
    // les booléens found et suite déterminent resp. si la requete a été complétée ou si cette requete peut
    // potentiellement être complétée avec une suite de trajets
    // i représente le nombre d'itérations réalisées pour parcourir la liste
    // tab est un pointeur vers des pointeurs de Trip, il repertorie tous les composants
    // d'un trajet qui pourrait potentiellement répondre à la requete de l'utilisateur
    // Contrat :
    // les chaines de caractères des villes de départ et d'arrivée doivent être valides
    // (pas d'espaces et moins de 64 caractères)
    // i doit etre inférieur à la taille de la liste pour poursuivre la recherche

    Node * GetFirst ( ) const;
    // Mode d'emploi :
    // Renvoie le premier Trip de la List ou null si la List est vide

    int GetSize ( ) const;
    // Mode d'emploi :
    // Renvoie la taille de la List donc le nombre de Trips repertories

//-------------------------------------------- Constructeurs - destructeur
    List ( );
    // Mode d'emploi :
    // Création d'une List vide, avec un premier élément nul

    List ( Trip const * aTrip );
    // Mode d'emploi :
    // Initialisation du premier élément de la List
    // aTrip est un pointeur sur ce premier Trip à repertorier
    // Contrat :
    // aTrip est un Trip qui remplit les conditions
    // (villes de départ, arrivée, transport...)

    virtual ~List ( );
    // Mode d'emploi :
    // Libération un à un des espaces mémoire alloués pour les éléments de List

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    Node * first;
    unsigned int size;

};

#endif //LIST_H