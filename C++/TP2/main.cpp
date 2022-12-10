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

using namespace std;
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int main ( )
// Algorithme :
// Lancement du programme par le système lors de l'execution
// Creation d'un catalogue vide
{
    Catalogue c;
    c.Launch();

/*    ComposedTrip *ct = new ComposedTrip();
    ct->AddSimpleTrip(new SimpleTrip("aaa","bbb","ccc"));
    ct->AddSimpleTrip(new SimpleTrip("ddd","eee","fff"));

    cout << ct->GetEnd();*/
    return 0;
} //----- Fin de Main