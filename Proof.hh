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

    BigInt r, c;

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
};

Proof generateProof(Point g, Point m, BigInt x) {
    Proof proof{};

    BigInt c = 12345;
    BigInt s = 12332334;

    BigInt r{};

    c = c % Curve::p;

    c = (c * x) % Curve::p;
    r = (s - c) % Curve::p;

    auto a = g.scalarMult(s);
    auto b = m.scalarMult(s);

    proof.a = a;
    proof.b = b;
    proof.g = g;
    proof.m = m;
    proof.h = g.scalarMult(x);
    proof.z = m.scalarMult(x);
    proof.c = c;
    proof.r = r;

    return proof;
}

#endif //DLEQ_PROOF_HH
