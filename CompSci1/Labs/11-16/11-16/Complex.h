#ifndef Complex_h
#define Complex_h

class Complex{
public:
    
    void setReal(double real);
    
    void setImag(double imag);
    
    double getReal();
    
    double getImag();
    
    void print();
    
    Complex addComplex(Complex a, Complex b);
    
    Complex subComplex(Complex a, Complex b);
    
    
    
private:
    double real_;
    double imag_;
    
};


#endif