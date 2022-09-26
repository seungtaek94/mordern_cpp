// 빌더와 마찬가지로 Point를 생성하는 함수들을 별도의 클래스에 몰아 넣을 수 있다.
// 그러한 글래스를 팩터리라 부른다.

#include <iostream>
#include <cmath>

struct Point
{
    float x;
    float y;

    friend class PointFactory;

private:
    // private으로 선언하여 사용자가 생성자를 직접 사용할 수 없게
    // 선택적이지만 두가지 방법을 제공해 사용자를 혼란스럽게할 필요는 없음
    Point(const float x, const float y)
    :x{x}, y{y} {}
};

struct PointFactory
{
    static Point NewCartesian(float x, float y)
    {
        return Point{x, y};
    }

    static Point NewPolar(float r, float theta)
    {
        return Point{r*std::cos(theta), r*std::sin(theta)};
    }
};


int main()
{
    auto my_point = PointFactory::NewCartesian(3, 4);
}