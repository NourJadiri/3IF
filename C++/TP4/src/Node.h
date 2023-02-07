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
#include "LogFile_Manager.h"
#include <map>

//TODO TOUS LES COMMENTAIRES
//------------------------------------------------------------------------
// Rôle de la classe <Node>
//
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
    //
    // Contrat :
    //

    void AddReferer ( const Node & aNode );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void Display ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    const std::string & GetName ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    int GetHits ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    int GetId ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs
    friend bool operator < ( Node & a, Node & b );
    // Mode d'emploi :
    //
    // Contrat :
    //

    friend std::ostream & operator << ( std::ostream & os, Node & aNode );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    explicit Node ( );
    // Mode d'emploi (constructeur par défaut) :
    //
    // Contrat :
    //

    Node ( const Node & aNode );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    explicit Node ( const Cible & uneCible );
    // Mode d'emploi (constructeur parametre) :
    //
    // Contrat :
    //

    explicit Node ( const Cible & uneCible, const Referer & unReferer );
    // Mode d'emploi (constructeur parametre) :
    //
    // Contrat :
    //

    ~Node ( );
    // Mode d'emploi :
    // Destructeur d'un Node


//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    int id; // l'id (unique) d'un noeud
    std::string name; // nom de la cible
    std::map < Referer, int > referers; // les differents referers d'un noeud, avec leurs poids
    int hits; // nombre total de consultations d'un noeud
};

#endif // NODE_H