// Pimpl은 Pointer to Implementation의 약자이다.
// 즉, 구현부를 포인터로 참조 하는 관례 이다.


/*
 - 다음과 같은 구현을 통해 클래스(Person)의 구현부의 상당 부분이 감춰질 수 있다.
 private/protected 한정자로 인해 실제로는 사용 불가능한 정보들의 노출을 숨길 수 있다.

 - 바이너리 호환성을 보증하기 쉬워진다. 숨겨진 구현 크래스에 대한  수정은 바이너리 호환성에 영향을 미치지 않는다.

 - 헤더 파일이 멤버 선언에 필요한 헤더들만 인클루드하게 할 수 있다.
 즉, 구현부 때문에 클라이언트에서 필요 없는 헤더까지 인클루드해야 하는 상황을 피할 수 있다.

 이러한 장점들은 깨끗하고 안정적인 헤더를 유지할 수 있게하고 컴파일 소요시간을 줄어들게 해준다.
 디자인 패턴의 관점에서는 Pimpl을 브릿지 패턴의 좋은 예로 볼 수 있다.
 구현이 숨겨진 포인터는 인터페이스아 숨겨야할 .cpp의 세부 구현을 연결하는 다리(브릿지) 역할 을 한다.
 */


#include <iostream>
#include <memory>
#include <vector>


// 클래스의 구현부를 다른 클래스(PersonImpl)에 숨기고자 하는 의도
struct Person
{
    std::string name;
    void greet();

    Person();
    ~Person();


    class PersonImpl;
    PersonImpl *impl;
};