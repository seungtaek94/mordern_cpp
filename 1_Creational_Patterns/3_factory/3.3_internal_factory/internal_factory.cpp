// 내부 팩터리는 새성할 타입의 내부 클래스로서 존재하는 간단한 팩터리를 말한다.
// c#, java등 friend 키워드에 해당하는 문법이 없는 프로그래밍 언어들에서 흔히 사용한다.

// 이 방법은 팩터리가 생성해야할 클래스가 한종류 일때 유용한다.

// 나중에 확장할 일이 없다는 전제하에 사용 가능
// 원본 객체 자체에 팩터리를 얻을 수 있게 하면 API의 사용성에 크게 도움이 된다.

#include <iostream>
#include <cmath>


struct Point
{
private:
    Point(const float x, const float y)
    :x{x}, y{y} {}

public:
    struct PointFactory
    {
    public:
        static Point NewCartesian(float x, float y)
        {
            return Point{x, y};
        }

        static Point NewPolar(float r, float theta)
        {
            return Point{r*std::cos(theta), r*std::sin(theta)};
        }
    };

public:
    float x;
    float y;

    //static PointFactory Factory;
    typedef PointFactory Factory;
};



int main()
{
    auto pp = Point::Factory::NewCartesian(3, 4);
}