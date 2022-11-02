#include <iostream>

struct Image
{
    virtual void draw() = 0;
};

struct Bitmap : Image
{
    Bitmap(const std::string& filename)
    :filename{filename}
    {
        std::cout << "Loading image from " << filename << std::endl;
    }

    void draw() override
    {
        std::cout << "Drawing image" << filename << std::endl;
    }

    std::string filename;
};

struct LazyBitmap : Image
{
    LazyBitmap(const std::string& filename)
    : filename{filename}
    {

    }
    ~LazyBitmap(){ delete bmp; }

    void draw() override
    {
        if(!bmp)
            bmp = new Bitmap(filename);
        bmp->draw();
    }

    Bitmap* bmp{nullptr};
    std::string filename;
};


void draw_image(Image& img)
{
    std::cout << "About to draw the image" << std::endl;
    img.draw();
    std::cout << "Done drawing the image" << std::endl;
}

int main()
{
    // 초가화 하는 순간 이미지 로딩
    // 성급한 인스턴스화
    Bitmap img { " test.jpg "};

    // 느긋한 인스턴스화
    LazyBitmap img2 { "test.jpg" };
    draw_image(img); // 그림 파일의 실제 로딩은 여기서 일어난다.
}