#include "OrderProcessor.hpp"

std::vector<Order> OrderProcessor::validateOrders(const std::vector<Order>& rawOrders)
{
    std::cout << "[1] Validating orders...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    auto orders = rawOrders;
    int validOrders = 0;
    for (auto& o : orders) {
        bool validated = true;
        if (o.getItems().empty()) {
            validated = false;
        }

        if (validated) {
            o.setStatus("Valid");
            validOrders++;
        }
    }

    std::cout << "Validation complete: " << validOrders << " valid orders.\n";
    return orders;
}

std::vector<Order> OrderProcessor::calculatePricing(const std::vector<Order>& validOrders)
{
    std::cout << "[2] Calculating prices...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    auto orders = validOrders;
    int pricedOrders = 0;
    for (auto& o : orders) {
        if (o.getStatus() == "Valid") {
            bool priced = false;
            for (auto& s : o.getItems()) {
                for (auto const& p : prices) {
                    if (s == p.first) {
                        o.setTotalPrice(o.getTotalPrice() + p.second);
                        priced = true;
                    }
                }
            }
            if (priced) {
                o.setStatus("Priced");
                pricedOrders++;
            }
            else {
                o.setStatus("Not Available");
            }
        }
        
    }
    std::cout << "Pricing complete: " << pricedOrders << " priced orders.\n";
    return orders;
}

std::vector<Order> OrderProcessor::checkInventory(const std::vector<Order>& pricedOrders)
{
    std::cout << "[3] Checking inventory...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    auto orders = pricedOrders;
    int availableOrders = 0;
    for (auto& o : orders) {
        if (o.getStatus() == "Priced") {
            bool inStock = true;
            for (auto& s : o.getItems()) {
                bool itemAvailable = false;
                for (auto& i : itemsInStock) {
                    if (s == i) {
                        itemAvailable = true;
                    }
                }
                if (!itemAvailable) {
                    inStock = false;
                }
            }
            if (inStock) {
                o.setStatus("Ready");
                availableOrders++;
            }
            else {
                o.setStatus("Not in Stock");
            }
        }
       
    }
    std::cout << "Inventory check complete: " << availableOrders << " available orders.\n";
    return orders;
}

void OrderProcessor::generateInvoices(const std::vector<Order>& finalOrders)
{
    std::cout << "[4] Generating Invoices...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    for (auto& o : finalOrders) {
        if (o.getStatus() == "Ready") {
            std::cout << "INVOICE #" << o.getId() << "\n";
            int item = 1;
            for (auto& s : o.getItems()) {
                std::cout << "Item #" << item << " " << s << ": " << prices.at(s) << "$\n";
                item++;
            }
            std::cout << "++TOTAL PRICE : " << o.getTotalPrice() << "$ ++\n"; 
        }
    }
}
