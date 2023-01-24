/*************************************************************************
                           Main  -  description
                             -------------------
    début                : 17/01/2023
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER
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
#include "Analog.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
static int test ( int & argcMain, char * * & argvMain )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{
    int retour;

    Analog anal;
    retour = anal.Launch ( argcMain, argvMain );
    return retour;
} //----- Fin de test

int main ( int argc, char * argv [ ] )
// Algorithme :
// Appel à la procédure de test
{
    //const string log = "192.168.0.11 - - [08/Sep/2012:12:01:18 +0200] \"GET /notesif HTTP/1.1\" 301 248 \"https://intranet-if.insa-lyon.fr/temps/zizi\" \"Tiny Tiny RSS/1.5.11 (http://tt-rss.org/)\"";
/*    Log * aLog = new Log(log);

    cout << aLog->getLongReferer() << endl;

    cout << getPathFromUrl( aLog->getLongReferer() ) << endl;

    cout << aLog->getShortReferer() << endl;

    cout << aLog->getDocumentRequested() << endl;

    cout << aLog->getHeureConsultation() << endl;

    cout << aLog->getReturnCode() << endl;

    delete aLog;*/
/*    LogFile_Manager fileManager("../C++/TP4/Logs/short.log");

    fileManager.Display();*/

    int retour;
    retour = test ( argc, argv );
    return retour;
} //----- fin de main