#include <iostream>
#include <utility>

namespace a {
    struct CellA {
        int x;
        CellA (int x)
        : x(x)
        {}
    };

    void f2(const a::CellA& _) {
        std::cout << "L or R" << std::endl;
    };
}

template <class T>
void passA(T&& t) {
    f2(std::forward<T>(t));
}

void f2(a::CellA&& _) {
    std::cout << "R Value" << std::endl;
}

namespace b {
    struct CellB {
        int x;
        CellB (int x)
        : x(x)
        {}
    };

    void f1(b::CellB&& _) {
        std::cout << "R Value" << std::endl;
    };
}

void f1(const b::CellB& _) {
    std::cout << "L or R" << std::endl;
}

namespace c {
    struct CellC : b::CellB {
        using b::CellB::CellB;
    };
}

namespace z {
    struct Wrapper {
        operator b::CellB() const { return b::CellB(5); }
    };
}

template <class T>
void passB(T&& t) {
    f1(t);
}

template <class T>
void forwardB(T&& t) {
    f1(std::forward<T>(t));
}

int main() {
   b::CellB testB(5);
   a::CellA testA(5);
   const b::CellB constB(5);
   const a::CellA constA(5);

   f1(testB);
   f1({5});
   f1(b::CellB(5));
   f1(std::move(testB));
   f1(std::move(constB));
   (f1)(b::CellB(5));
   {
       void f1(const b::CellB&);
       f1(b::CellB(5));
   }
   {
       using ::f1;
       f1(b::CellB(5));
   }
   f1(c::CellC(5));
   f1(c::CellC{5});
   f1(5);
   b::CellB&& refB = b::CellB(5);
   f1(refB);
   passB(b::CellB(5));
   forwardB(b::CellB(5));
   forwardB(testB);
   f1(true ? testB : b::CellB(5));
   f1(z::Wrapper{});
   std::cout << "BREAK" << std::endl;
   f2(testA);
   f2({5});
   f2(a::CellA(5));
   f2(std::move(testA));
   f2(std::move(constA));
   f2(static_cast<const a::CellA&>(a::CellA(5)));
   f2(a::CellA{5});
   f2(5);
   passA(a::CellA(5));
   passA(testA);
}
