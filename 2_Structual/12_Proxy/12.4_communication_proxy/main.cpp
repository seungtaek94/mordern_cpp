#include <iostream>

struct Pingable
{
    virtual std::wstring ping(const std::wstring& message) = 0;
};

struct Pong : Pingable
{
    std::wstring ping(const std::wstring& message) override
    {
        return message + L" pong";
    }
};


void tryit(Pingable& pp)
{
    std::wcout << pp.ping(L"ping") << "\n";
}

int main()
{
    Pong pp;
    for(int i=0; i<3; ++i)
    {
        tryit(pp);
    }

}