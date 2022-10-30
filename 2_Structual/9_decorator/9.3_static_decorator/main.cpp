#include <iostream>
#include<sstream>
#include <vector>
#include <cstdio>

// 동적 컴포지션
// - 참조를 주고 받으면서 런타임에 동적으로 무언가를 합성 가능
// - 최대한의 유연성 제공
// - ex) 사용자 이볅에 따라 런타임에 바응하여 컴포지션을 만들 수 있음


// 정적 컴포지션
// - 템플릿을 이용해 컴파일 시점에 추가 기능을 합성
// - 코드 작성 시점에 객체에 대한 정확한 추가기능 조합이 결정되어야함.
// - 즉 나중에 수정 불가능
struct Shape
{
    virtual std::string str() const = 0;
};


struct Circle : Shape
{
    float radius;

    explicit Circle(const float radius)
            :radius{radius}{}

    void resize(float factor) { radius *= factor; }

    std::string str() const override
    {
        std::ostringstream oss;
        oss << " A circle of radius " << radius;
        return oss.str();
    }

};


struct Square : Shape
{
    float side;

    Square(){}

    explicit Square(const float side)
            : side{side}
    {
    }

    std::string str() const override
    {
        std::ostringstream oss;
        oss << "A square with side " << side;
        return oss.str();
    }
};

/*
struct  ColoredShape : Shape
{
    Shape& shape;
    std::string color;

    ColoredShape(Shape& shape, const std::string& color)
            :shape{shape}, color{color} {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << shape.str() << " has the color " << color;
        return  oss.str();
    }
};
*/


struct TransparentShape : Shape
{
    Shape& shape;
    uint8_t transparency;

    TransparentShape(Shape& shape, const uint8_t transparency)
            :shape{shape}, transparency{transparency} {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << shape.str() << " has "
            << static_cast<float>(transparency) / 255.f * 100.f
            << "% transparency";
        return oss.str();
    }
};

// 노트: typename이 아니라 class 이다
template <typename T> struct ColoredShape2 : T
{
    static_assert(std::is_base_of<Shape, T>::value,
                  "Template argument must be a Shape");

    std::string color;

    // need this (or not!)
    ColoredShape2(){}

    template <typename...Args>
    ColoredShape2(const std::string& color, Args ...args)
            : T(std::forward<Args>(args)...), color{color}
    // 여기서 베이스 클래스의 소멸자를 호출할 수는 없다.
    // 왜냐면 소멸자를 알 수가 없기 때문이다.
    {
    }

    std::string str() const override
    {
        std::ostringstream oss;
        oss << T::str() << " has the color " << color;
        return oss.str();
    }
};

template <typename T> struct TransparentShape2 : T
{
    uint8_t transparency;

    template<typename...Args>
    TransparentShape2(const uint8_t transparency, Args ...args)
            : T(std::forward<Args>(args)...), transparency{ transparency }
    {
    }
s
    std::string str() const override
    {
        std::ostringstream oss;
        oss << T::str() << " has "
            << static_cast<float>(transparency) / 255.f * 100.f
            << "% transparency";
        return oss.str();
    }
};


int main()
{
    ColoredShape2<TransparentShape2<Circle>> circle{"red", 2 , 1};


    std::cout << circle.str() << std::endl;
    circle.resize(2);
    std::cout << circle.str() << std::endl;

}

