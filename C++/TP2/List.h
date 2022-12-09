/*************************************************************************
                           List  -  SMTGXXXXX
                             -------------------
    début                : 22/11/2022
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER,
                                        Vincent VOIGTLÄNDER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
                           vincent.voigtlander@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <List> (fichier List.h) ----------------
#if ! defined ( LIST_H )
#define LIST_H

//--------------------------------------------------- Interfaces utilisées
#include "Node.h"

//------------------------------------------------------------- Constantes
#define DEFAULT_LIST_SIZE 0

//------------------------------------------------------------------------
// Rôle de la classe <List>
//
//
//------------------------------------------------------------------------

class List : public Node
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Display ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    void AddTrip ( Trip *aTrip );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void FetchTrip ( const char* start, const char* end ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    void Sort ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    Node * GetFirst ( ) const;
    int GetSize ( ) const;

//-------------------------------------------- Constructeurs - destructeur

    List ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    explicit List ( Trip *aTrip );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~List ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    Node *first;
    unsigned int size;
};

#endif //LIST_H
