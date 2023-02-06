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
#include <iostream>
#include <regex>
using namespace std;

//------------------------------------------------------ Include personnel
#include "LogFile_Manager.h"
#include "Main.h"
#include "Analog.h"


///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
static int test ( int & argcMain, char * * & argvMain )
// Mode d'emploi :
// Procédure de test appelée par le main
// Algorithme :
// Création d'un Analog lors du lancement de l'application
{
    Analog anal;
    return anal.Launch ( argcMain, argvMain );
} //----- Fin de test

int main ( int argc, char * argv [ ] )
// Algorithme :
// Appel à la procédure de test
{
    return test(argc,argv);
} //----- fin de main