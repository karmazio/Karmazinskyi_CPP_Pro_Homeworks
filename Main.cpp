#include "FileManager.hpp"
#include "Sensor.hpp"
#include <iostream>
#include <memory>
#include <vector>


// HOMEWORK 3
void testFileManager() {
    try {
        FileManager fm("output.txt");
        fm.write("New line\n");
        std::cout << "FileManager test passed.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "FileManager error: " << e.what() << "\n";
    }
}

void testSensorSharedReadings() {
    auto sharedData = std::make_shared<std::vector<int>>();

    Sensor sensor1(sharedData);
    Sensor sensor2(sharedData);

    sensor1.addReading(1);
    sensor2.addReading(2);
    sensor1.addReading(3);
    sensor2.addReading(123);

    sensor1.printReadings("Sensor1");
    sensor2.printReadings("Sensor2");
}

// END OF HOMEWORK 3

int main() {

    // HW 3
    testFileManager();
    testSensorSharedReadings();

    return 0;
}
