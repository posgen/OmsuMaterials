#include <iostream>
#include <ostream>
#include <istream>
#include <string>

using namespace std;

/// Базовый класс, являющийся полиморфным
class Base
{
public:
    Base(const string& details) : details_{details}
    {}

    /// Дейструктор полиморфного класса всегда должен быть
    /// объявлен виртуальным (эмпирическое правило, не требования самого C++)
    virtual ~Base() = default;

    string details() const
    { return details_; }

    void set_details(const string& new_details)
    { details_ = new_details; }

    /// виртуальный метод
    virtual string about() const
    {
        return "[Base] with details: " + details_;
    }

private:
    string details_;
};

/// Абстрактный или чисто виртуальный (pure-virtual) тип
class VBase
{
public:
    /// Абстрактный метод
    virtual string about_me() const = 0;
};

void print_about(const VBase& vb)
{
    cout << vb.about_me() << endl;
}

/// Производный класс: допустимо и множественное наследование
class Derived : public Base, public VBase
{
public:
    explicit Derived(string details, string description) :
        Base{details}, description_{description}
    {}

    /// Переопределённый виртуальный метод базового класса
    string about() const override
    {
        return Base::about() + "\n[Derived] with description: "
            + description_;
    }

    string about_me() const override
    {
        return "me + " + about();
    }

    /// Пример дружественной функции
    friend ostream& operator<<(ostream& out, const Derived& d_obj);

private:
    string description_;
};

ostream& operator<<(ostream& out, const Derived& d_obj)
{
    out << "<{"<< d_obj.details() << "}, {"
        << d_obj.description_ << "}>";
    return out;
}

class D3 : public Derived
{
public:
    /// Как использовать конструкторы базового класса в производном
    using Derived::Derived;

    string about() const override
    {
        return "D3";
    }
};

void test_explicit(const Derived& d_obj)
{
    cout << d_obj.details() << endl;
}


int main()
{
    Base b1{"red, green, blur"};
    cout << b1.about() << endl << endl;

    Derived d1{"one, two, three", "something important"};
    cout << d1.about() << endl << endl;

    Base b2 = d1;
    Base& ref_b1 = d1;
    Base* ptr_b1 = &d1;

    cout  << "obj-to-obj" << b2.about() << endl
          << "------------------"<< endl;

    cout  << "ref-to-obj" << ref_b1.about() << endl
          << "------------------"<< endl;

    cout  << "ptr-to-obj" << ptr_b1->about() << endl
          << "------------------"<< endl;

    cout << endl << d1 << endl;

    D3 d3{"a", "b"};
    ptr_b1 = &d3;
    cout  << "ptr-to-obj(2)" << ptr_b1->about() << endl
          << "------------------"<< endl;

    print_about(d1);
    print_about(d3);


    test_explicit(Derived{"c, b, a", "what's"});
}
