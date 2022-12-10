/*************************************************************************
                           List  -  description
                             -------------------
    début                : 22/11/2022
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER,
                                        Vincent VOIGTLÄNDER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
                           vincent.voigtlander@insa-lyon.fr
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
////////////// A COMPLETER
//
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
    // Ajout du Trip pointé par aTrip à la List des Trips
    // Ajout au bon endroit par rapport au tri alphabétique
    // Contrat :
    // aTrip est un Trip qui remplit les conditions
    // (villes de départ, arrivée, transport...)

    void FetchTrip ( char const * start, char const * end ) const;
    // Mode d'emploi :
    // Comparaison des chaines de caractères en paramètres avec les
    // attributs des Trips pour déterminer si un Trip de start à end
    // existe dans notre List
    // Contrat :
    // Les chaînes de caractères respectent les conditions nécessaires
    // (pas d'espace et moins de 64 caractères)


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
    // Libération de l'espace mémoire alloué pour les éléments de List

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    Node * first;
    unsigned int size;

};

#endif //LIST_H
