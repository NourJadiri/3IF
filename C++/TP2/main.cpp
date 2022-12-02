/*************************************************************************
                           Main  -  lancement du programme
                             -------------------
    début                : 22/11/2022
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER,
                                        Vincent VOIGTLÄNDER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
                           vincent.voigtlander@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Main> (fichier Main.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//------------------------------------------------------ Include personnel
#include "Catalogue.h"
#include "SimpleTrip.h"
#include "ComposedTrip.h"
using namespace std;
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int main ( )
// Algorithme :
// Lancement du programme par le système lors de l'execution
// Creation d'un catalogue vide
{
/*
    Catalogue c;
    c.Launch();
*/
    List list = List(new SimpleTrip("Paris","Lyon","Car"));
    list.AddTrip(new SimpleTrip("Lyon","Metz","Car"));

    Trip *ct = new ComposedTrip(list);
    Trip *st = new SimpleTrip("Rabat","Casa","Car");
    Trip *st2 = new SimpleTrip("Rabat","Marrakech","Car");

    List tripList = List(ct);
    tripList.AddTrip(st);
    tripList.AddTrip(st2);

    tripList.Display();

    return 0;
} //----- Fin de Main