/*************************************************************************
                           CatalogueUtils  -  gestion des separateurs
                             -------------------
    début                : 04/01/2023
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la librairie <CatalogueUtils> (fichier CatalogueUtils.h) ----------------
#if ! defined ( CATALOGUEUTILS_H )
#define CATALOGUEUTILS_H

//--------------------------------------------------- Interfaces utilisées
//#include "Catalogue.h"

//------------------------------------------------------------------------
// Rôle de la librairie <CatalogueUtils>
// La librairie permet de gérer le format dans un fichier d'un trip
// Elle permet notamment de distinguer les différentes informations d'un
// trajet, mais aussi de trouver l'indice du dernier trajet qui a été
// écrit dans le fichier, afin de reprendre la numérotation au bon
// chiffre lors de l'écriture, mais aussi afin de déterminer le nombre de
// trajets disponibles dans le fichier pour pouvoir avoir la borne
// maximale lors de l'importation par intervalle
// Enfin, elle permet de veiller à la bonne utilisation de l'application
// en empechant l'utilisateur de rentrer le caractère ',' dans une ville
//------------------------------------------------------------------------

//-------------------------------------------------------------- Fonctions
int countSeparators ( std::string & s, char separator );
// Mode d'emploi :
// Cette fonction permet de généraliser la fonction split en comptant
// le nombre de séparateurs 'separators' sur une ligne d'un fichier 's'

std::string * split ( std::string & s, char separator );
// Mode d'emploi :
// Cette fonction permet de séparer les informations d'un trajet 's' écrit
// dans un fichier, et stocker ses informations dans le tableau de string
// qu'elle retourne
// les informations sont, dans l'ordre : l'index (numéro), le type, la ville
// de depart, la ville d'arrivée (finale pour un composedTrip) et le moyen de
// transport ('-' pour un composedTrip)

int findNextTripIndex( std::ifstream & tripStream );
// Mode d'emploi :
// Cette fonction retourne le prochain indice d'un potentiel trajet
// qui pourrait s'ajouter au catalogue afin de poursuivre la numerotation
// lors de l'ecriture.
// elle permet egalement de savoir combien il y a de trips dans un fichier
// afin de determiner la borne maximale que l'utilisateur peut rentrer
// lors d'un import par intervalle
// Contrat :
// tripStream est un flux d'entrée valide, i.e. : le fichier existe et n'est pas vide ou corrompu

string inputValidString ( const string & label );
// Mode d'emploi :
// La fonction renvoie un string qui contient les informations
// que l'utilisateur a entrées.
// Le paramètre label permet d'avoir un affichage sur la console
// plus personnalisé.
// Contrat :
// L'utilisateur ne doit pas renseigner de caractère " " (espace)
// au risque de comprommettre le flux d'entrée standard.

#endif // CATALOGUEUTILS_H