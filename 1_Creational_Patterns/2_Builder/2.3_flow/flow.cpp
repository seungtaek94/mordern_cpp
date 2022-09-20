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

struct HtmlBuilder
{
    HtmlElement root;
    HtmlBuilder(std::string root_name) {root.name = root_name;}

    HtmlBuilder& add_child(std::string child_name, std::string child_text)
    {
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);

        return *this;
    }

    std::string str() { return  root.str(); }
};


int main()
{
    HtmlBuilder builder{"ul"};

    builder.add_child("li", "hello").add_child("li", "world");

    std::cout << builder.str() << std::endl;

    return 0;
}