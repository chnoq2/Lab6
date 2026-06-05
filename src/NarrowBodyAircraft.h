#pragma once
#include "PassengerAircraft.h"

class NarrowBodyAircraft : public PassengerAircraft {
private:
    int AisleCount;
    bool HasBusinessClass;

public:
    NarrowBodyAircraft(const std::string& model, int maxSpeed, int range, int passengerCapacity, int cabinCrewCount, int aisleCount, bool hasBusinessClass)
    : PassengerAircraft(model, maxSpeed, range, passengerCapacity, cabinCrewCount), AisleCount(aisleCount), HasBusinessClass(hasBusinessClass) {}

    int GetAisleCount() const { return AisleCount; }
    bool GetHasBusinessClass() const { return HasBusinessClass; }
};