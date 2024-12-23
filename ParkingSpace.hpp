#ifndef PARKINGSPACE_H
#define PARKINGSPACE_H
#include <iostream>
#include "ParkingAbstract.hpp"
#include <vector>
using namespace std;

//ParkingSpace serves as the "leaf" for the composite pattern for ParkingAbstract and ParkingLot (shares display() uniformity)
class ParkingSpace : public Parking{
 int spaceNumber;
 static const int totalTimeSlots = 17; // numbrt of time slots from reservation 7am-12am
 bool timeSlots[totalTimeSlots]; //  creates bool array of total hours of time reservation
 bool isSpaceEmpty;
 int  reservationEndTime;
 string userID;
 

public:

    ParkingSpace( int number, bool spaceEmpty = true, const string& user = "")  
    {
       spaceNumber = number;
       isSpaceEmpty = spaceEmpty;
       for (int i = 0; i < totalTimeSlots; i++)
       {
        timeSlots[i] = true;
       } 
    
    }

    int getSpaceNumber() // returns spaceNumber
    {
       return spaceNumber;
    }   

    bool getIsSpaceEmpty()  // Returns status of space if empty
    {
        return isSpaceEmpty;
    }

    int getReservationEndTime()
    {
        return reservationEndTime;
    }
    
    void setSpaceNumber(int number) // sets space number
    {
       spaceNumber = number;
    }

    void setSpacetoEmpty() // sets space status to empty
    {
       isSpaceEmpty = true;
    }
 
    void setSpacetoFull() // sets space to full
    {
      isSpaceEmpty = false;
    }


 bool reserveTimeSlot(const string& id, int startTime, int endTime) {

    if (startTime < 0 || endTime >= totalTimeSlots) 
    {
        cout << "Time range invalid" << endl;
        return false;
    }

    // Validate availability of the time slots
    for (int i = startTime; i <= endTime; i++) {
        if (!timeSlots[i]) 
        {
        cout << "Time slot between " << startTime + 7 << ":00 and " << endTime + 7
             << ":00 is already reserved for space # " << spaceNumber << endl;
            return false;
        }
    }

    // Reserve the time slots
    for (int i = startTime; i <= endTime; i++) {
        timeSlots[i] = false; // Mark slot as reserved
       // debug log cout << "Slot " << i + 7 << ":00 reserved." << endl;
    }
    
    updateSpaceStatus();

    userID = id;
    reservationEndTime = endTime + 7;

    cout << "Parking Space " << spaceNumber << " reserved by id: " << userID <<" for " << startTime + 7 << ":00"
         << " through " << endTime + 7 << ":00." << endl;

    return true;
}

 void clearReservedTimeSlots()
    {
        for (int i = 0; i < totalTimeSlots; i++)
        {
            timeSlots[i] = true;
        }
    }

 void updateSpaceStatus() 
 {
    // Assume the space is fully reserved initially
    isSpaceEmpty = false;

    // Check if any time slot is still available
    for (int i = 0; i < totalTimeSlots; i++) {
        if (!timeSlots[i]) { 
            // Found an available slot, mark the space as not fully reserved
            isSpaceEmpty = false;
            return; // Exits early
        }
    }

    // If no available slots are found, the space remains fully reserved
}
    void display() override // displays Parking space number and it its status, also helps Composite uniformity with ParkingLot.hpp
    {
     cout << "Displaying Parking Space " << spaceNumber << endl;
        if (isSpaceEmpty)
            {
                cout << "This space is currently empty."  << endl;
            }
        else 
            {
            cout << "This space is currently occupied." << " Space will be free at " << reservationEndTime << ":00" << endl;
            }           

     }

    //string getName() const override 
    //{
   //     return "Parking Space #" + (spaceNumber);
   // }
     

};

#endif