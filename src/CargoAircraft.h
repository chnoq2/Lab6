#pragma once
#include "Aircraft.h"
#include "QString"

class CargoAircraft : public Aircraft {
private:
    double MaxCargoWeight;
    double CargoVolumeCapacity;

public:
    CargoAircraft(const std::string& model, int maxSpeed, int range, double maxCargoWeight, double cargoVolumeCapacity)
    : Aircraft(model, maxSpeed, range), MaxCargoWeight(maxCargoWeight), CargoVolumeCapacity(cargoVolumeCapacity) {}

    double GetMaxCargoWeight() const { return MaxCargoWeight; }
    double GetCargoVolumeCapacity() const { return CargoVolumeCapacity; }
    QString toString() const override {
        return Aircraft::toString() + QString(", Тип: Грузовой, Вес: %1, Объем: %2").arg(GetMaxCargoWeight()).arg(GetCargoVolumeCapacity());
    }
};