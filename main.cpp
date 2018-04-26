#include <iostream>

#include "Proof.hh"

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    auto curve = Point(Curve::G.x, Curve::G.y);

    uint64_t x = rand();

    std::cout << "x: " << x << "\n";

    BigInt rand1 = rand();
    BigInt rand2 = rand();


    std::cout << "rand1: " << rand1 << "\n";
    std::cout << "rand2: " << rand2 << "\n";

    std::cout << "rand1: " << rand1 << "\n";
    std::cout << "rand2: " << rand2 << "\n";


    Point g = curve.scalarMult(rand1);
    Point m = curve.scalarMult(rand2);

    auto proof = generateProof(g, m, x);
    std::cout << "valid for x: " << proof.verify() << "\n";

   return 0;
}