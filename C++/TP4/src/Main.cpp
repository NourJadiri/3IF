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
/*
    int retour;

    Analog anal;
    retour = anal.Launch ( argcMain, argvMain );
*/

    return 0;
} //----- Fin de test

int main ( int argc, char * argv [ ] )
// Algorithme :
// Appel à la procédure de test
{
    const string log = "192.168.0.11 - - [08/Sep/2012:12:01:18 +0200] \"GET /notesif HTTP/1.1\" 301 248 \"https://intranet-if.insa-lyon.fr/temps/zizi\" \"Tiny Tiny RSS/1.5.11 (http://tt-rss.org/)\"";

    LogFile_Manager l("../C++/TP4/Logs/short.log");

    Graph g("../C++/TP4/Logs/short.log");

    g.Display();
} //----- fin de main