#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <mutex>
#include <atomic>

class SafeBankAccount {
private:
    double balance = 1000.0;
    mutable std::mutex balance_mutex;

public:
    void deposit(double amount) {
        std::lock_guard<std::mutex> lock(balance_mutex);
        balance += amount;
    }

    bool withdraw(double amount) {
        std::lock_guard<std::mutex> lock(balance_mutex);
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }

    double get_balance() const {
        std::lock_guard<std::mutex> lock(balance_mutex);
        return balance;
    }
};

class SafeBankStatistics {
private:
    std::atomic<int> transaction_count{ 0 };
    std::atomic<double> total_amount{ 0.0 };

public:
    void record_transaction(double amount) {
        transaction_count++;

        double current = total_amount.load();
        double desired;
        do {
            desired = current + amount;
        } while (!total_amount.compare_exchange_weak(current, desired));
    }

    int get_total_transactions() const {
        return transaction_count.load();
    }

    double get_total_amount() const {
        return total_amount.load();
    }
};

void safe_cashier_work(SafeBankAccount& account, SafeBankStatistics& stats, int id) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> op_dist(0, 1);
    std::uniform_int_distribution<> dep_dist(50, 500);
    std::uniform_int_distribution<> with_dist(10, 200);

    for (int i = 0; i < 100; ++i) {
        bool is_deposit = op_dist(gen);
        double amount = is_deposit ? dep_dist(gen) : with_dist(gen);

        if (is_deposit) {
            account.deposit(amount);
            stats.record_transaction(amount);
        }
        else if (account.withdraw(amount)) {
            stats.record_transaction(amount);
        }
    }
}