#include <iostream>
#include <vector>



int main()
{
    std::vector<std::string> names{"jhon", "jane", "jill", "jack"};

    std::vector<std::string>::iterator it = names.begin();;

    std::cout << "first name is " << *it << std::endl;
    it++;
    std::cout << "second name is " << *it << std::endl;

    it->append(" goodall");
    std::cout << "full name is " << *it << std::endl;

    while(++it != names.end())
    {
        std::cout << "another name: " << *it << std::endl;
    }

    // rbegin 마지막 항목
    // rend 첫 항목의 바로 앞
    for(auto ri = std::rbegin(names); ri != rend(names); ++ri)
    {
        std::cout << *ri;
        if(ri + 1 != rend(names))
            std::cout <<", ";
    }
    std::cout<<std::endl;

    for(auto& name : names)
    {
        std::cout << "name = " << name << std::endl;
    }
}