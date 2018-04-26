//
// Created by algys on 4/26/18.
//

#ifndef DLEQ_ECC_HH
#define DLEQ_ECC_HH
#include "lib/BigInt.hpp"

// secp256k1 curve
namespace Curve {
    static const BigInt p {"115792089237316195423570985008687907853269984665640564039457584007908834671663"};
    static const BigInt a {"0"};
    static const BigInt b {"7"};
    static const BigInt n {"115792089237316195423570985008687907852837564279074904382605163141518161494337"};

    static const struct {
        BigInt x;
        BigInt y;
    } G = { {"55066263022277343669578718895168534326250603453777594175500187360389116729240"},
            {"32670510020758816978083085130507043184471273380659243275938904335757337482424"} };
};

class Point {
public:
    Point() = default;

    Point(BigInt x, BigInt y) :
        _x{x}, _y{y}
    { }

    //R = P + Q
    Point add(Point const & point) {
        if (point == *this)
            return dbl();

        auto l = (point.y() - _y) / (point.x() - _x);

        auto x = l * l - _x - point.x();
        auto y = l * (_x - x) - _y;

        return {x, y};
    }

    //R = P+P
    Point dbl() {
        if (_y == 0 || _x == 0)
            return *this;

        auto l = 3 * _x * _x / (2 * _y);

        auto x = l * l - 2 * _x;
        auto y = l * (_x - x) - _y;

        return {x, y};
    }

    Point scalarMult(BigInt scalar) {
        auto n = *this;
        Point q{};
        while(scalar > 0) {
            q = q.dbl();
            if (scalar % 2 != 0)
                q = q.add(*this);
            scalar = scalar / 2;
        }
        return q;
    }

    bool isOnCurve() {
        return true;
    }

    friend bool operator== (Point const & lhs, Point const & rhs) {
        return lhs._x == rhs._x && lhs._y == rhs._y;
    }

    const BigInt & x() const {
        return _x;
    }

    const BigInt & y() const {
        return _y;
    }

    private:
    BigInt _x{};
    BigInt _y{};
};


#endif //DLEQ_ECC_HH
