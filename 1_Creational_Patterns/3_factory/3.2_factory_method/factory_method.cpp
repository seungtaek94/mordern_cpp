//
// Created by admin on 2022-09-27.
//

#include <iostream>
#include <cmath>

struct Point
{
    float x;
    float y;

protected:
    Point(const float x, const float y)
    :x{x}, y{y} {}

public:
    // 여기서 각각의  static 함수들을 팩터리 메서드라고 부른다.
    static Point NewCartesian(float x, float y)
    {
        return {x, y};
    }

    static Point NewPolar(float r, float theta)
    {
        return {r * std::cos(theta), r * std::sin(theta)};
    }
};


int main()
{
    auto p = Point::NewPolar(5, M_PI_4);
}