/*************************************************************************
                           Node  -  description
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

//------------------------------------------------------------------------
// Rôle de la classe <Node>
//
//
//------------------------------------------------------------------------

class Node
{
//----------------------------------------------------------------- PUBLIC

public:
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
    //
    // Contrat :
    //


//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    std::string name; // Nom de la cible
    std::map < Referer, int > referers; // Les différents referers, avec leurs poids
    int hits;
};

#endif // NODE_H