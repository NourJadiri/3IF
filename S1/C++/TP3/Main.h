/*************************************************************************
                           Main  -  lancement du programme
                             -------------------
    début                : 22/11/2022
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Interface du module <Main> (fichier Main.h) -------------------
#if ! defined ( MAIN_H )
#define MAIN_H

//------------------------------------------------------------------------
// Rôle du module <Main>
// Ce module permet le lancement du programme par le système lors de
// l'exécution, à travers l'appel à une procédure test
//------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------ Fonctions privées
static void test ( );
// Mode d'emploi :
// Procédure de test appelée par la fonction Main
// Permet de mieux tracer les destructeurs à la fin de l'éxécution de
// l'application

int main ( );
// Mode d'emploi :
// Appelle la procédure test

#endif // MAIN_H