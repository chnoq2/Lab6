#pragma once
#include <string>
#include "QString"

class Aircraft {
protected:
    std::string Model;
    int MaxSpeed;
    int Range;

public:
    Aircraft(const std::string& model, int maxSpeed, int range)
    : Model(model),MaxSpeed(maxSpeed > 0 ? maxSpeed : 0), Range(range > 0 ? range : 0) {}

    std::string GetModel() const { return Model; }
    int GetMaxSpeed() const { return MaxSpeed; }
    int GetRange() const { return Range; }

    virtual ~Aircraft() {}
    virtual QString toString() const {
        return QString("Модель: %1, Скорость: %2, Дальность: %3").arg(QString::fromStdString(Model)).arg(MaxSpeed).arg(Range);
    }
};