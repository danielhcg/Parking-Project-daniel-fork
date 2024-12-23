#ifndef PARKINGLOTFACTORY
#define PARKINGLOTFACTORY

#include <iostream>
#include "ParkingLot.hpp"
// single static method in single class turns into simple Factory pattern to create objects (Parking lots)
class ParkingLotFactory { 
public:

     static ParkingLot createParkingLot(const string& name, int numSpaces)  
        {
        ParkingLot lot(name); //creates new parking lot object with name
        for (int i = 1; i <= numSpaces; i++) { // creates and adds spaces, based on numSpaces input, and sets parking spaces to empty.
            ParkingSpace space(i, true); 
            lot.addSpace(space);
        }
        return lot;
    }
};

#endif
