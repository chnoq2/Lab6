#pragma once
#include "Aircraft.h"
#include "PassengerAircraft.h"
#include "CargoAircraft.h"
#include "WideBodyAircraft.h"
#include "NarrowBodyAircraft.h"

class IAircraftFactory {
public:
    virtual ~IAircraftFactory() {}
    virtual Aircraft* CreateAircraft() = 0; 
};

class NarrowBodyFactory : public IAircraftFactory {
private:
    std::string model; int maxSpeed; int range;
    int passengerCapacity; int cabinCrewCount;
    int aisleCount; bool hasBusinessClass;
public:
    NarrowBodyFactory(std::string m, int speed, int r, int cap, int crew, int aisles, bool biz)
    : model(m), maxSpeed(speed), range(r), passengerCapacity(cap), cabinCrewCount(crew), aisleCount(aisles), hasBusinessClass(biz) {}

    Aircraft* CreateAircraft() override {
        return new NarrowBodyAircraft(model, maxSpeed, range, passengerCapacity, cabinCrewCount, aisleCount, hasBusinessClass);
    }
};

class WideBodyFactory : public IAircraftFactory {
private:
    std::string model; int maxSpeed; int range;
    int passengerCapacity; int cabinCrewCount;
    int deckCount; int firstClassSeats;
public:
    WideBodyFactory(std::string m, int speed, int r, int cap, int crew, int decks, int firstClass)
    : model(m), maxSpeed(speed), range(r), passengerCapacity(cap), cabinCrewCount(crew), deckCount(decks), firstClassSeats(firstClass) {}

    Aircraft* CreateAircraft() override {
        return new WideBodyAircraft(model, maxSpeed, range, passengerCapacity, cabinCrewCount, deckCount, firstClassSeats);
    }
};

class CargoAircraftFactory : public IAircraftFactory {
private:
    std::string model; int maxSpeed; int range;
    double maxCargoWeight; double cargoVolumeCapacity;
public:
    CargoAircraftFactory(std::string m, int speed, int r, double weight, double vol)
    : model(m), maxSpeed(speed), range(r), maxCargoWeight(weight), cargoVolumeCapacity(vol) {}

    Aircraft* CreateAircraft() override {
        return new CargoAircraft(model, maxSpeed, range, maxCargoWeight, cargoVolumeCapacity);
    }
};