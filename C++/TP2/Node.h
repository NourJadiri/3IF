/*************************************************************************
                           Node  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Node> (fichier Node.h) ----------------
#ifndef NODE_H
#define NODE_H

//--------------------------------------------------- Interfaces utilisées

#include <iostream>
#include "Trip.h"
#include "SimpleTrip.h"

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
    Node* getNext ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    Trip* getTrip ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void setNext ( Node* aNode );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual void Display() const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool operator== (const Node & aNode) const;
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    explicit Node ( Trip *aTrip );
    // Mode d'emploi :
    //
    // Contrat :
    //

    Node ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Node ( );
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    Trip *trip;
    Node *next;

};

#endif // NODE_H

