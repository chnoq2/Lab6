#pragma once
#include "PassengerAircraft.h"

class WideBodyAircraft : public PassengerAircraft {
private:
    int DeckCount;
    int FirstClassSeats;

public:
    WideBodyAircraft(const std::string& model, int maxSpeed, int range, int passengerCapacity, int cabinCrewCount, int deckCount, int firstClassSeats)
    : PassengerAircraft(model, maxSpeed, range, passengerCapacity, cabinCrewCount), DeckCount(deckCount), FirstClassSeats(firstClassSeats) {}
    int GetDeckCount() const { return DeckCount; }
    int GetFirstClassSeats() const { return FirstClassSeats; }
};