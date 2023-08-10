#include <memory>
#include <string_view>
#include <iostream>
#include <vector>
#include <algorithm>
#include <optional>

class R5
{
public:
    R5()
    {
        std::cout << "R5()\n";
    }
    ~R5()
    { std::cout << "~R5\n";
        
    }
    R5(int a)
        : a_(a)
    {
        std::cout << "R5(int)\n";
    }
    R5(const R5& rhs)
        : a_(rhs.a_)
    {
        std::cout << "R5(const R5&)\n";
    }
    R5& operator=(const R5& rhs)
    {
        std::cout << "R5=(const R5&)\n";
        if (&rhs != this) {
            a_ = rhs.a_;
        }
        return *this;
    }
    R5(R5&& rhs) noexcept
        : a_(std::move(rhs.a_))
    {
        std::cout << "R5(R5&&)\n";
    }
    R5& operator=(R5&& rhs) noexcept
    {
        std::cout << "R5=(R5&&)\n";
        std::swap(a_, rhs.a_);
        return *this;
    }

private:
    int a_ = 666;
};

class R45
{
public:
    R45()
    {
        std::cout << "R45()\n";
    }
    ~R45()
    {
        std::cout << "~R45()\n";
    }
    R45(int a)
        : a_(a)
    {
        std::cout << "R45(int)\n";
    }
    R45(const R45& rhs)
        : a_(rhs.a_)
    {
        std::cout << "R45(const R45&)\n";
    }
    R45& operator=(R45 rhs)
    {
        std::cout << "R45=(const R45&)\n";
        swap(rhs);
        return *this;
    }
    R45(R45&& rhs)
    noexcept
        : a_(std::move(rhs.a_))
    {
        std::cout << "R45(R45&&)\n";
    }

private:
    void swap(R45& rhs) noexcept(true)
    {
        std::cout << "swap(R45&)\n";
        std::swap(a_, rhs.a_);
    }

    int a_ = 666;
};

int main(int argc, char* argv[])
{
    return 0;
}
