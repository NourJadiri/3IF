/*************************************************************************
                           Node  -  SMTGXXXXXX
                             -------------------
    début                : 22/11/2022
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER,
                                        Vincent VOIGTLÄNDER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
                           vincent.voigtlander@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Node> (fichier Node.h) ----------------
#if ! defined ( NODE_H )
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
    virtual void Display ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    Node * GetNext ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    Trip * GetTrip ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void SetNext ( Node * aNode );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs
    bool operator == ( const Node & aNode ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

//-------------------------------------------- Constructeurs - destructeur
    Node ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

   explicit Node ( Trip * aTrip );
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
    Trip * trip;
    Node * next;

};

#endif // NODE_H

