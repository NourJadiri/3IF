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
#include <iostream>

//------------------------------------------------------------------------
// Rôle de la classe <CatalogueUtils>
// La classe permet de
//
//------------------------------------------------------------------------


int countSeparators ( std::string &, char );

std::string * split ( std::string &, char );


#endif // CATALOGUEUTILS_H



///est ce que cest une classe?
