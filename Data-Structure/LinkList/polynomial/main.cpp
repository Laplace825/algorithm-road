#include "polynomial.h"

int main()
{
    using namespace Poly;
    constexpr std::array<Term, 3> ts = {Term(1.3, 3), Term(2.55, -1), Term(3.04, 5)};
    Polynomial polys(ts);
    Polynomial polys2({Term(-1.3, 3), Term(-2.55, -1), Term(-3.04, 5)});
    polys.print();
    polys2.print();
    (polys2 + polys).print();
    std::cout << polys.cal(2) << '\n';
    constexpr Polynomial_C polyC(ts);
    polyC.print();
    constexpr auto value = polyC.cal(2);
}
