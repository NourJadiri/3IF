/*************************************************************************
                           CatalogueUtils  -  gestion des separateurs
                             -------------------
    début                : 04/01/2023
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <CatalogueUtils> (fichier CatalogueUtils.h) ----------------
#if ! defined ( CATALOGUEUTILS_H )
#define CATALOGUEUTILS_H

//--------------------------------------------------- Interfaces utilisées
#include "Catalogue.h"

//------------------------------------------------------------------------
// Rôle de la classe <CatalogueUtils>
// La classe permet de
//
//------------------------------------------------------------------------


int countSeparators ( std::string & s, char separator );

std::string * split ( std::string & s, char separator );

int findNextTripIndex( std::ifstream & tripStream );
// Mode d'emploi :
// Cette fonction retourne le prochain indice d'un potentiel trajet
// qui pourrait s'ajouter au catalogue.


#endif // CATALOGUEUTILS_H



///est ce que cest une classe?