/*************************************************************************
                           Main  -  description
                             -------------------
    début                : 17/01/2023
    copyright            : (C) 2023 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Réalisation du module <Main> (fichier Main.cpp) ---------------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
using namespace std;

//------------------------------------------------------ Include personnel
#include "Main.h"
#include "Analog.h"


///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------ Fonctions privées
static int test ( int & argcMain, char * * & argvMain )
// Mode d'emploi :
// Procédure de test appelée par le main
// Algorithme :
// Création d'un Analog lors du lancement de l'application
{
    Analog anal;
    return anal.Launch ( argcMain, argvMain );
    return 0;
} //----- Fin de test

int main ( int argc, char * argv [ ] )
// Algorithme :
// Appel à la procédure de test
{
/*    bool commandes[5] = { false , false , false , false , false };

    commandes[G] = true;

    auto l = make_shared < Connections > ( "../C++/TP4/Logs/short.log" );

    l->Init( commandes );

    Graph graph ( l );

    cout << graph;*/

    return test ( argc, argv );
} //----- fin de main