#pragma once
#include "Aircraft.h"

class PassengerAircraft : public Aircraft {
protected:
    int PassengerCapacity;
    int CabinCrewCount;

public:
    PassengerAircraft(const std::string& model, int maxSpeed, int range, int passengerCapacity, int cabinCrewCount)
    : Aircraft(model, maxSpeed, range), PassengerCapacity(passengerCapacity > 0 ? passengerCapacity : 0), CabinCrewCount(cabinCrewCount > 0 ? cabinCrewCount : 0) {}

    int GetPassengerCapacity() const { return PassengerCapacity; }
    int GetCabinCrewCount() const { return CabinCrewCount; }
};