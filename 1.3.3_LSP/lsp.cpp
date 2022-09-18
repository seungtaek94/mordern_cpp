//
// Created by admin on 2022-09-15.
//

#include <iostream>

class Rectangle
{
protected:
    int width, height;
public:
    Rectangle(const int width, const int height):width(width), height(height){}

    int get_width() const { return  width;}
    virtual void set_width(const int width) {this->width = width;}
    int get_height() const { return  height; }
    virtual void set_height(const int height) {this->height = height;}

    int area() { return  width * height;}
};


class Square: public Rectangle
{
public:
    Square(int size): Rectangle(size, size){}

    void set_width(const int width) override{
        this->width = height = width;
    }

    void set_height(const int height) override{
        this->height = width = height;
    }
};

void get_area(Rectangle& r)
{
    int w = r.get_width();
    r.set_height(10);

    std::cout<<"expected area: " << (w * 10)
        << ", got " << r.area() << std::endl;
}

int main()
{
    Rectangle rectangle(5, 10);
    Square square(5);

    get_area(rectangle);
    get_area(square);
}