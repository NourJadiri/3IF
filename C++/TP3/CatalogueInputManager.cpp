#include "Catalogue.h"
#include "ComposedTrip.h"


#include <fstream>
//#include <limits>

using namespace std;


//----------------------------------------------------- Méthodes ordinaires

void importComposedTrip (Catalogue * c, ifstream & tripStream , string * data , string & trip ,int tripIndex )
{
    ComposedTrip *composedTrip = new ComposedTrip();

    while(getline(tripStream , trip) && !trip.empty())
    {
        data = split(trip , ',');

        if(data[0] != "0") break;

        composedTrip->AddSimpleTrip(new SimpleTrip(data[2].c_str(),data[3].c_str(),data[4].c_str()));

    }

    if(composedTrip->IsValid()) {
        c->tripList.AddTripSorted(composedTrip);
    }
    else
    {
        cout << "Composed trip number " << tripIndex << " is not valid..." << " " << "Not saving it..." << endl;
        delete composedTrip;
    }

}

void importSimpleTrip( Catalogue * c, ifstream &tripStream, std::string *data, string & trip )
{
    c->tripList.AddTripSorted(new SimpleTrip(data[2].c_str(), data[3].c_str(), data[4].c_str()));
}

//------------------------------------------------------------------ Méthodes protégées

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

        int tripIndex = stoi(data[0]);

        if(data[1] == "Simple" && data[0] != "0")
            importSimpleTrip(this,tripStream,data,trip);

        else if(data[1] == "Composed")
            importComposedTrip( this , tripStream , data , trip , tripIndex);

        //cout << "Current pointed trip : " << trip << endl;

        delete[ ] data;
    }

    tripStream.clear();
    tripStream.seekg(0);
}

void Catalogue::importTripsFromType( ifstream & tripStream )
{
    cout << "Please enter the type of trips you want to import from the file : " << endl << "\t(1) Simple Trip" << endl << "\t(2) Composed Trip" << endl << "\t(3) Cancel" << endl;

    int type;

    do {
        cin >> type;

        /// Commented code checks if the input is numeric (not asked in the specifications)
/*      if(!cin)
        {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Input must be purely numeric, please try again..."<<endl;
            continue;
        }*/

        if((type != 3 && type != SIMPLE_TRIP && type != COMPOSED_TRIP))
        {
            cout << "Invalid input, please use 1 for Simple Trips, 2 for Composed Trips or 3 to Cancel your import..." << endl;
        }

    } while(!cin || (type != 3 && type != SIMPLE_TRIP && type != COMPOSED_TRIP));

    if( type == SIMPLE_TRIP )
    {
        this->importAllSimpleTrips( tripStream );
    }

    else if( type == COMPOSED_TRIP )
    {
        this->importAllComposedTrips( tripStream );
    }
    else
    {
        cout << "Cancelling..." << endl;
        return;
    }
}

void Catalogue::importAllSimpleTrips ( ifstream & tripStream )

{
    string trip;

    while (tripStream.good())
    {
        getline(tripStream,trip);

        if(trip.empty()) continue;

        string * data = split(trip,',');

        if(data[1] == "Simple" && data[0] != "0")
            importSimpleTrip(this,tripStream,data,trip);

        delete[ ] data;
    }

    tripStream.clear();
    tripStream.seekg(0);
}

void Catalogue::importAllComposedTrips (ifstream & tripStream )

{
    string trip;

    while(tripStream.good())
    {
        getline(tripStream,trip);

        if(trip.empty()) continue;

        string * data = split(trip,',');

        int tripIndex = stoi(data[0]);

        if(data[1] == "Composed")
            importComposedTrip(this , tripStream , data , trip , tripIndex);

        delete [ ] data;
    }

    tripStream.clear();
    tripStream.seekg(0);
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
}

//----- Fin de importCities
