//
// Created by algys on 4/19/18.
//

#ifndef DLEQ_PROOF_HH
#define DLEQ_PROOF_HH

#include <array>
#include <cstring>
#include "Ecc.hh"


struct Proof {
    Proof() = default;

    Point g, m;
    Point h, z;
    Point a, b;

    uint256_t r, c;

    bool verify() {
        if (!h.isOnCurve() || !g.isOnCurve())
            return false;

        if (!z.isOnCurve() || !m.isOnCurve())
            return false;

        auto ch = h.scalarMult(c);
        auto rg = g.scalarMult(r);
        auto aa = rg.add(ch);

        auto cz = z.scalarMult(c);
        auto rm = m.scalarMult(r);
        auto bb = rm.add(cz);

        return a == aa && b == bb;
    }

    static Proof generate(Point g, Point m, uint256_t x) {
        uint256_t c = rand();

        // s must be large then Curve.N
        uint256_t s = Secp256k1.n;
        s += rand();

        uint256_t r{};

        c = c % Secp256k1.n;
        r = (s - c * x) % Secp256k1.n;

        auto a = g.scalarMult(s);
        auto b = m.scalarMult(s);

        return {
            g, m,
            g.scalarMult(x), m.scalarMult(x),
            a, b,
            r, c
        };
    }
};

#endif //DLEQ_PROOF_HH
