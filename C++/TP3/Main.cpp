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
//-------------------------------------------------------- Include système
using namespace std;

//------------------------------------------------------ Include personnel
#include "Main.h"
#include "Catalogue.h"
#include "ComposedTrip.h"
#include "CatalogueUtils.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------ Fonctions privées

static void test ( )
// Mode d'emploi :
// Procédure de test appelée par le main
// Algorithme :
// Création d'un catalogue vide lors du lancement de l'application
{
    Catalogue c;
    c.Launch ( );

/*    ComposedTrip * ct = new ComposedTrip();

    SimpleTrip *st1 = new SimpleTrip("aaa","bbb","ccc");
    SimpleTrip *st2 = new SimpleTrip("eee","ccc","ccc");

    ct->AddSimpleTrip(st1),ct->AddSimpleTrip(st2);

    ct->Display();
    cout << endl;
    cout << ct->IsValid() << endl;*/
} //----- Fin de test

int main ( )
// Algorithme :
// Appel à la procédure de test
{
    test ( );
    return 0;
} //----- Fin de main