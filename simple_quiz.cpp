#include <bits/stdc++.h>

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

int main() {
   b::CellB testB(5);
   a::CellA testA(5);
   f1(testB); 
   f1({5}); 
   f1(b::CellB(5)); 
   std::cout << "BREAK" << std::endl;
   f2(testA); 
   f2({5}); 
   f2(a::CellA(5)); 
}
