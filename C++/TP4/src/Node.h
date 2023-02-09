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
// Dans ce dernier cas, si le referer n'est pas une page qui a été demandée
// à un certain moment, alors le nombre de hits total sera 0.
// Pour chaque Node, ses referers sont stockés de manière unique dans une map,
// triés par ordre alphabétique.
// Un Node stock aussi le nombre de hits, le nombre de fois total qu'une
// cible a été demandée pour la consultation.
//------------------------------------------------------------------------

class Node
{
//----------------------------------------------------------------- PUBLIC

public:
    friend class Graph;

//----------------------------------------------------- Méthodes publiques
    void AddReferer ( const Referer & aReferer );
    // Mode d'emploi :
    // La méthode permet d'ajouter un nouveau referer aReferer au noeud
    // si celui-ci n'existe pas.
    // Si le referer est déjà renseigné, alors la méthode incrémentera
    // le nombre de fois que ce referer a demandé le noeud
    // Contrat :
    // aReferer n'est pas vide

    void AddReferer ( const Node & aNode );
    // Mode d'emploi :
    // Cette méthode ajoute tous les referers d'un noeud passé en paramètre
    // aNode, à la liste de referers en attribut
    // Cette méthode fait appel à AddReferer ( const string & )
    // Contrat :
    // aNode est un noeud non null, bien formé et existant

    const std::string & GetName ( ) const;
    // Mode d'emploi :
    // Renvoie le nom du Node

    int GetHits ( ) const;
    // Mode d'emploi :
    // Renvoie le nombre de hits du Node

    int GetId ( ) const;
    // Mode d'emploi :
    // Renvoie l'id du Node


//------------------------------------------------- Surcharge d'opérateurs
    friend bool operator < ( Node & a, Node & b );
    // Mode d'emploi :
    // La comparaison entre les deux noeuds en paramètre se fait d'abord
    // en comparant leur nombre de hits
    // Si le nombre de hits est égal, les noeuds sont comparés selon leur ordre
    // alphabétique.
    // Contrat :
    // Les Nodes ne sont pas null, et sont bien formés

    friend std::ostream & operator << ( std::ostream & os, Node & aNode );
    // Mode d'emploi :
    // Affiche le nom du noeud avec le nombre de hits (nombre totale de visites)
    // Contrat :
    // aNode n'est pas null, et est bien formé


//-------------------------------------------- Constructeurs - destructeur
    explicit Node ( );
    // Mode d'emploi (constructeur par défaut) :
    // Constructeur par défaut de Node

    Node ( const Node & aNode );
    // Mode d'emploi (constructeur de copie) :
    // Effectue une copie en profondeur de aNode.
    // Initialise les attributs de this aux mêmes valeurs que les
    // attributs de aNode
    // Contrat :
    // aNode n'est pas null, et est bien formé

    explicit Node ( const Referer & unReferer );
    // Mode d'emploi (constructeur paramétré) :
    // Le constructeur crée un objet Node à partir d'un nom de page unReferer.
    // Le Node représente un referer dans le Graph. Il pourra ne pas
    // avoir de referers à son tour.
    // Contrat :
    // unReferer n'est pas null, et est bien formé

    explicit Node ( const Cible & uneCible, const Referer & unReferer );
    // Mode d'emploi (constructeur paramétré) :
    // Construit un Node à partir d'un nom de cible et du nom d'un referer
    // Les deux paramètres seront stockés dans la map referers
    // Contrat :
    // uneCible et unReferer ne sont pas null

    ~Node ( );
    // Mode d'emploi :
    // Destructeur d'un Node


//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    int id; // l'id (unique) d'un Node
    std::string name; // nom du Node (peut représenter une cible ou un referer)
    std::map < Referer, int > referers; // les différents referers d'un Node, avec leurs poids
    int hits; // nombre total de consultations d'un Node
};

#endif // NODE_H