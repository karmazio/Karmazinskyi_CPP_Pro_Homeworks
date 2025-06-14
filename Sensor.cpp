#include "Sensor.hpp"
#include <iostream>

Sensor::Sensor(std::shared_ptr<std::vector<int>> sharedData)
    : readings(std::move(sharedData)) {
}

void Sensor::addReading(int value) {
    readings->push_back(value);
}

void Sensor::printReadings(const std::string& label) const {
    std::cout << label << " Readings: ";
    for (int value : *readings) {
        std::cout << value << " ";
    }
    std::cout << "\n";
}