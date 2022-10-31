#include <iostream>
#include <functional>

#include<sstream>
#include <vector>
#include <cstdio>

struct Logger
{
    std::function<void()> func;

    std::string name;

    Logger(const std::function<void()>& func, const std::string& name)
    : func{func}, name{name}
    {

    }

    void operator()() const
    {
        std::cout << "Entering " << name << std::endl;
        func();
        std::cout << "Exiting " << name << std::endl;
    }
};

template <typename Func>
struct Logger2
{
    Func func;
    std::string name;

    Logger2(const Func& func, const std::string& name)
    :func{func}, name{name}
    {

    }

    void operator()() const
    {
        std::cout << "Entering " << name << std::endl;
        func();
        std::cout << "Exiting " << name << std::endl;
    }
};

template<typename Func> auto make_logger2(Func func, const std::string& name)
{
    return Logger2<Func>{func, name};
}


double add(double a, double b)
{
    return a + b;
}

template <typename> struct Logger3;

template <typename R, typename... Args>
struct Logger3<R(Args...)>
{
    Logger3(std::function<R(Args...)> func, const std::string& name)
            :func{func}, name{name}
    {

    }

    R operator()(Args ...args) const
    {
        std::cout << "Entering " << name << std::endl;
        R result = func(args...);
        std::cout << "Exiting " << name << std::endl;
        return result;
    }

    std::function<R(Args...)> func;
    std::string name;
};

template <typename R, typename... Args>
auto make_logger3(R(*func)(Args...), const std::string& name)
{
    return Logger3<R(Args...)>(
            std::function<R(Args...)>(func), name);
}


int main()
{
    Logger([](){std::cout << "hello" << std::endl;}, "HelloFunction")();

    auto call = make_logger2([](){std::cout << "hello2" << std::endl;}, "HelloFunction2");
    call();

    auto logged_add = make_logger3(add, "Add");
    auto result = logged_add(2, 3);
    std::cout << result << std::endl;
}

