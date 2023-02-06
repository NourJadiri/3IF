/*************************************************************************
                           Node  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Node> (fichier Node.h) ----------------
#if ! defined ( NODE_H )
#define NODE_H

//--------------------------------------------------- Interfaces utilisées
#include "LogFile_Manager.h"
#include <map>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

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

    void AddReferer( const Referer & aReferer );

    void AddReferer( const Node & aNode );

    void Display( ) const;

    const std::string & GetName ( ) const ;


//------------------------------------------------- Surcharge d'opérateurs

    friend bool operator < ( Node & a , Node & b );

    friend std::ostream & operator<< ( std::ostream & os , Node & aNode );

//-------------------------------------------- Constructeurs - destructeur
    explicit Node ();

    explicit Node ( const Cible & uneCible );

    Node ( const Node & aNode );

    explicit Node ( const Cible & uneCible, const Referer & unReferer );

    ~Node ( );
//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    std :: string name; // Nom de la cible
    std :: map <Referer , int > referers; // Les différents réferers, avec leurs poids
    int hits;
public:
    int getHits() const;
};

//-------------------------------- Autres définitions dépendantes de <Node>



#endif // NODE_H

