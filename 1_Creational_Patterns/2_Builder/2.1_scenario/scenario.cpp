//
// Created by admin on 2022-09-20.
//
#include <iostream>
#include <sstream>
#include <vector>
#include <string>


// 방법 2.
struct HtmlElement
{
    std::string name;
    std::string text;

    std::vector<HtmlElement> elements;

    HtmlElement() {};
    HtmlElement(const std::string& name, const std::string& text)
        :name(name), text(text){}

    std::string str(int indent = 0) const
    {
        std::string strIndent;

        for(int i=0; i< indent; i++)
        {
            strIndent += "    ";
        }

        std::ostringstream  oss;
        oss << strIndent << "<" << name << ">\n";

        for(auto e : elements)
        {
            oss <<"    "<<strIndent<< "<"<< e.name << "> ";
            oss << e.text;
            oss << " </" << e.name << ">\n";
        }
        oss << strIndent << "</" << name << ">\n";

        return oss.str();
    }
};


int main()
{
    std::string words[] = {"hello", "world"};
    std::ostringstream  oss;

    // 벙법 1. Not Good
    oss << "<ul>";
    for(auto w : words)
    {
        oss << " <li>" << w << "</li>";
    }
    oss << "</ul>";
    printf(oss.str().c_str());
    std::cout << "@@\n";


    // 방법 2. OOP 스타일
    HtmlElement list{"ul", ""};
    for(auto w : words)
    {
        list.elements.emplace_back(HtmlElement{"li", w});
    }
    printf(list.str().c_str());

    return 0;
}