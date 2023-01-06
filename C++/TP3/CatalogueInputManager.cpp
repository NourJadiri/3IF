/*************************************************************************
                           CatalogueInputManager  -  gestion des imports
                             -------------------
    début                : 04/01/2023
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Fichier source <CatalogueInputManager> (fichier CatalogueInputManager.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <fstream>
//#include <limits>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Catalogue.h"
#include "ComposedTrip.h"

//------------------------------------------------------------------ PRIVE

//--------------------------------------------------------- Méthodes amies
void importComposedTrip ( Catalogue * c, ifstream & tripStream, string * data, string & trip, int tripIndex )
// Generic method that allows to import a single composedTrip into a catalogue C
{
    ComposedTrip * composedTrip = new ComposedTrip();

    while ( getline( tripStream, trip ) && !trip.empty() )
    {
        data = split( trip , ',' );

        if ( data[0] != "0" ) break;

        composedTrip->AddSimpleTrip( new SimpleTrip( data[2].c_str(),
                                                     data[3].c_str(), data[4].c_str() ) );
    }

    if ( composedTrip->IsValid() )
    {
        c->tripList.AddTripSorted( composedTrip );
    }
    else
    {
        cout << "Composed trip number " << tripIndex << " is not valid... Not saving it..." << endl;
        delete composedTrip;
    }
} //----- Fin de importComposedTrip

void importSimpleTrip( Catalogue * c, ifstream & tripStream, std::string * data, string & trip )
// Generic method that allows to import a single simpleTrip into a catalogue C
{
    c->tripList.AddTripSorted( new SimpleTrip( data[2].c_str(),
                                               data[3].c_str(), data[4].c_str() ) );
} //----- Fin de importSimpleTrip

//----------------------------------------------------- Méthodes protégées
void Catalogue::import ( )
// Algorithme :
// Appending XXXXXX
{
    ifstream tripStream( askNameFileImport() );
    if ( !tripStream )
    {
        return; // going back to menu
    }

    if ( tripStream.peek() == EOF )
    {
        cout << endl << "File is empty... Nothing to add to the Catalogue :(" << endl;
        return; // going back to menu
    }

    int choice;
    for ( ; ; )
    {
        cout << endl << "Enter a NUMBER corresponding to one of the options listed below" << endl;
        cout << "\t1: import all the trips from the file into the Catalogue" << endl;
        cout << "\t2: import only the trips of a certain type from the file into the Catalogue" << endl;
        cout << "\t3: import only the trips corresponding to specific city(ies) conditions" << endl;
        cout << "\t4: import only an interval of trips from the file into the Catalogue" << endl;
        cout << "\t5: go back to the main menu" << endl;

        cin >> choice;

        switch ( choice )
        {
            case 1:
                importAll( tripStream );
                break;
            case 2:
                importType( tripStream );
                break;
            case 3:
                //TODO : finish import cities
                importCities ( tripStream );
                break;
            case 4:
                //TODO : import interval
                importInterval ( tripStream );
                break;
            case 5:
                break;
            default:
                cout << endl << "Incorrect choice, please enter a number between 1 and 5!" << endl;
                //sleep(1);
                continue; // go back to options
        }
        break;
    }
    tripStream.close();
} //----- Fin de import

void Catalogue::importAll ( ifstream & tripStream )
// Algorithme :
//
{
    string trip;

    // While the stream does not return an error
    while ( tripStream.good() )
    {
        // Read a line from the stream
        getline( tripStream, trip );

        // If the line is empty, continue
        if ( trip.empty() ) continue;

        // Else we get the line, and split it with the ',' delimiter and store it in a string array
        string * data = split( trip, ',' );

        // Store the lastIndex of the trip (useful)
        int tripIndex = stoi( data[0] );

        // If the trip is a simple trip (data[1] corresponds to the type of the trip), we import it as a simple trip
        if ( data[1] == "Simple" && data[0] != "0" )
        {
            importSimpleTrip( this, tripStream, data, trip );
        }
        // Else if the trip is a composed trip, we import it as such
        else if ( data[1] == "Composed")
        {
            importComposedTrip( this, tripStream, data, trip, tripIndex );
        }

        delete [ ] data;
    }
    tripStream.clear();
    tripStream.seekg(0);
} //----- Fin de importAll

void Catalogue::importType ( ifstream & tripStream )
{
    const int CANCEL = 3;

    cout << "Please enter the type of trips you want to import from the file : " << endl;
    cout << "\t1: import all Simple trips" << endl;
    cout << "\t2: import all Composed trips" << endl;
    cout << "\t3: cancel" << endl;

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

        if((type != CANCEL && type != SIMPLE_TRIP && type != COMPOSED_TRIP))
        {
            cout << endl << "Incorrect choice, please enter a number between 1, 2 or 3..." << endl;
        }

    } while(!cin || (type != CANCEL && type != SIMPLE_TRIP && type != COMPOSED_TRIP));

    if ( type == SIMPLE_TRIP )
    {
        importAllSimpleTrips( tripStream );
    }
    else if ( type == COMPOSED_TRIP )
    {
        importAllComposedTrips( tripStream );
    }
    else if ( type == CANCEL )
    {
        cout << "Cancelling..." << endl;
        return;
    }
} //----- Fin de importType

void Catalogue::importAllSimpleTrips ( ifstream & tripStream )
{
    string trip;

    while ( tripStream.good() )
    {
        getline( tripStream, trip) ;

        if ( trip.empty() ) continue;

        string * data = split( trip, ',' );

        if ( data[1] == "Simple" && data[0] != "0" )
        {
            importSimpleTrip( this, tripStream, data, trip );
        }
        delete [ ] data;
    }
    tripStream.clear();
    tripStream.seekg(0);
} //----- Fin de importAllSimpleTrips

void Catalogue::importAllComposedTrips ( ifstream & tripStream )

{
    string trip;
    int tripIndex;

    while ( tripStream.good() )
    {
        getline( tripStream, trip );

        if ( trip.empty() ) continue;

        string * data = split( trip, ',' );

        tripIndex = stoi(data[0]);

        if ( data[1] == "Composed" )
        {
            importComposedTrip( this, tripStream, data, trip, tripIndex );
        }
        delete [ ] data;
    }
    tripStream.clear();
    tripStream.seekg(0);
} //----- Fin de importAllComposedTrips

void Catalogue::importTripsFromDeparture ( ifstream & tripStream )
{
    string trip;

    string departureCity;
    cout << "Enter the city of departure you are looking for : ";
    cin >> departureCity;

    int count = 0;
    int tripIndex;

    while(tripStream.good())
    {
        getline(tripStream,trip);

        if(trip.empty()) continue;

        string * data = split(trip,',');

        if( data[2] == departureCity && data[0] != "0")
        {
            count++;

            if(data[1] == "Simple")
            {
                importSimpleTrip(this, tripStream, data, trip);
            }
            else if (data[1] == "Composed")
            {
                tripIndex = stoi(data[0]);
                importComposedTrip(this, tripStream, data, trip, tripIndex);
            }
        }

        delete [ ] data;

    }

    if(count == 0){
        cout << "Sorry, no trips starting from " << departureCity << " are available..."<<endl;
    } else{
        cout << count << " trips starting from " << departureCity << " have been found !" << endl;
    }
}

void Catalogue::importTripsToArrival ( ifstream & tripStream )
{
    string trip;

    string arrivalCity;
    cout << "Enter the city of arrival you are looking for : ";
    cin >> arrivalCity;

    int count = 0;
    int tripIndex;

    while(tripStream.good())
    {
        getline(tripStream,trip);

        if(trip.empty()) continue;

        string * data = split(trip,',');

        if( data[3] == arrivalCity && data[0] != "0")
        {
            count++;

            if(data[1] == "Simple")
            {
                importSimpleTrip(this, tripStream, data, trip);
            }
            else if (data[1] == "Composed")
            {
                tripIndex = stoi(data[0]);
                importComposedTrip(this, tripStream, data, trip, tripIndex);
            }
        }

    }

    if(count == 0){
        cout << "Sorry, no trips going to " << arrivalCity << " are available..."<<endl;
    }else{
        cout << count << " cities going to " << arrivalCity << " have been found !" << endl;
    }
}

void Catalogue::importTripsFromTo( ifstream & tripStream )
{
    int count = 0;
    int tripIndex;

    string trip;
    string departureCity , arrivalCity;

    cout << "Enter the city of departure of the trip(s) you are looking for : ";
    cin >> departureCity;
    cout << "Enter the city of arrival of the trip(s) you are looking for : ";
    cin >> arrivalCity;

    while(tripStream.good())
    {
        getline(tripStream , trip);

        if(trip.empty()) continue;

        string *data = split(trip , ',');

        if(data[0] != "0" && data[2] == departureCity && data[3] == arrivalCity)
        {
            count++;
            tripIndex = stoi(data[0]);

            if(data[1] == "Simple")
            {
                importSimpleTrip(this , tripStream , data , trip);
            }
            else if(data[1] == "Composed")
            {
                importComposedTrip(this , tripStream , data , trip , tripIndex);
            }
        }
        delete[ ] data;
    }
}

void Catalogue::importCities ( ifstream & tripStream )
// Algorithme :
// XXXX
{
    int choice;

    string start , end;

    for ( ; ; )
    {
        cout << endl << "Enter a NUMBER corresponding to one of the options listed below" << endl;
        cout << "\t1: import trips leaving from a certain city" << endl;
        cout << "\t2: import trips arriving at a certain city" << endl;
        cout << "\t3: import trips both leaving and arriving to the cities you want" << endl;
        cout << "\t4: go back to import menu" << endl;

        cin >> choice;

        switch ( choice )
        {
            case 1:
                importTripsFromDeparture( tripStream );
                break;
            case 2:
                importTripsToArrival( tripStream );
                break;
            case 3:
                importTripsFromTo( tripStream );
                break;
            case 4:
                cout <<endl << "Going back to import menu..." << endl << endl;
                break;
            default:
                cout << endl << "Incorrect choice, please enter a number between 1 and 4!" << endl;
                //sleep(1);
                continue; // go back to options
        }
        break;
    }
} //----- Fin de importCities

void Catalogue::importInterval ( ifstream & tripStream ) ///A FINIR
// Algorithme :
// XXXX
{
    int start, end;

    //findLastIndex( tripStream );
    for ( ; ; )
    {
        cout << endl << "From which trip NUMBER do you wish to save into the file?" << endl;
        cin >> start;

        /*if ( start > //NB OF TRIPS IN FILE )
        {
            cout << endl << "Please enter a number inferior or equal to " << //NB OF TRIPS IN FILE << endl;
        }
        else break;*/
        break; /// a virer
    }

    for ( ; ; )
    {
        cout << "Until which trip NUMBER?" << endl;
        cin >> end;

        /*if ( end > //NB OF TRIPS IN FILE )
        {
            cout << endl << "Please enter a number inferior or equal to " << //NB OF TRIPS IN FILE << endl;
        }
        else break;*/
        break; /// a virer
    }

} //----- Fin de importInterval

ifstream Catalogue::askNameFileImport ( ) const
{
    string nameFile;

    bool fileOk = false; // to check if name of file respects the conditions and exists

    while ( !fileOk )
    {
        cout << endl << "Enter the name of the file containing the trips to import." << endl;
        cout << "Names such as '.' or '..' are NOT valid!" << endl;
        cout << "Please, do NOT add the extension of the file, nor add spaces or any special character!!" << endl;

        cin >> nameFile;

        if ( nameFile.empty() )
        {
            cerr << "File name is empty, please enter a valid name..." << endl;
            continue;
        }
        if ( nameFile.find('.') != string::npos )
        {
            cout << "This name of file is NOT valid..." << endl;
            continue;
        }

        nameFile.insert(0,"../C++/TP3/");
        nameFile.append(".txt");

        fileOk = true;
    }

    ifstream tripStream(nameFile.c_str());

    if ( !tripStream )
    {
        cerr << "Error opening the file, going back to the menu..." << endl;
    }
    else
    {
        cout << endl << "Importing trips from " << nameFile << endl;
    }

    return tripStream;
} //----- Fin de askNameFileImport