#include <iostream>

#include "Proof.hh"

// Simple scalar multiplication test
void multTest() {
    auto curve = Point(Secp256k1, Secp256k1.G.x, Secp256k1.G.y);

    auto q = curve;
    std::cout << "Curve point: " << q.x() << " " << q.y() << "\n";

    std::cout << "Is on curve ? " << q.isOnCurve() << "\n";

    for (auto i = 2; i < 10; ++i) {
        q = q.add(curve);
        std::cout << "Curve point: " << q.x() << " " << q.y() << "\n";

        auto g = curve.scalarMult(i);

        if (q != g)
            std::cout << "Fail " << i << "\n";
        else
            std::cout << "Success " << i << "\n";
    }
}


// NIZK proof test
void proofTest() {
    srand(static_cast<unsigned int>(time(nullptr)));

    // ECC curve secp256k1
    auto curve = Point(Secp256k1.G.x, Secp256k1.G.y);

    // Secret value
    uint256_t x = rand();

    std::cout << "x: " << x << "\n";

    // Random private keys
    uint256_t rand1 = rand();
    uint256_t rand2 = rand();

    std::cout << "rand1: " << rand1 << "\n";
    std::cout << "rand2: " << rand2 << "\n";

    // Init generators (public keys)
    Point g = curve.scalarMult(rand1);
    Point m = curve.scalarMult(rand2);
    std::coud << "g: " << g.x() << " " < g.y() << "\n";
    std::coud << "m: " << m.x() << " " < m.y() << "\n";


    // Prepare list of random tests
    std::vector<uint256_t> cList;
    for (auto k = 0; k < 5; ++k)
        cList.push_back((uint256_t)rand());

    // Proof
    auto proof = Proof::generate(g, m, x, cList);

    // Print a, b
    std::cout << "Proof generated\n";
    std::cout << "a: " << proof.a.x() << " " << proof.a.y() << "\n";
    std::cout << "b: " << proof.b.x() << " " << proof.b.y() << "\n";

    // Validate
    std::cout << "valid for x: " << proof.verify() << "\n";
}

int main() {

    multTest();

    proofTest();

    return 0;
}