/*************************************************************************
                           Catalogue  -  repertoire de tous les trajets
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
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Catalogue.h"
#include "List.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Catalogue::Launch ( )
// Algorithme :
// Menu de l'interface utilisateur sur la sortie standard, qui lui
// propose plusieurs options, tant qu'il ne choisit pas de quitter
{
    cout << "\nWelcome to the worst version of Gouggle Mapse :)" << endl;

    int choice;
    while (1)
    {
        cout << "\n-------------------- Menu. --------------------" << endl;
        cout << "Enter a NUMBER corresponding to one of the options listed below" << endl;
        cout << "\t1: display the catalogue of the available trips" << endl;
        cout << "\t2: add a trip" << endl;
        cout << "\t3: look for a trip" << endl;
        cout << "\t4: close Gouggle Mapse" << endl;

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

//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue ( )
// Algorithme :
// Constructeur
{
#ifdef MAP
    cout << "Appel au constructeur de <Catalogue>" << endl;
#endif
} //----- Fin de Catalogue


Catalogue::~Catalogue ( )
// Algorithme :
// Destructeur
{
#ifdef MAP
    cout << "Appel au destructeur de <Catalogue>" << endl;
#endif
} //----- Fin de ~Catalogue


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void Catalogue::Display ( ) const
// Algorithme :
// Affichage du catalogue en appelant la fonction de la classe List
{
    if (tripList.GetSize() == 0)
    {
        cout << "Unfortunately, there are no trips yet..." << endl;
    } else {
        if (tripList.GetSize() > 1)
        {
            cout << "There are " << tripList.GetSize() << " trips ";
        }
        else
        {
            cout << "There is only 1 trip ";
        }
        cout << "available at the moment:" << endl;
        tripList.DisplayTrip();
    }
} //----- Fin de Display

void Catalogue::Add ( )
// Algorithme :
//
{
    char *start = (char*)malloc(sizeof(char)*64);
    char* end = (char*)malloc(sizeof(char)*64);;
    char* transport = (char*)malloc(sizeof(char)*64);;
    cout << "let's add a trip to our beautiful and (in)exhaustive catalogue!" << endl;
    cout << "first things first, !!!DO NOT INSERT SPACES!!! when you write your trip";
    cout << "\n\tinsert the city of departure: ";
    cin >> start;
    int going = 1;
    while (going) {
        cout << "\n\tinsert the kind of transport used: ";
        cin >> transport;
        cout << "\n\tinsert the city of arrival: ";
        cin >> end;
        Trip newTrip = Trip(start, end, transport);
        tripList.AddTrip(newTrip);
        cout << "\ndo you wish to add another trip from the city of arrival? (composed Trip)" << endl;
        cout << "enter 1 for YES or 0 for NO" << endl;
        cin >> going;
        start = end;
    }

} //----- Fin de Add

void Catalogue::Fetch ( ) const
// Algorithme :
//
{
    if (tripList.GetSize() == 0) {
        cout << "Unfortunately, there are no trips yet..." << endl;
    } else {
        cout << "let's find you the best way to get to your destination!" << endl;
        char *start;
        char *end;
        cout << "where do you wanna go to?" << endl;
        cin >> end;
        cout << "and where do you wanna leave from?" << endl;
        cin >> start;
        tripList.FetchTrip(start, end);
    }
} //----- Fin de Fetch