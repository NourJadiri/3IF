/*************************************************************************
                           Node  -  description
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
// Node correspond aux éléments de la liste simplement chainee List
/// Elle permet notamment de JSP
//------------------------------------------------------------------------

class Node
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    virtual void Display ( ) const;
    // Mode d'emploi :
    // Appel de la méthode de la classe Trip pour afficher le Trip de Node
    // Contrat :
    // Le Trip doit être non nul

    Trip * GetTrip ( ) const;
    // Mode d'emploi :
    // Renvoie un pointeur sur le Trip associé au Node
    // Contrat :
    //

    Node * GetNext ( ) const;
    // Mode d'emploi :
    // Renvoie un pointeur sur le prochain Node,
    // donc sur le prochain Trip de la List
    // Contrat :
    //

    void SetNext ( Node * aNode );
    // Mode d'emploi :
    // Permet d'affecter le prochain Node au Node appelant
    // aNode est un pointeur vers un Node
    // copie en surface
    // Contrat :
    // aNode est un Node valide (donc avec un Trip et un next valides)

//------------------------------------------------- Surcharge d'opérateurs
    virtual bool operator == ( Node const & aNode ) const;
    // Mode d'emploi :
    // Surcharge de l'opérateur == afin de retourner un bool en fonction de
    // si les deux trip de deux Nodes sont égaux
    // aNode est une référence sur le Node a comparer, pas de copie
    // Contrat :
    // les deux trip comparés sont des Trip valides

//-------------------------------------------- Constructeurs - destructeur
    Node ( );
    // Mode d'emploi :
    /// A COMPLETER
    // Contrat :
    //

    Node ( Trip const * aTrip );
    // Mode d'emploi :
    /// A COMPLETER
    // Contrat :
    //

    virtual ~Node ( );
    // Mode d'emploi :
    // Chaque Node delete son Trip et le suivant

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    Trip const * trip; // Pointeur sur le Trip du Node
    Node * next; // Chainage simple sur le prochain Node, donc sur le prochain Trip

};

#endif // NODE_H

