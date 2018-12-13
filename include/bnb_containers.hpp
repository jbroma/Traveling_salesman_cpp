#pragma once
#include "city.hpp"

#include <iostream>
#include <queue>
#include <stack>

namespace alg {

// TODO refactor to use templates
using limits = std::numeric_limits<uint32_t>;
using plain_matrix = std::vector<std::vector<uint32_t>>;
using city_p_queue = std::priority_queue<City, std::vector<City>, City::compare>;

class Container {

public:
    Container() = default;

    virtual ~Container() = default;
    virtual City top() = 0;
    virtual void push(City city) = 0;
    virtual void pop() = 0;
    virtual bool empty() = 0;
};

class Priority_Queue : public Container {

public:
    Priority_Queue(city_p_queue queue)
        : city_q { queue } {};

    City top() override { return city_q.top(); };
    void push(City city) override { city_q.push(city); };
    void pop() override { city_q.pop(); };
    bool empty() override { return city_q.empty(); };
    ~Priority_Queue() override = default;

private:
    city_p_queue city_q;
};

class Stack : public Container {
public:
    Stack(std::stack<City> city_stack)
        : city_s { city_stack } {};

    City top() override { return city_s.top(); };
    void push(City city) override { city_s.push(city); };
    void pop() override { city_s.pop(); };
    bool empty() override { return city_s.empty(); };
    ~Stack() override = default;

private:
    std::stack<City> city_s;
};

} // namespace alg