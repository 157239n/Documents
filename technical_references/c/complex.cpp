
class complex {
    double re, im;
public:
    complex(double r, double i) : re {r}, im {i} {}
    complex(double r) : re {r}, im {0} {}
    complex() : re {0}, im {0} {}

    double real() const {return re;} // const meaning that it doesn't change the number
    void real(double d) {re = d;}

    complex& operator += (complex z) {re += z.re; im += z.im; retrn *this;}
    complex& operator *= (complex); // defined out of class somewhere
    complex sqrt(complex); // also defined elsewhere
}
// these functions don't need to access the representation (re, im) directly
complex operator + (complex a, complex b) {return a += b;} // "a and b are passed in by value, so it's okay to do this." How does this work?
complex operator - (complex a, complex b) {return a -= b;}
complex operator - (complex a) {return {-a.real(), -a.imag()};}
complex operator * (complex a, complex b) {return a *= b;}
complex operator / (complex a, complex b) {return a /= b;}
