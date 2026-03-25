#include <concepts>
#include <iostream>
#include <numeric>



template<typename I> 
requires std::integral<I>

class rational
{
private:

    I num_;
    I den_;
    void check_n_fix() {

        // gestione numeratore = 0 e normalizzazione ---> 1/0 o -1/0
        if (den_ == 0) {
            if (num_ != 0) {
                num_ = (num_ > 0 ) ? 1 : -1;
            }
            return;
        }
 
        // se numeratore = 0 metto denominatore a 0 ---> 0/1
        if (num_ == 0) {
            den_ = 1;
            return;
        }

        // sposto segno del denominatore sempre al numeratore
        if (den_ < 0) {
            num_ = -num_;
            den_ = -den_;
        }

        // trovo MCD con gcd e semplifico il razionale
        auto g = std::gcd(num_ < 0 ? -num_ : num_, den_);
        if (g > 1) {
            num_ /= g;
            den_ /= g;
        }
    }

public:

    rational() : num_(0), den_(1) {}

    rational(const I& n, const I& d) 
        : num_(n), den_(d) {
        check_n_fix();
    }

    I num() const { return num_; }
    I den() const { return den_; }


    // funzioni per il controllo di NaN e INF
    bool is_nan() const {
        if (num_ == 0 && den_ == 0) {
            return true;
        } else {
            return false;
        }
    }

    bool is_inf() const {
        if (num_ != 0 && den_ == 0) {
            return true;
        } else {
            return false;
        }
    }

    //operatori di incremento per le 4 operazioni
    
    rational& operator+=(const rational& other) {

        if (is_nan() || other.is_nan()) {
            num_ = 0; 
            den_ = 0;
            return *this;
        }
        if (is_inf()) {
            if (other.is_inf() && (num_ > 0) != (other.num_ > 0)) {
                num_ = 0; 
                den_ = 0; 
            }
            return *this;
        }
        if (other.is_inf()) {
            num_ = other.num_; den_ = 0;
            return *this;
        }

        num_ = num_ * other.den_ + other.num_ * den_;
        den_ *= other.den_;

        check_n_fix();
        return *this;
    }

    rational& operator-=(const rational& other) {
        return *this += rational(-other.num_, other.den_);
    }

    rational& operator*=(const rational& other) {
        if (is_nan() || other.is_nan()) {
            num_ = 0; 
            den_ = 0;
            return *this;
        }
        if ((is_inf() && other.num_ == 0) || (num_ == 0 && other.is_inf())) {
            num_ = 0; 
            den_ = 0;
            return *this;
        }

        num_ *= other.num_;
        den_ *= other.den_;
        check_n_fix();
        return *this;
    }

    rational& operator/=(const rational& other) {
        if (is_nan() || other.is_nan() || (is_inf() && other.is_inf())) {
            num_ = 0; 
            den_ = 0;
            return *this;
        }
        if (other.num_ == 0 && other.den_ != 0) {
            den_ = 0;
            check_n_fix();
            return *this;
        }
        num_ *= other.den_;
        den_ *= other.num_;
        check_n_fix();
        return *this;
    }

    // 4 operatori delle operazioni
    rational operator+(const rational& other) const {
        rational ret = *this;
        ret += other;
        return ret;
    }

    rational operator-(const rational& other) const {
        rational ret = *this;
        ret -= other;
        return ret;
    }

    rational operator*(const rational& other) const {
        rational ret = *this;
        ret *= other;
        return ret;
    }

    rational operator/(const rational& other) const {
        rational ret = *this;
        ret /= other;
        return ret;
    }
};

template<typename I>
std::ostream& operator<<(std::ostream& os, const rational<I>& r) {
    if (r.is_nan()) {
        os << "NaN";
    }      
    else if (r.is_inf()) {
        os << (r.num() > 0 ? "+Inf" : "-Inf");
    } 
    else if (r.den() == 1) {
        os << r.num();
    }
    else{
        os << r.num() << "/" << r.den();
    }                 
    return os;
}