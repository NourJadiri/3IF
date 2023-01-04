//
// Created by Nour on 04/01/2023.
//

#include "CatalogueFileManager.h"
#include "Catalogue.h"

using namespace std;

void Catalogue::saveAll ( ofstream & tripStream ) const

{
    if( tripList.GetFirst() == nullptr )
    {
        cout << "Catalogue is empty... Nothing to add to the file :(";
        return;
    }
    int index = 1;

    Node * iter = tripList.GetFirst();

    while( iter != nullptr )
        // Parses through tripList
    {
        // Saves all the trips to file

        tripStream << index << ",";

        iter->GetTrip()->SaveTripToFile(tripStream);

        index++;

        iter = iter->GetNext();
    }


}
