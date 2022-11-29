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
using namespace std;
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int main ( )
// Algorithme :
// Lancement du programme par le système lors de l'execution
// Creation d'un catalogue vide
{
    Trip* st1 = new SimpleTrip("Paris","Lyon","Car");
    Trip* st2 = new SimpleTrip("Lyon","Dresden","Foot");
    cout << st1->GetTransport() << endl;
    List list = List(st1);
    list.AddTrip(st2);

    list.Display();

    return 0;
} //----- Fin de Main