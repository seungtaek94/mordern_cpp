# 3장 팩토리(Factory)

## 3.1 시나리오

- 좌표계에 정보를 저장하려고한다.

```c++
struct Point
{
  Point(const float x, const float y)
  : x(x), y,(y){}
  
  float x, y;
};
```
위와 같이 구현을 할 수 있다. 이후 극좌표계 좌푯값을 정장해야하면 아래와 같이 
극좌표계용 생성자를 추가만 한다면 생각할 수 있다.

그러나 직교 좌표계, 극좌표계 모두 두개의 float 값을 파라미터로 하기때문에
생성자간에 구분이 불가능하다.

```c++
Point(const float r, const float theta)
{
    x = r * cos(theta);
    y = r * sin(theta);
}
```

한 가지 단순한 해결 방법은 아래와 같이 `enum` 타입 값을 파라미터에 추가하는 것이다. 

변수 이름이 x, y 및 r, theta 에서 중립적인 a, b로 바뀌었다.
이방법은 생성자의 사용법을 직관적으로 표현하는데 있어서 분명 손해이다.
기능적으로는 문제가 없지만 좋은 것과는 거리가 멀다.

이번장에서는 이러한 문제를 어떻게 다룰 수 있을지 알아 본다.

```c++
enum class PointType
{
    cartesian,
    polar    
};

Point(const float a, const float b, PointType type = PointType::cartesian)
{
    if(type == PointType::cartesian)
    {
        x = a;
        x = b;
    }
    else
    {
        x = a * cos(b);
        y = a * sin(b);
    }
}
```

