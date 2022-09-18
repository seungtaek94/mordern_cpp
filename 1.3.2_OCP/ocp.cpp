//
// Created by admin on 2022-09-14.
//
#include <iostream>
#include <vector>

template <typename T> struct Specification;
template <typename T> struct AndSpecification;

enum class Color {Red, Green, Blue};
enum class Size {Small, Medium, Large};

struct Product
{
    std::string name;
    Color color;
    Size size;
};


template <typename T> struct Specification
{
    virtual bool is_satisfied(T* item) = 0;

    AndSpecification<T> operator &&(Specification&& other)
    {
        return AndSpecification<T>(*this, other);
    }
};

// 복합 명세
template <typename T> struct AndSpecification : Specification<T>
{
    Specification<T> & first;
    Specification<T> & second;

    AndSpecification(Specification<T>& first, Specification<T>& second)
    :first(first), second(second)
    {
    }

    bool is_satisfied(T* item) override
    {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

template <typename T> struct Filter
{
    virtual std::vector<T*> filter(
            std::vector<T*> items,
            Specification<T>& spec) = 0;
};

struct BetterFilter:Filter<Product>
{
    std::vector<Product*> filter(
            std::vector<Product*> items,
            Specification<Product>& spec) override
    {
        std::vector<Product*> results;
        for(auto &p : items)
        {
            if(spec.is_satisfied(p))
                results.push_back(p);
        }
        return results;
    }
};


struct ColorSpecification:Specification<Product>
{
    Color color;

    explicit ColorSpecification(const Color color) : color{color}
    {

    }

    bool is_satisfied(Product* item) override{
        return item->color == color;
    }
};

struct SizeSpecification:Specification<Product>
{
    Size size;

    explicit SizeSpecification(const Size size) : size(size)
    {

    }

    bool is_satisfied(Product* item) override{
        return item->size == size;
    }
};

int main()
{
    Product apple {"Apple", Color::Green, Size::Small};
    Product tree {"Tree", Color::Green, Size::Large};
    Product house {"House", Color::Blue, Size::Large};

    std::vector<Product*> objects {&apple, &tree, &house};

    ColorSpecification green(Color::Green);
    SizeSpecification large(Size::Large);
    SizeSpecification small(Size::Small);

    // 단일 명세
    BetterFilter bf;
    auto green_obj = bf.filter(objects, green);

    for(auto & obj: green_obj)
    {
        std::cout << obj->name << " is green\n";
    }
    //

    // 복합 명세
    AndSpecification<Product> green_and_large{large, green};
    auto large_green_obj = bf.filter(objects, green_and_large);

    for(auto& obj: large_green_obj)
    {
        std::cout << obj->name << " is large and green\n";
    }

    // 복합 명세 && 연산자 오버로딩 사용
    auto green_and_small = ColorSpecification(Color::Green) && SizeSpecification(Size::Small);
    auto small_green_obj = bf.filter(objects, green_and_small);

    for(auto& obj: small_green_obj)
    {
        std::cout << obj->name << " is small and green\n";
    }

}