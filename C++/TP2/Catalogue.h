/*************************************************************************
                           Catalogue  -  repertoire de tous les trajets
                             -------------------
    début                : 22/11/2022
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER,
                                        Vincent VOIGTLÄNDER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
                           vincent.voigtlander@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------------
#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H

//--------------------------------------------------- Interfaces utilisées
#include "List.h"

//------------------------------------------------------------------------
// Rôle de la classe <Catalogue>
//
//
//------------------------------------------------------------------------

class Catalogue
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Launch ( );
    // Mode d'emploi :
    // suivre les instructions qui apparaissent sur la sortie standard
    // donc entrer un chiffre entre 1 et 4
    // Contrat :
    // il faut entrer un CHIFFRE

//-------------------------------------------- Constructeurs - destructeur
    Catalogue ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Catalogue ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    virtual void Display ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    void Add ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void Fetch ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

//----------------------------------------------------- Attributs protégés
    List tripList;

};

#endif // CATALOGUE_H