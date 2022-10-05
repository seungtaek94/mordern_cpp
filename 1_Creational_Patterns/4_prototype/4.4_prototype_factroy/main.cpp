#include <iostream>
#include <memory>

struct Address
{
    std::string street, city;
    int suite;

    Address(const std::string& street,  const std::string& city, int suite)
            :street{street}, city{city}, suite{suite}
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

struct EmployeeFactory
{
    static Contact main;
    static Contact aux;

    static std::unique_ptr<Contact> NewMainOfficeEmployee(std::string name, int suite)
    {
        return NewEmployee(name, suite, main);
    }

    static std::unique_ptr<Contact> NewAuxOfficeEmployee(std::string name, int suite)
    {
        return NewEmployee(name, suite, aux);
    }

private:
    static std::unique_ptr<Contact> NewEmployee(std::string name, int suite, Contact& proto)
    {
        auto result = std::make_unique<Contact>(proto);
        result->name = name;
        result->address->suite = suite;
        return result;
    }
};


Contact EmployeeFactory::main{ "", new Address{"123 East Dr", "London", 0} };
Contact EmployeeFactory::aux{ "", new Address{"123b East Dr", "London", 0} };

int main()
{
    // 프로토타입 객체
    //static Contact main{"", new Address{"123 East Dr", "London", 0}};
    //static Contact aux{"", new Address{"123 East Dr", "London", 0}};

    auto john = EmployeeFactory::NewMainOfficeEmployee("John Doe", 123);
    auto jane = EmployeeFactory::NewAuxOfficeEmployee("Jane Doe", 125);
}