/*************************************************************************
                           Main  -  lancement du programme
                             -------------------
    début                : 22/11/2022
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Réalisation du module <Main> (fichier Main.cpp) ------------

/////////////////////////////////////////////////////////////////  INCLUDE
//------------------------------------------------------ Include personnel
#include "Main.h"
#include "Catalogue.h"
using namespace std;

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------ Fonctions privées

static void test ( )
// Mode d'emploi :
// Procédure de test appelée par le main
// Algorithme :
// Création d'un catalogue vide lors du lancement de l'application
{
    //Catalogue c;
    //c.Launch ( );
    ofstream tripStream("myTrips.txt");
    SimpleTrip *st1 = new SimpleTrip("Rabat" , "Lyon" , "Plane");
    st1->SaveTripToFile(tripStream);
    st1->Display();
    cout << endl;
} //----- fin de test

int main ( )
// Algorithme :
// Appel à la procédure de test
{
    test ( );
    return 0;
} //----- fin de main