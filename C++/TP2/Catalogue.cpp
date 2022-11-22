/*************************************************************************
                           Catalogue  -  catalogue de tous les trajets
                             -------------------
    début                : 22/11/2022
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER,
                                        Vincent VOIGTLÄNDER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
                           vincent.voigtlander@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Catalogue.h"
#include "List.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Catalogue::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

void Catalogue::Launch ( )
// Algorithme :
//
{
    cout << "\nWelcome to the worst version of Gouggle Mapse :)" << endl;

    while (1)
    {
        cout << "\n==================== Menu. ====================" << endl;
        cout << "Enter a NUMBER corresponding to one of the options listed below" << endl;
        cout << "\t1: display the catalogue" << endl;
        cout << "\t2: add a trip" << endl;
        cout << "\t3: look for a trip" << endl;
        cout << "\t4: close Gouggle Mapse" << endl;

        int choice;
        // pour bien avoir un CHIFFRE et pas une lettre par exemple
        while (true)
        {
            cin >> choice;
            if (!cin)
            {
                cout << "Wrong input, please enter a NUMBER" << endl;
                // pour clear l'erreur
                cin.clear();
                // pour enlever ce qui reste dans le buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;

            }
            else break;
        }

        switch (choice)
        {
            case 1:
                Display();
                break;
            case 2:
                Add();
                break;
            case 3:
                Fetch();
                break;
            case 4:
                goto end;
            default:
                cout << "incorrect choice, please enter a number between 1 and 4" << endl;
                continue; // go back to menu
        }
    }
    end:
    cout << "See you soon on Gouggle Mapse :)" << endl;
} //----- Fin de Launch

void Catalogue::Display (  )
// Algorithme :
//
{
    if (tripList.size == nullptr)
    {
        cout << "there are no trips yet" << endl;
    } else {
        tripList.Display();
    }
    cout << "le display ca marche" << endl;
} //----- Fin de Display

void Catalogue::Add (  )
// Algorithme :
//
{
    tripList.Add();
} //----- Fin de Add

void Catalogue::Fetch (  )
// Algorithme :
//
{
    cout << "le fetch ca marche" << endl;
} //----- Fin de Fetch

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Catalogue>" << endl;
#endif
} //----- Fin de Catalogue


Catalogue::~Catalogue ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Catalogue>" << endl;
#endif
} //----- Fin de Catalogue


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

