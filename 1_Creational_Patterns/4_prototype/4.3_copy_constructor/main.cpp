#include <iostream>


struct Address
{
    std::string street, city;
    int suit;

    Address(const std::string& street,  const std::string& city, int suit)
    :street{street}, city{city}, suit{suit}
    {

    }
};

struct Contact
{
    std::string name;
    Address* address;

    Contact(std::string name, Address* address)
    :name{name}, address(address)
    {
    }

    Contact(const Contact& other)
    :name{other.name},
    address{new Address(*other.address)}
    {
    }

    Contact& operator=(const Contact& other)
    {
        if(this == &other)
            return *this;

        name = other.name;
        address = other.address;
        return *this;
    }
};

int main()
{
    // 프로토타입 객체
    Contact worker{"", new Address{"123 East Dr", "London", 0}};

    // 프로토 타입을 복제하여 일부 수정
    Contact john{worker};

    john.name = "John";
    john.address->suit  = 10;

}