#include "ParkingLot.hpp"  
#include <iostream>
using namespace std;

// Decorator will decorate Parking lot "component" creating  different  parkinglots "Student" and "Faculty"

class ParkingLotDecorator: public ParkingLot  // decorator wraps around ParkingLot
{

  public:
    ParkingLot* baseParkingLot; 

    ParkingLotDecorator(ParkingLot* blankLot) : ParkingLot("Decorator Lot"), baseParkingLot(blankLot) {}// pointer intializes decorator with the Object from the Parkinglot

    /*virtual*/
    void display() override // decorator overrids display function 
    {
        baseParkingLot->display(); //Delegation of the display function to base ParkingLot
    }

    bool reserveSpace(const string& id, int spaceNumber, int startTime, int endTime)   // reserves space, with the space number to the base Parkinglot Object
    {
        return baseParkingLot-> reserveSpace(id,spaceNumber, startTime, endTime);
    }

    bool clearSpace(int spaceNumber) //clears  a parking space by delegating to base Parkinglot object
    {
        return baseParkingLot-> clearSpace(spaceNumber);
    }

    int countEmptySpaces() // counts the number of emptybase with delegation
    {
        return baseParkingLot->countEmptySpaces();
    }
};

// Below FacultyLotDecorator serves as ConcreteDecorator1
 
class FacultyLotDecorator: public ParkingLotDecorator, public Observer // decorator and observer for the Faculty lot, will add faculty functionality, as well as observers to the lot
{
  public:
    FacultyLotDecorator(ParkingLot* blankLot): ParkingLotDecorator(blankLot)
    {
        baseParkingLot->registerObserver(this); 
    } // constructor which will intialize falcultylotDecorator with parklot pointer as well as register observer with parkinglot
 
    /*virtual*/
   void display() override//tailors display message for faculty user
    {
        baseParkingLot->display(); 
        cout << "Authorized lot for Faculty" << endl;
    }

    void update(const string& message) override
    {
        cout << "Faculty Notification: " << message << endl;
    }

    bool reserveFacultySpot(const string& factID, int spaceNumber, int startTime, int endTime) // reserves parking spot for faculty with their ID in parameter and displays its faculty lot
    {
        vector<ParkingSpace>& spaces = baseParkingLot->getSpaces();
            for(int i = 0; i <spaces.size(); i++)
                {
                    if (spaces[i].getSpaceNumber() == spaceNumber)
                        {
                            if(spaces[i].getIsSpaceEmpty() == false)
                            {
                              cout << "Space " << spaceNumber << " is already occupied. "
                               << "Will be free to reserve after " << spaces[i].getReservationEndTime() << ":00." << endl;
                               return false;           
                            }
                        }
                }
            if(baseParkingLot-> reserveSpace(factID, spaceNumber, startTime, endTime))
            {
            // observers display this now cout << "Faculty space reserved for Faculty ID: " << factID << endl;
            return true;
            }
            else
            {
                return false;
            }
  }
};


// Below StudentLotDecorator serves as ConcreteDecorator1

class StudentLotDecorator: public ParkingLotDecorator, public Observer // decorator for the Student  lot, will add student  functionality
{
  public:
    StudentLotDecorator(ParkingLot* blankLot): ParkingLotDecorator(blankLot)
    {
        baseParkingLot->registerObserver(this);
    } // constructor which will intialize studentlotDecorator with parklot pointer
 
    /*virtual*/
    void display() override //tailors display message for student user
        { 
           baseParkingLot->display(); 
           cout << "Authorized lot for Students" << endl;
        }


    
    void update(const string& message) override
    {
        cout << "Student Notification: " << message << endl;
    }

    bool reserveStudentSpot(const string& studentID, int spaceNumber, int startTime, int endTime) // reserves parking spot for student  with their ID in parameter and displays its student lot
        {
            vector<ParkingSpace>& spaces = baseParkingLot->getSpaces();
            for(int i = 0; i <spaces.size(); i++)
                {
                    if (spaces[i].getSpaceNumber() == spaceNumber)
                        {
                            if(spaces[i].getIsSpaceEmpty() == false)
                            {
                              cout << "Space " << spaceNumber << " is already occupied. "
                               << "Will be free to reserve after " << spaces[i].getReservationEndTime() << ":00." << endl;
                               return false;           
                            }
                        }
                }
            if(baseParkingLot-> reserveSpace(studentID, spaceNumber, startTime, endTime))
            {
            // observers display this cout << "Student space reserved for Student ID: " << studentID << endl;
            return true;
            }
            else
            {
                return false;
            }
        }

};    
