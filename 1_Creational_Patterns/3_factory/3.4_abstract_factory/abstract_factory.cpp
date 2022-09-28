#include <iostream>
#include <cmath>
#include <memory>
#include <map>


struct HotDrink
{
    virtual void prepare(int volume) = 0;
};

struct Tea : HotDrink
{
    void prepare(int volume) override
    {
        std::cout << "Take tea bag, boil water pour "<< volume << "ml, add some lemon" << std::endl;
    }
};

struct Coffee : HotDrink
{
    void prepare(int volume) override
    {
        std::cout << "Take coffee, boil water pour "<< volume << "ml" << std::endl;
    }
};

std::unique_ptr<HotDrink> make_drink(std::string type)
{
    std::unique_ptr<HotDrink> drink;

    if(type == "tea")
    {
        drink = std::make_unique<Tea>();
        drink->prepare(200);
    }
    else
    {
        drink = std::make_unique<Coffee>();
        drink->prepare(50);
    }
    return drink;
}


struct HotDrinkFactory
{
    virtual std::unique_ptr<HotDrink> make() const = 0;
};

struct CoffeeFactory : HotDrinkFactory
{
    std::unique_ptr<HotDrink> make() const override
    {
        return std::make_unique<Coffee>();
    }
};

struct TeaFactory : HotDrinkFactory
{
    std::unique_ptr<HotDrink> make() const override
    {
        return std::make_unique<Tea>();
    }
};

class DrinkFactory
{
    std::map<std::string, std::unique_ptr<HotDrinkFactory>> hot_factories;

public:
    DrinkFactory()
    {
        hot_factories["coffee"] = std::make_unique<CoffeeFactory>();
        hot_factories["tea"] = std::make_unique<TeaFactory>();
    }

    std::unique_ptr<HotDrink> make_drink(const std::string& name)
    {
        auto drink = hot_factories[name]->make();
        drink->prepare(200);
        return drink;
    }

};


int main()
{
    auto d = make_drink("tea");

    DrinkFactory df;

    df.make_drink("coffee");

    return 0;
}