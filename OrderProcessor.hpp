#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <map>
#include <future>

class Order {
private:
    int id;
    std::vector<std::string> items;
    double totalPrice;
    std::string status;

public:
    Order(int id, std::vector<std::string> items)
        : id(id), items(items), totalPrice(0.0), status("New") {
    }

    int getId() const { return id; }
    std::vector<std::string> getItems() const { return items; }
    double getTotalPrice() const { return totalPrice; }
    std::string getStatus() const { return status; }
    void setTotalPrice(double price) { totalPrice = price; }
    void setStatus(const std::string& s) { status = s; }

    void print() const {
        std::cout << "Order #" << id << " | Status: " << status
            << " | Price: $" << totalPrice << "\n";
    }
};

class OrderProcessor {
private:
    std::map<std::string, double> prices;
    std::vector<std::string> itemsInStock;
public:
    OrderProcessor() {
        prices.insert(std::pair< std::string, double>("TV", 100));
        prices.insert(std::pair< std::string, double>("Phone", 50));
        prices.insert(std::pair< std::string, double>("PC", 150));

        itemsInStock.push_back("TV");
        itemsInStock.push_back("PC");
    }

    std::vector<Order> validateOrders(const std::vector<Order>& rawOrders);
    std::vector<Order> calculatePricing(const std::vector<Order>& validOrders);
    std::vector<Order> checkInventory(const std::vector<Order>& pricedOrders);
    void generateInvoices(const std::vector<Order>& finalOrders);
};