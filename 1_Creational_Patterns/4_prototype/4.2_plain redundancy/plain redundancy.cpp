#include <iostream>



struct Address
{
    std::string street, city;
    int suit;
};

struct Contact
{
    std::string name;
    Address address;
};

int main()
{
    // 프로토타입 객체
    Contact worker{"", Address{"123 East Dr", "London", 0}};

    // 프로토 타입을 복제하여 일부 수정
    Contact john = worker;
    john.name = "Jhon Doe";
    john.address.suit = 10;

}