#include <iostream>
#include <thread>
#include <vector>
#include <functional>
#include <cmath>

class ThreadPool {
private:
	std::vector<std::thread> threads;
public:
	// Створюємо пул потоків
	explicit ThreadPool(size_t numThreads);

	// Додаємо завдання до пулу
	template<typename Function, typename... Args>
	void addTask(Function&& func, Args&&... args);

	// Чекаємо завершення всіх завдань
	void waitAll();

	// T1
	static unsigned long long factorial(int n);

	// T2
	static unsigned long long sumOfSquares(int limit);

	// T3
	static std::vector<unsigned long long> fibonacci(int n);

	// T4
	static std::vector<int> findPrimes(int limit);
};template<typename Function, typename... Args>
void ThreadPool::addTask(Function&& func, Args&&... args) {
	threads.emplace_back(std::forward<Function>(func),
		std::forward<Args>(args)...);
}