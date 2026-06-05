#pragma once
#include <iostream>
#include "Aircraft.h"
#include "CargoAircraft.h"
#include "NarrowBodyAircraft.h"
#include "WideBodyAircraft.h"
#include "Airline.h"

class AircraftPrinter {
public:
    void Print(const Aircraft* aircraft) const {
        if (!aircraft) {
            std::cout << "Ошибка: указатель на самолет пуст!" << std::endl;
            return;
        }

        std::cout << "  ----------------------------------------" << std::endl;
        std::cout << "  Модель: " << aircraft->GetModel() << std::endl;
        std::cout << "  Макс. скорость: " << aircraft->GetMaxSpeed() << " км/ч" << std::endl;
        std::cout << "  Дальность полета: " << aircraft->GetRange() << " км" << std::endl;

        if (auto cargo = dynamic_cast<const CargoAircraft*>(aircraft)) {
            std::cout << "  Тип: Грузовой" << std::endl;
            std::cout << "  Макс. вес груза: " << cargo->GetMaxCargoWeight() << " кг" << std::endl;
            std::cout << "  Объем грузового отсека: " << cargo->GetCargoVolumeCapacity() << " м³" << std::endl;
        }
        else if (auto narrow = dynamic_cast<const NarrowBodyAircraft*>(aircraft)) {
            std::cout << "  Тип: Пассажирский (Узкофюзеляжный)" << std::endl;
            std::cout << "  Вместимость: " << narrow->GetPassengerCapacity() << " чел." << std::endl;
            std::cout << "  Экипаж: " << narrow->GetCabinCrewCount() << " чел." << std::endl;
            std::cout << "  Количество проходов: " << narrow->GetAisleCount() << std::endl;
            std::cout << "  Бизнес-класс: " << (narrow->GetHasBusinessClass() ? "Есть" : "Нет") << std::endl;
        }
        else if (auto wide = dynamic_cast<const WideBodyAircraft*>(aircraft)) {
            std::cout << "  Тип: Пассажирский (Широкофюзеляжный)" << std::endl;
            std::cout << "  Вместимость: " << wide->GetPassengerCapacity() << " чел." << std::endl;
            std::cout << "  Экипаж: " << wide->GetCabinCrewCount() << " чел." << std::endl;
            std::cout << "  Количество палуб: " << wide->GetDeckCount() << std::endl;
            std::cout << "  Мест первого класса: " << wide->GetFirstClassSeats() << std::endl;
        }
        std::cout << "  ----------------------------------------" << std::endl;
    }

    void PrintAirline(const Airline& airline) const {
        std::cout << "=========================================" << std::endl;
        std::cout << "АВИАКОМПАНИЯ: " << airline.GetName() << " (" << airline.GetCountry() << ")" << std::endl;
        std::cout << "Год основания: " << airline.GetFoundedYear() << std::endl;
        std::cout << "Размер флота: " << airline.GetFleet().size() << " самол." << std::endl;
        std::cout << "=========================================" << std::endl;

        std::cout << "Список самолетов в составе флота:" << std::endl;
        
        const auto& fleet = airline.GetFleet();
        
        if (fleet.empty()) {
            std::cout << "  [Флот пуст]" << std::endl;
        } else {
            for (const auto* aircraft : fleet) {
                Print(aircraft);
            }
        }
        std::cout << "=========================================" << std::endl;
    }
};