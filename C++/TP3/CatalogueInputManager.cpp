/*************************************************************************
                           CatalogueInputManager  -  gestion des imports
                             -------------------
    début                : 04/01/2023
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <CatalogueInputManager> (fichier CatalogueInputManager.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <fstream>

//------------------------------------------------------ Include personnel
#include "Catalogue.h";

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void Catalogue::importAll ( ifstream & tripStream )
// Algorithme :
//
{
    string trip;
    getline( tripStream, trip );

    string * data = split( trip, ',' );

    this->tripList.AddTripSorted( new SimpleTrip( data[2].c_str(), data[3].c_str(), data[4].c_str() ) );

    delete [ ] data;
} //----- Fin de importAll

void Catalogue::importCities ( )
// Algorithme :
// XXXX
{
    int choice;
    for ( ; ; ) {
        cout << endl << "Enter a NUMBER corresponding to one of the options listed below" << endl;
        cout << "\t1: import trips leaving from a certain city" << endl;
        cout << "\t2: import trips arriving at a certain city" << endl;
        cout << "\t3: import trips both leaving and arriving to the cities you want" << endl;

        cin >> choice;

        switch ( choice ) {
            case 1:
                //TODO : import trips a partir d'une ville de depart
                break;
            case 2:
                //TODO : import trips a partir d'une ville d'arrivee
                break;
            case 3:
                //TODO : import trips a partir des deux villes de depart & arrivee
                break;
            default:
                cout << endl << "Incorrect choice, please enter a number between 1 and 3!" << endl;
                //sleep(1);
                continue; // go back to options
        }
        break;
    }
} //----- Fin de importCities
