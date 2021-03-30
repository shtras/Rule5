#include <memory>
#include <string_view>
#include <iostream>
#include <vector>
#include <algorithm>

class Metric;

Metric* gMetric = nullptr;
bool printDetails = true;
void print(std::string s)
{
    if (printDetails) {
        std::cout << s << "\n";
    }
}

class Metric
{
public:
    Metric(std::string name)
        : name(name)
    {
        gMetric = this;
    }
    Metric(const Metric&) = delete;
    Metric(Metric&&) = delete;
    Metric& operator=(const Metric&) = delete;
    Metric& operator=(Metric&&) = delete;
    ~Metric()
    {
        std::cout << "==== " << name << " ====\n"
                  << "| A()"
                  << "\t"
                  << "| ~A()"
                  << "\t"
                  << "| A(&)"
                  << "\t"
                  << "| A(&&)"
                  << "\t"
                  << "| A=(&)"
                  << "\t"
                  << "| A=(&&)\n";
        std::cout << "| " << ctrs << "\t| " << dtrs << "\t| " << copyctrs << "\t| " << movectrs << "\t| " << copyassigns
                  << "\t| " << moveassigns << "\n";
    }

    static void ctr()
    {
        if (gMetric) {
            ++gMetric->ctrs;
        }
    }
    static void dtr()
    {
        if (gMetric) {
            ++gMetric->dtrs;
        }
    }
    static void copyctr()
    {
        if (gMetric) {
            ++gMetric->copyctrs;
        }
    }
    static void movectr()
    {
        if (gMetric) {
            ++gMetric->movectrs;
        }
    }
    static void copyassign()
    {
        if (gMetric) {
            ++gMetric->copyassigns;
        }
    }
    static void moveassign()
    {
        if (gMetric) {
            ++gMetric->moveassigns;
        }
    }

private:
    int ctrs = 0;
    int dtrs = 0;
    int copyctrs = 0;
    int movectrs = 0;
    int copyassigns = 0;
    int moveassigns = 0;
    std::string name;
};

class R5
{
public:
    R5()
    {
        print("R5()");
        Metric::ctr();
    }
    ~R5()
    {
        print("~R5");
        Metric::dtr();
    }
    R5(int a)
        : a_(a)
    {
        print("R5(int)");
        Metric::ctr();
    }
    R5(const R5& rhs)
        : a_(rhs.a_)
    {
        print("R5(const R5&)");
        Metric::copyctr();
    }
    R5& operator=(const R5& rhs)
    {
        print("R5=(const R5&)");
        if (&rhs != this) {
            a_ = rhs.a_;
        }
        Metric::copyassign();
        return *this;
    }
    R5(R5&& rhs)
        : a_(std::move(rhs.a_))
    {
        print("R5(R5&&)");
        Metric::movectr();
    }
    R5& operator=(R5&& rhs)
    {
        print("R5=(R5&&)");
        std::swap(a_, rhs.a_);
        Metric::moveassign();
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
        print("R45()");
        Metric::ctr();
    }
    ~R45()
    {
        print("~R45()");
        Metric::dtr();
    }
    R45(int a)
        : a_(a)
    {
        print("R45(int)");
        Metric::ctr();
    }
    R45(const R45& rhs)
        : a_(rhs.a_)
    {
        print("R45(const R45&)");
        Metric::copyctr();
    }
    R45& operator=(R45 rhs)
    {
        print("R45=(const R45&)");
        swap(rhs);
        Metric::copyassign();
        return *this;
    }
    R45(R45&& rhs)
    noexcept
        : a_(std::move(rhs.a_))
    {
        print("R45(R45&&)");
        Metric::movectr();
    }

private:
    void swap(R45& rhs) noexcept(true)
    {
        print("swap(R45&)");
        std::swap(a_, rhs.a_);
    }

    int a_ = 666;
};

template <class T>
void inner(T&&)
{
}

R5 gr5;

void tworefs(R5&& r5)
{
    print("tworefs1");
    inner(r5);
    gr5 = std::move(r5);
}

void tworefs(const R5& r5)
{
    print("tworefs2");
    inner(r5);
    gr5 = r5;
}

template <class T>
void uniref(T&& t)
{
    print("uniref");
    inner(t);
    gr5 = std::forward<T>(t);
}

void constref(const R5& r5)
{
    print("constref");
    inner(r5);
    gr5 = r5;
}

void byval(R5 r5)
{
    print("byval");
    inner(r5);
    gr5 = std::move(r5);
}

int main(int argc, char* argv[])
{
    printDetails = false;
    R5 r5(123);
    {
        Metric m("Const reference");
        constref(r5);
        constref(R5());
        constref(222);
    }

    {
        Metric m("Universal reference");
        uniref(r5);
        uniref(R5());
        uniref(333);
    }

    {
        Metric m("Two functions");
        tworefs(r5);
        tworefs(R5());
        tworefs(333);
    }

    {
        Metric m("By value");
        byval(r5);
        byval(R5());
        byval(333);
    }
    return 0;
}