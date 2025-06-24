#include "OrderProcessor.hpp"

std::vector<Order> OrderProcessor::validateOrders(const std::vector<Order>& rawOrders)
{
    std::cout << "[1] Validating orders...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    auto orders = rawOrders;
    int validOrders = 0;
    for (auto& order : orders) {
        bool validated = true;
        if (order.getItems().empty()) {
            validated = false;
        }

        if (validated) {
            order.setStatus("Valid");
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
    for (auto& order : orders) {
        if (order.getStatus() == "Valid") {
            bool priced = false;
            for (auto& item : order.getItems()) {
                for (auto const& priceTag : prices) {
                    if (item == priceTag.first) {
                        order.setTotalPrice(order.getTotalPrice() + priceTag.second);
                        priced = true;
                    }
                }
            }
            if (priced) {
                order.setStatus("Priced");
                pricedOrders++;
            }
            else {
                order.setStatus("Not Available");
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
    for (auto& order : orders) {
        if (order.getStatus() == "Priced") {
            bool inStock = true;
            for (auto& item : order.getItems()) {
                bool itemAvailable = false;
                for (auto& itemInStock : itemsInStock) {
                    if (item == itemInStock) {
                        itemAvailable = true;
                    }
                }
                if (!itemAvailable) {
                    inStock = false;
                }
            }
            if (inStock) {
                order.setStatus("Ready");
                availableOrders++;
            }
            else {
                order.setStatus("Not in Stock");
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

    for (auto& order : finalOrders) {
        if (order.getStatus() == "Ready") {
            std::cout << "INVOICE #" << order.getId() << "\n";
            int i = 1;
            for (auto& item : order.getItems()) {
                std::cout << "Item #" << item << " " << item << ": " << prices.at(item) << "$\n";
                i++;
            }
            std::cout << "++TOTAL PRICE : " << order.getTotalPrice() << "$ ++\n";
        }
    }
}
