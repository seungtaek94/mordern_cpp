#include <iostream>
#include <cmath>
#include <memory>

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

struct Coffe : HotDrink
{
    void prepare(int volume) override
    {
        std::cout << "Take Coffe, boil water pour "<< volume << "ml, add some lemon" << std::endl;
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
        drink = std::make_unique<Coffe>();
        drink->prepare(50);
    }
    return drink;
}

int main()
{

}