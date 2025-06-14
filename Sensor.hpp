#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <vector>
#include <memory>
#include <string>

class Sensor {
private:
    std::shared_ptr<std::vector<int>> readings;

public:
    Sensor(std::shared_ptr<std::vector<int>> sharedData);

    void addReading(int value);
    void printReadings(const std::string& label) const;
};

#endif // SENSOR_HPP