#pragma once
 
#ifdef __linux__
#include <time.h>
#elif _WIN32
#include <Windows.h>
#endif
 
#include <iostream>
#include <functional>
#include <optional>
 
template<typename U, typename T, typename ... Args>
class Timer{
 
public:
    Timer() = delete;
   
    Timer(T(U::*fnc_to_measure)( Args ... args), U* context)
        : fnc_to_measure_{ fnc_to_measure }, context_{ context }
    {};
 
    ~Timer() = default;
    Timer& operator=(const Timer& rhs) = default;
 
    double run(Args ... args);
    double run_average(const int executions);
 
    T get_output();
 
private:
 
    U* context_;
    T (U::*fnc_to_measure_)(Args ... args);
    std::optional<T> alg_value;
 
    void start_counter();
    double get_time();
 
    // Attributes for OS specific timing functions.
    #ifdef __linux__
    clock_t start_time_;
 
    #elif _WIN32
    double pc_freq_ = 0.0;
    long long start_time_;
   
    #endif
};
 
template<typename U, typename T, typename ... Args>
double Timer<U, T, Args ... >::run(Args ... args)
{
    start_counter();
    alg_value = (context_->*fnc_to_measure_)(args ...);
    return get_time();
}
 
template<typename U, typename T, typename ... Args>
double Timer<U, T, Args ...>::run_average(const int executions)
{
    double accu_time{ 0 };
 
    for (int i{ 0 }; i < executions; ++i)
        accu_time += run();
 
    return accu_time / executions;
}
 
#ifdef __linux__
 
template<typename T, typename ... Args>
void Timer<T, Args ...>::start_counter()
{
    start_time_ = clock();
}
 
template<typename T, typename ... Args>
double Timer<T, Args ...>::get_time()
{
    return (clock() - start_time_) / static_cast<double>(CLOCKS_PER_SEC) ;  // Time in seconds.
}
 
#elif _WIN32
template<typename U, typename T, typename ... Args>
void Timer<U, T, Args ...>::start_counter()
{
    LARGE_INTEGER per_f;
    if (QueryPerformanceFrequency(&per_f))
 
        pc_freq_ = double(per_f.QuadPart) / 1000.0;
 
    QueryPerformanceCounter(&per_f);
    start_time_ = per_f.QuadPart;
}
 
template<typename U, typename T, typename ... Args>
double Timer<U, T, Args ...>::get_time()
{
    LARGE_INTEGER per_f;
    QueryPerformanceCounter(&per_f);
    return double(per_f.QuadPart - start_time_) / pc_freq_;
}
#endif
 
template<typename U, typename T, typename ... Args>
T Timer<U, T, Args ...>::get_output()
{
    if(alg_value.has_value())
        return alg_value.value();
    else
        throw std::invalid_argument("Timed function does not return a value.");
}