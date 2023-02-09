/*************************************************************************
                           Node  -  élément d'un Graph
                             -------------------
    début                : 17/01/2023
    copyright            : (C) 2023 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Node> (fichier Node.h) ----------------
#if ! defined ( NODE_H )
#define NODE_H

//--------------------------------------------------- Interfaces utilisées
#include <map>
#include "Connections.h"

//------------------------------------------------------------------------
// Rôle de la classe <Node>
// Un Node est l'élément qui représente une page web.
// Ce noeud possède un certain nombre de referers, pages à partir
// desquelles on a cherché à atteindre ce Node.
// Un Node peut être une cible (avec tous les hits) ou un Referer.
// Dans ce dernier cas, si le referer n'est pas une page qui a été demandé aussi
// alors le nombre de hits total sera 0.
// Pour chaque Node, ses referers sont stockés de manière unique dans une map,
// triés par ordre alphabétique.
// Un Node stock aussi le nombre de hits, ou le nombre de fois total qu'une
// cible a été demandée pour la consultation.
//
//------------------------------------------------------------------------

class Node
{
//----------------------------------------------------------------- PUBLIC

public:
    friend class Graph;

//----------------------------------------------------- Méthodes publiques
    void AddReferer ( const Referer & aReferer );
    // Mode d'emploi :
    // La méthode permet d'ajouter un nouveau referer au noeud si celui-ci
    // n'existe pas.
    // Si le referer est déjà renseigné, alors la méthode incrémentera
    // le nombre de fois que ce referer a demandé le noeud
    // Contrat :
    // aReferer n'est pas vide

    void AddReferer ( const Node & aNode );
    // Mode d'emploi :
    // Cette méthode ajoute tous les referers d'un noeud passé en paramètre
    // à la liste de referers en attribut.
    // Cette méthode fait appel à AddReferer(const string &)
    // Contrat :
    //

    void Display ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    const std::string & GetName ( ) const;
    // Mode d'emploi :
    // Retourne le nom du noeud
    // Contrat :
    //

    int GetHits ( ) const;
    // Mode d'emploi :
    // Retourne le nombre de hits du Noeud
    // Contrat :
    //

    int GetId ( ) const;
    // Mode d'emploi :
    // Retourne l'id du noeud
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs
    friend bool operator < ( Node & a, Node & b );
    // Mode d'emploi :
    // La comparaison entre deux noeuds d'abord en comparant leur nombre de hits d'abord.
    // Si le nombre de hits est égal, les noeuds sont comparé selon leur ordre
    // lexicographique.
    // Contrat :
    // Aucun des noeuds passés en paramètre n'est NULL

    friend std::ostream & operator << ( std::ostream & os, Node & aNode );
    // Mode d'emploi :
    // Affiche le nom du noeud avec le nombre de hits (nombre totale de visites)
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    explicit Node ( );
    // Mode d'emploi (constructeur par défaut) :
    // Constructeur par défaut de Node
    // Contrat :
    //

    Node ( const Node & aNode );
    // Mode d'emploi (constructeur de copie) :
    // Effectue une copie en profondeur de aNode.
    // Initialise les attributs de <this> aux mêmes valeurs que les
    // attributs de aNode
    // Contrat :
    //

    explicit Node ( const Referer & unReferer );
    // Mode d'emploi (constructeur parametre) :
    // Le constructeur crée un objet Node à partir d'un nom de page seulement.
    // Le Noeud représentera un referer dans notre graph. Il pourra ne pas
    // avoir de referers à son tour.
    // Contrat :
    //

    explicit Node ( const Cible & uneCible, const Referer & unReferer );
    // Mode d'emploi (constructeur parametre) :
    // Construit un Noeud à partir d'un nom de cible et du nom d'un referer
    // Les eux parametres seront stockés dans la map referers
    // Contrat :
    //

    ~Node ( );
    // Mode d'emploi :
    // Destructeur d'un Node


//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    int id; // l'id (unique) d'un noeud
    std::string name; // nom du noeud (peut représenter une cible ou un referer
    std::map < Referer, int > referers; // les differents referers d'un noeud, avec leurs poids
    int hits; // nombre total de consultations d'un noeud
};

#endif // NODE_H