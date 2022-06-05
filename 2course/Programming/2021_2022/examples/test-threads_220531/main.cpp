#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include <utility>

struct Range
{
    size_t first, second;
};

void f1(const Range& obj)
{
    std::cout << "Stay calm, " << obj.first + obj.second << std::endl;
}

void f2(int value1, int value2)
{
    int sum = value1 + value2;
    std::cout << "sum = " << sum << std::endl;
}

void product_part(const std::vector<std::vector<double>>& matr,
                  const std::vector<double>& vec,
                  Range range,
                  std::vector<double> *result)
{
    const size_t end_idx = range.first + range.second;
    for (size_t i = range.first; i < end_idx; i++) {
        (*result)[i] = 0.0;
        for (size_t j = 0; j < vec.size(); j++) {
            (*result)[i] += matr[i][j] * vec[j];
        }
    }
}

Range r_global = {0, 5};
std::mutex mt;
//std::atomic<Range> at_range;

void update_value(size_t first, size_t second)
{
	using namespace std::chrono;

	/*
	class MT
	{
	public:
		MT(std::mutex& mt) : mt_ref_{mt}
		{
			mt_ref_.lock();
		}

		~MT()
		{
			mt_ref_.unlock();
		}
	private:
		std::mutex& mt_ref_

	};
	{
        std::lock_guard lk{mt};
        auto r = at_range.load();
        std::cout << r.first << ", " << r.second << std::endl;
	}
	at_range = {first * 2, second * 2};
	*/

	{
	std::lock_guard lk{mt};
	std::cout << "r_global: {" << r_global.first << ", "
		  << r_global.second << "}" << std::endl;
	r_global.first = first;
	r_global.second = second;
	}
	std::this_thread::sleep_for(2500ms);
}

int main()
{
    /*
    // Part 1
    Range t{4, 8};
    std::thread thr1{f1, t}, thr2{f2, 4, 5};
    thr1.join();
    thr1.join();
    //thr1.detach();
    //thr2.detach();
    std::cout << "main thread completed" << std::endl;
    */

    // Part 2
    std::vector<std::vector<double>> matr = {
        {4.5, 6.7, 5.3, 7.8, -5.6, -45.9},
        {4.5, 6.7, 5.3, 7.8, -5.6, -45.9},
        {4.5, 6.7, 5.3, 7.8, -5.6, -45.9},
        {4.5, 6.7, 5.3, 7.8, -5.6, -45.9},
        {4.5, 6.7, 5.3, 7.8, -5.6, -45.9},
        {4.5, 6.7, 5.3, 7.8, -5.6, -45.9},
        {2.5, 4.7, 4.3, 4.8, -1.6, -3.4},
    };

    std::vector<double> vec = {4.5, 5.5, 0.6, 6.5, 7.8, -4.2};
    std::vector<double> res(matr.size());

    //std::thread t1{product_part, matr, vec, t, &res};
    //t1.join();
    std::vector<std::thread> threads;
    Range r1{0, 2}, r2{2, 2}, r3{4,3};
    threads.push_back(std::thread{product_part, matr, vec,
                         r1, &res});
    threads.push_back(std::thread{product_part, matr, vec,
                         r2, &res});
    threads.push_back(std::thread{product_part, matr, vec,
                         r3, &res});
    for (auto& thr : threads) {
        thr.join();
    }

    for (const auto elem : res) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    threads.clear();
    threads.emplace_back(update_value, 8, 9);
    threads.emplace_back(update_value, 44, 101);
    threads.emplace_back(update_value, 555, 111);

    for (auto& thr : threads) {
	    thr.join();
    }
    std::cout << "r_global final: {" << r_global.first
	      << ", " << r_global.second << "}" << std::endl;
    /*
    auto r = at_range.load();
    std::cout << "at_range final: {" << r.first << ", "
	      << r.second << "}" << std::endl;
    std::cout << "All done!" << std::endl;
    */
}
