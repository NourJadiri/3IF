/*************************************************************************
                           Trip  -  Objet d'un trajet en général
                             -------------------
    début                : 03/01/2023
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Trip> (fichier Trip.h) ----------------
#if ! defined ( TRIP_H )
#define TRIP_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <fstream>
#include <cstring>

//------------------------------------------------------------------ Types
enum types { VIRTUAL, SIMPLE_TRIP, COMPOSED_TRIP };
const std::string tripTypes [ 3 ] = { "V" , "S" , "C" };

//------------------------------------------------------------------------
// Rôle de la classe <Trip>
// Trip est la clase Mère des deux classes filles SimpleTrip et ComposedTrip
// Trip est un trajet entre une ville de départ et d'arrivée, qui peut
// avoir des escales si c'est un ComposedTrip
// Classe abstraite afin de gérer les deux différents types de Trip
// sans distinction de leur nature
// On retrouve donc trois différents types de Trip :
// Virtual par défaut lors de la construction d'un Trip
// Simple_Trip si le Trip ne comporte pas d'escale
// Composed_Trip si le Trip comporte une ou plusieurs escales
// un trajet, qu'il soit simple ou composé, a une ville de départ et
// d'arrivée, donc deux chaines de caractères start et end respectivement
// Enfin, elle permet de commencer l'écriture d'un trajet, peu importe
// son type
//------------------------------------------------------------------------

class Trip
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    virtual void Display ( ) const = 0;
    // Mode d'emploi :
    // Méthode virtuelle pure, donc méthode définie dans les classes filles
    // SimpleTrip et ComposedTrip

    virtual char * GetStart ( ) const;
    // Mode d'emploi :
    // Renvoie une chaine de caractères correspondant à la ville de départ
    // du Trip, qu'il soit Composed ou Simple
    // Contrat :
    // La chaine de caractères doit être valide (pas d'espaces et moins de
    // 64 caractères)

    virtual char * GetEnd ( ) const;
    // Mode d'emploi :
    // Renvoie une chaine de caractères correspondant à la ville d'arrivée
    // du Trip, qu'il soit Composed ou Simple
    // Contrat :
    // La chaine de caractères doit être valide (pas d'espaces et moins de
    // 64 caractères)

    virtual int GetType ( ) const;
    // Mode d'emploi :
    // Renvoie l'entier correspondant au type du Trip (Virtual, Simple ou
    // Composed)

    virtual void SaveTripToFile ( std::ofstream & tripStream );
    // Mode d'emploi :
    // Ecriture du type du trajet ainsi que de ses villes de depart et d'arrivée
    // Contrat :
    // tripStream est un flux de sortie valide, i.e. : le fichier existe ou est créé et n'est pas corrompu

    //------------------------------------------------- Surcharge d'opérateurs
    virtual bool operator == ( Trip const & aTrip ) const;
    // Mode d'emploi :
    // Surcharge de l'opérateur == afin de retourner un bool en fonction de
    // si les deux Trip sont égaux sans distinction de leur type
    // aTrip est une référence sur le Trip à comparer, pas de copie
    // Contrat :
    // les deux Trips comparés sont des Trips qui remplissent les conditions
    // (villes de départ, arrivée, transport : chaines de caractères
    // sans espaces et de moins de 64 caractères de long)

    virtual bool operator <= ( Trip const & aTrip ) const;
    // Mode d'emploi :
    // Surcharge de l'opérateur <= afin de retourner un bool en fonction de
    // si Trip est inférieur ou égal à aTrip
    // aTrip est une référence sur le Trip à comparer, pas de copie
    // Contrat :
    // les deux Trips comparés sont des Trips qui remplissent les conditions
    // (villes de départ, arrivée, transport : chaines de caractères
    // sans espaces et de moins de 64 caractères de long)

    virtual bool operator >= ( Trip const & aTrip ) const;
    // Mode d'emploi :
    // Surcharge de l'opérateur >= afin de retourner un bool en fonction de
    // si Trip est supérieur ou égal à aTrip
    // aTrip est une référence sur le Trip à comparer, pas de copie
    // Contrat :
    // les deux Trips comparés sont des Trips qui remplissent les conditions
    // (villes de départ, arrivée, transport : chaines de caractères
    // sans espaces et de moins de 64 caractères de long)

//-------------------------------------------- Constructeurs - destructeur
    Trip ( );
    // Mode d'emploi :
    // Constructeur par défaut d'un Trip sans paramètres

    Trip ( char const *  start, char const * end );
    // Mode d'emploi :
    // Allocations dynamiques pour les chaines de caractères communes aux
    // différents types de Trips
    // Copie en profondeur des paramètres, qui sont des pointeurs vers des
    // chaines de caractères correspondant respectivement aux villes de
    // départ et arrivée d'un Trip
    // Par défaut, le type du Trip construit est Virtual
    // Contrat :
    // Les chaines de caractères doivent être valides (pas d'espaces et moins
    // de 64 caractères)

    Trip ( Trip const & aTrip );
    // Mode d'emploi :
    // Allocations dynamiques pour les chaines de caractères communes aux
    // différents types de Trips
    // Copie en profondeur des attributs du Trip en paramètre
    // aTrip est une référence du Trip à partir duquel on doit construire
    // un Trip
    // Par défaut, le type du Trip construit est Virtual
    // Contrat :
    // aTrip est un Trip qui remplit les conditions
    // (villes de départ, arrivée, transport : chaines de caractères
    // sans espaces et de moins de 64 caractères de long)

    virtual ~Trip ( );
    // Mode d'emploi :
    // Suppression des zones mémoire allouées dynamiquement pour les chaines
    // de caractères communes à tous les types de Trip (donc villes de départ
    // et d'arrivée)

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    char * start;
    char * end;
    int type;

};

#endif //TRIP_H