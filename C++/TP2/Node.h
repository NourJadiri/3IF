/*************************************************************************
                           Node  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Node> (fichier Node.h) ----------------
#include <iostream>
#include "Trip.h"

#ifndef NODE_H
#define NODE_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Node>
//
//
//------------------------------------------------------------------------

class Node {
//----------------------------------------------------------------- PUBLIC

protected:
    Trip trip;
    Node *next;

public:
//-------------------------------------------- Constructeurs - destructeur
    //Node();

    virtual ~Node ( );

    explicit Node (const Trip & aTrip = Trip());

//-------------------------------------------- Member methods
    Node* getNext();

    Trip getTrip();

    void setNext(Node * aNode);

    virtual void Display() const;

    bool operator== (const Node & aNode) const;
};

//-------------------------------- Autres définitions dépendantes de <Node>

#endif // NODE_H

