#pragma once
#include <string>
#include <vector>
#include "Aircraft.h"

class Airline {
private:
    std::string Name;
    std::string Country;
    int FoundedYear;
    std::vector<Aircraft*> _Fleet;

public:
    Airline(const std::string& name, const std::string& country, int foundedYear): Name(name), Country(country), FoundedYear(foundedYear) {}

    std::string GetName() const { return Name; }
    std::string GetCountry() const { return Country; }
    int GetFoundedYear() const { return FoundedYear; }
    const std::vector<Aircraft*>& GetFleet() const { return _Fleet; }

    void AddAircraft(Aircraft* aircraft) { _Fleet.push_back(aircraft); }

    // Airline.h
    void RemoveAircraft(int index) {
        if (index >= 0 && index < _Fleet.size()) {
            delete _Fleet[index];          // Освобождаем память
            _Fleet.erase(_Fleet.begin() + index); // Удаляем указатель из вектора
        }
    }
};