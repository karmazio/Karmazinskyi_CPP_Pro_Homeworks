#include "FileManager.hpp"
#include "Sensor.hpp"
#include <iostream>
#include <memory>
#include <vector>

#include "ThreadPool.hpp"
#include "OrderProcessor.hpp"

#include "UnsafeBankAccount.hpp"
#include "SafeBankAccount.hpp"


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


// HOMEWORK 4
void testThreadPool() {
    ThreadPool pool(4);

    pool.addTask(ThreadPool::factorial, 15);
    pool.addTask(ThreadPool::sumOfSquares, 1000);
    pool.addTask(ThreadPool::fibonacci, 30);
    pool.addTask(ThreadPool::findPrimes, 100);

    std::cout << "All tasks were added, waiting for completion...\n";

    pool.waitAll();

    std::cout << "All tasks are completed!\n";

}

void testOrderProcessor() {
    OrderProcessor processor;
    std::vector<Order> rawOrders = {
        Order(1, {"TV", "PHONE", "PC"}),
        Order(2, {}),
        Order(3, {"TV", "PC"}),
        Order(4, {"TV", "TV"})
    };

    std::promise<std::vector<Order>> promise1;
    std::future<std::vector<Order>> future1 = promise1.get_future();

    std::promise<std::vector<Order>> promise2;
    std::future<std::vector<Order>> future2 = promise2.get_future();

    std::promise<std::vector<Order>> promise3;
    std::future<std::vector<Order>> future3 = promise3.get_future();

    // Thread 1 - Validation
    std::thread t1([&]() {
        auto validated = processor.validateOrders(rawOrders);
        promise1.set_value(std::move(validated));
        });

    // Thread 2 - Prices
    std::thread t2([&]() {
        auto validated = future1.get(); 
        auto priced = processor.calculatePricing(validated);
        promise2.set_value(std::move(priced));
        });

    // Thread 3 - Checking the stock
    std::thread t3([&]() {
        auto priced = future2.get();  
        auto stocked = processor.checkInventory(priced);
        promise3.set_value(std::move(stocked));
        });

    // Thread 3 - Invoices
    std::thread t4([&]() {
        auto finalOrders = future3.get();  
        processor.generateInvoices(finalOrders);
        });


    t1.join();
    t2.join();
    t3.join();
    t4.join();

}

// HOMEWORK 5
void testUnsafeBankAccount() {
    UnsafeBankAccount account;
    UnsafeBankStatistics stats;

    std::cout << "\n=== Unsafe Bank Simulation ===\n";
    std::cout << "Initial balance: " << account.get_balance() << "\n";

    std::vector<std::thread> cashiers;
    for (int i = 0; i < 5; ++i) {
        cashiers.emplace_back(cashier_work, std::ref(account), std::ref(stats), i);
    }

    for (auto& t : cashiers) t.join();

    std::cout << "Final balance: " << account.get_balance() << "\n";
    std::cout << "Total transactions: " << stats.get_total_transactions() << "\n";
    std::cout << "Total transaction amount: " << stats.get_total_amount() << "\n";
}

void testSafeBankAccount() {
    SafeBankAccount account;
    SafeBankStatistics stats;

    std::cout << "\n=== Safe Bank Simulation ===\n";
    std::cout << "Initial balance: " << account.get_balance() << "\n";

    std::vector<std::thread> cashiers;
    for (int i = 0; i < 5; ++i) {
        cashiers.emplace_back(safe_cashier_work, std::ref(account), std::ref(stats), i);
    }

    for (auto& t : cashiers) t.join();

    std::cout << "Final balance: " << account.get_balance() << "\n";
    std::cout << "Total transactions: " << stats.get_total_transactions() << "\n";
    std::cout << "Total transaction amount: " << stats.get_total_amount() << "\n";
    std::cout << "All cashiers completed work safely!\n";
}



int main() {

    // HW 3
    //testFileManager();
    //testSensorSharedReadings();

    // HW 4
    //testThreadPool();
    //testOrderProcessor();

    // HW 5
    testUnsafeBankAccount();
    testUnsafeBankAccount();
    testUnsafeBankAccount();
    testSafeBankAccount();
    testSafeBankAccount();
    testSafeBankAccount();

    return 0;
}
