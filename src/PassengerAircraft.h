#pragma once
#include "Aircraft.h"

class PassengerAircraft : public Aircraft {
protected:
    int PassengerCapacity;
    int CabinCrewCount;

public:
    PassengerAircraft(const std::string& model, int maxSpeed, int range,int passengerCapacity, int cabinCrewCount)
    : Aircraft(model, maxSpeed, range), PassengerCapacity(passengerCapacity), CabinCrewCount(cabinCrewCount) {}

    int GetPassengerCapacity() const { return PassengerCapacity; }
    int GetCabinCrewCount() const { return CabinCrewCount; }
};