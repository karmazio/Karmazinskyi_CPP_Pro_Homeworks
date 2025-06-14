#define _CRT_SECURE_NO_WARNINGS
#include "ThreadPool.hpp"


ThreadPool::ThreadPool(size_t numThreads) {
	threads.reserve(numThreads);
}




void ThreadPool::waitAll() {
	for (auto& t : threads) {
		if (t.joinable()) {
			t.join();
		}
	}
	threads.clear();
}


// T1
unsigned long long ThreadPool::factorial(int n) {
	unsigned long long result = 1;
	for (int i = 2; i <= n; ++i) {
		result *= i;
	}
	std::cout << "1) Factorial of " << n << " = " << result << std::endl;
	return result;
}

// T2
unsigned long long ThreadPool::sumOfSquares(int limit) {
	unsigned long long sum = 0;
	for (int i = 1; i <= limit; ++i)
		sum += static_cast<unsigned long long>(i) * i;
	std::cout << "2) Sum of squares from 1 to " << limit << " = " << sum << "\n";
	return sum;
}

// T3
std::vector<unsigned long long> ThreadPool::fibonacci(int n) {
	std::vector<unsigned long long> result(n);
	if (n <= 1) {
		std::cout << "3) Too few elements in fibonacci sequence!\n";
		return result;
	}
	result[0] = 0;
	result[1] = 1;
	for (int i = 2; i < n; ++i) {
		result[i] = result[i - 1] + result[i - 2];
	}
	std::cout << "3) Fibonacci sequence with " << n << " elements :\n";
	for (auto val : result) {
		std::cout << val << " ";
	}
	std::cout << "\n";
	return result;
}

// T4
std::vector<int> ThreadPool::findPrimes(int limit) {
	std::vector<int> primes;
	for (int num = 2; num <= limit; ++num) {
		bool isPrime = true;
		for (int div = 2; div <= std::sqrt(num); ++div) {
			if (num % div == 0) {
				isPrime = false;
				break;
			}
		}
		if (isPrime)
			primes.push_back(num);
	}

	std::cout << "4) Prime numbers up to " << limit << ": \n";
	for (int p : primes)
		std::cout << p << " ";
	std::cout << "\n";

	return primes;
}
