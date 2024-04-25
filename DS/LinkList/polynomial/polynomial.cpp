#include "polynomial.h"

using namespace Poly;

inline void Term::setCoef(double c) noexcept { coef = c; }

inline void Term::setExp(int e) noexcept { exp = e; }

void Polynomial::sort(const std::function<bool(const Term &, const Term &)> &cmp) noexcept
{
    std::sort(poly.begin(), poly.end(), cmp);
}

Polynomial::Polynomial() = default;
Polynomial::Polynomial(const std::initializer_list<Term> &list)
    : poly(list)
{
    // 按指数递增排序
    std::sort(poly.begin(), poly.end(),
              [](const Term &a, const Term &b)
              { return a.getExp() < b.getExp(); });
}

Polynomial::Polynomial(const Polynomial &p)
try : poly(p.poly)
{
}
catch (...)
{
    std::cerr << "copy constructor failed\n";
    throw;
}

constexpr Polynomial::Polynomial(Polynomial &&p)
try : poly(std::move(p.poly))
{
}
catch (...)
{
    std::cerr << "move constructor failed\n";
    throw;
}

Polynomial::~Polynomial() = default;

Polynomial &Polynomial::operator=(Polynomial other) noexcept
{
    std::swap(poly, other.poly);
    return *this;
}

// 重载加法运算符
Polynomial Polynomial::operator+(const Polynomial &other) const
{
    Polynomial result;
    auto otherIt = other.poly.begin();
    auto thisIt = poly.begin();
    // 将长度小的作为主循环
    while (thisIt != poly.end() && otherIt != other.poly.end())
    {
        if (thisIt->exp < otherIt->exp)
        {
            result.poly.push_back(*thisIt);
            ++thisIt;
        }
        else if (thisIt->exp > otherIt->exp)
        {
            result.poly.push_back(*otherIt);
            ++otherIt;
        }
        else
        {
            if (thisIt->coef + otherIt->coef != 0)
                result.poly.push_back(*thisIt + *otherIt);
            ++thisIt;
            ++otherIt;
        }
    }
    // 将剩余的元素添加到结果中
    while (thisIt != poly.end())
    {
        result.poly.push_back(*thisIt);
        ++thisIt;
    }
    while (otherIt != other.poly.end())
    {
        result.poly.push_back(*otherIt);
        ++otherIt;
    }
    return result;
}

// 利用加法重载减法运算符
// 利用传入参数的拷贝构造函数可以减少代码量
Polynomial Polynomial::operator-(Polynomial other) const
{
    for (auto &t : other.poly)
        t.setCoef(-t.getCoef());
    return *this + other;
}

void Polynomial::insert(const Term &t)
{
    for (auto it = poly.begin(); it != poly.end(); ++it)
    {
        if (it->getExp() == t.getExp())
        {
            it->setCoef(it->getCoef() + t.getCoef());
            return;
        }
        if (it->getExp() > t.getExp())
        {
            poly.insert(it, t);
            return;
        }
    }
}

void Polynomial::print(const std::size_t &precision,
                       const std::size_t &width) const
{
    auto t = poly.begin();
    for (; t != poly.end(); ++t)
    {
        std::cout.precision(precision);
        std::cout.width(width);
        std::cout << t->getCoef() << "x^" << t->getExp() << " ";
    }
    if ((t + 1) == poly.end())
        std::cout << '\n';
}

inline bool Polynomial::empty() const noexcept
{
    return poly.empty();
}

inline size_t Polynomial::size() const noexcept
{
    return poly.size();
}

double Polynomial::cal(double x) const noexcept
{
    // 递归计算多项式的值
    double result = 0;
    for (auto &t : poly)
        result += t.cal(x);
    return result;
}

auto Polynomial::begin() noexcept
{
    return poly.begin();
}

auto Polynomial::end() noexcept
{
    return poly.end();
}

auto Polynomial::cbegin() const noexcept
{
    return poly.cbegin();
}

auto Polynomial::cend() const noexcept
{
    return poly.cend();
}



