
#include "CatalogueInputManager.h"
#include "Catalogue.h"
#include "ComposedTrip.h"


#include <fstream>

using namespace std;


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void Catalogue::importAll ( ifstream & tripStream )
// Algorithme :
//
{

    string trip;


    while(tripStream.good())
    {

        getline(tripStream , trip);

        if(trip.empty()) continue;

        string * data = split(trip, ',');

        if(data[1] == "Simple" && data[0] != "0")
        {
            this->tripList.AddTripSorted(new SimpleTrip(data[2].c_str(), data[3].c_str(), data[4].c_str()));
        }
        else if(data[1] == "Composed")
        {
            ComposedTrip *composedTrip = new ComposedTrip();

            // This SimpleTrip will be useful to check if our composed trip is valid

            SimpleTrip *temp = new SimpleTrip(data[2].c_str(), data[3].c_str(), data[4].c_str());

            while(getline(tripStream , trip) && !trip.empty())
            {
                data = split(trip , ',');

                if(data[0] != "0") break;

                composedTrip->AddSimpleTrip(new SimpleTrip(data[2].c_str(),data[3].c_str(),data[4].c_str()));

            }

            if(composedTrip->IsValid()) {
                cout << composedTrip->IsValid() << endl;
                this->tripList.AddTripSorted(composedTrip);
            }
            else
            {
                cout << "Composed trip number " << data[0] << " is not valid..." << endl << "Not saving it..." << endl;
                delete composedTrip;
            }
        }

        cout << "Current pointed trip : " << trip << endl;

        delete[ ] data;
    }
}


void Catalogue::importCities ( )
// Algorithme :
// XXXX
{
    int choice;
    for ( ; ; ) {
        cout << endl << "Enter a NUMBER corresponding to one of the options listed below" << endl;
        cout << "\t1: import trips leaving from a certain city" << endl;
        cout << "\t2: import trips arriving at a certain city" << endl;
        cout << "\t3: import trips both leaving and arriving to the cities you want" << endl;

        cin >> choice;

        switch ( choice ) {
            case 1:
                //TODO : import trips a partir d'une ville de depart
                break;
            case 2:
                //TODO : import trips a partir d'une ville d'arrivee
                break;
            case 3:
                //TODO : import trips a partir des deux villes de depart & arrivee
                break;
            default:
                cout << endl << "Incorrect choice, please enter a number between 1 and 3!" << endl;
                //sleep(1);
                continue; // go back to options
        }
        break;
    }
} //----- Fin de importCities
