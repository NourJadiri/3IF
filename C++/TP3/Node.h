/*************************************************************************
                           Node  -  Element de la liste chainee List
                             -------------------
    début                : 22/11/2022
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
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
// Node correspond à un élément de la liste simplement chainee List
// Permet la manipulation de la liste, notamment l'insertion ordonnée
// dans notre cas alphabétiquement
// Node désigne un Trip et a pour attributs un pointeur de ce Trip,
// ainsi qu'un pointeur sur le prochain Node (donc sur le prochain Trip)
//------------------------------------------------------------------------

class Node
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    virtual void Display ( ) const;
    // Mode d'emploi :
    // Appel de Display de la classe Trip pour afficher le Trip de Node
    // Contrat :
    // Node doit bien contenir un Trip valide (et donc etre non null)

    Trip * GetTrip ( ) const;
    // Mode d'emploi :
    // Renvoie le pointeur sur le Trip associé au Node

    Node * GetNext ( ) const;
    // Mode d'emploi :
    // Renvoie le pointeur next sur le prochain Node,
    // donc sur le prochain Trip de la List

    void SetNext ( Node * aNode );
    // Mode d'emploi :
    // Permet d'affecter le prochain Node au Node appelant
    // aNode est un pointeur vers un Node
    // copie en surface
    // Contrat :
    //aNode est un Node valide (donc avec un Trip et un next valides)

//------------------------------------------------- Surcharge d'opérateurs
    virtual bool operator == ( Node const & aNode ) const;
    // Mode d'emploi :
    //Surcharge de l'opérateur == afin de retourner un bool en fonction de
    // si les deux attributs trip des deux Nodes sont égaux
    // aNode est une référence sur le Node à comparer, pas de copie
    // Contrat :
    // les deux attributs trip comparés sont des Trip valides

//-------------------------------------------- Constructeurs - destructeur
    Node ( );
    // Mode d'emploi :
    // Constructeur par défaut d'un Node
    // Initialise les attributs trip et next à nullptr

    Node ( Trip const * aTrip );
    // Mode d'emploi :
    // Constructeur paramétré de Node
    // * trip pointe vers la même zone mémoire que aTrip
    // * next est toujours initialisé à nullptr
    // Contrat :
    // aTrip est un Trip valide

    virtual ~Node ( );
    // Mode d'emploi :
    // Chaque Node supprime son Trip et appelle le destructeur du suivant

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    Trip const * trip; // pointeur sur le Trip du Node
    Node * next; // chainage simple sur le prochain Node, donc sur le prochain Trip

};

#endif // NODE_H