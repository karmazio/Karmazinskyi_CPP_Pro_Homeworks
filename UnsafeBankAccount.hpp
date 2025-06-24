#include <iostream>
#include <thread>
#include <vector>
#include <random>

class UnsafeBankAccount {
private:
    double balance = 1000.0;  

public:
    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }

    double get_balance() const {
        return balance;
    }
};

class UnsafeBankStatistics {
private:
    int transaction_count = 0;
    double total_amount = 0.0;

public:
    void record_transaction(double amount) {
        transaction_count++;
        total_amount += amount;
    }

    int get_total_transactions() const { return transaction_count; }
    double get_total_amount() const { return total_amount; }
};

void cashier_work(UnsafeBankAccount& account, UnsafeBankStatistics& stats, int id) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> operation_distribution(0, 1);
    std::uniform_int_distribution<> deposit_distribution(50, 500);
    std::uniform_int_distribution<> withdraw_distribution(10, 200);

    for (int i = 0; i < 100; ++i) {
        bool is_deposit = operation_distribution(gen);
        double amount = is_deposit ? deposit_distribution(gen) : withdraw_distribution(gen);

        if (is_deposit) {
            account.deposit(amount);
            stats.record_transaction(amount);
        }
        else if (account.withdraw(amount)) {
            stats.record_transaction(amount);
        }
    }
}