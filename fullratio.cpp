#include<iostream>
#ifndef CONTEST
#include "fullratio.hpp"
#endif // CONTEST

using namespace std;

void Negative(int &n ,int &d){
    if((n<0 && d>0)||(n>0 && d<0))
        if(d<0){
            d=-d;
            n=-n;
        }
}

int rational::gcd(int a,int b){
    if(a==0) return b;
    return gcd(b%a,a);
}

rational::rational(int n,int d){
    int CurrentGCD = gcd(n,d);

    nom = n/CurrentGCD;
    den = d/CurrentGCD;
}

rational operator+ (const rational &x,const rational &y){
    int NewNom = x.nom * y.den + x.den * y.nom;
    int NewDen = x.den * y.den;

    int CurrentGCD = x.gcd(NewNom,NewDen);
    rational NewRational(NewNom/CurrentGCD,NewDen/CurrentGCD);

    return NewRational;
}
rational operator- (const rational &x,const rational &y){
    int NewNom = x.nom * y.den - x.den * y.nom;
    int NewDen = x.den * y.den;

    int CurrentGCD = x.gcd(NewNom,NewDen);
    rational NewRational(NewNom/CurrentGCD,NewDen/CurrentGCD);

    return NewRational;
}
rational operator* (const rational &x,const rational &y){
    int NewNom = x.nom * y.nom;
    int NewDen = x.den * y.den;

    int CurrentGCD = x.gcd(NewNom,NewDen);
    rational NewRational(NewNom/CurrentGCD,NewDen/CurrentGCD);

    return NewRational;
}
rational operator/ (const rational &x,const rational &y){
    int NewNom = x.nom * y.den;
    int NewDen = x.den * y.nom;

    int CurrentGCD = x.gcd(NewNom,NewDen);
    rational NewRational(NewNom/CurrentGCD,NewDen/CurrentGCD);

    return NewRational;
}
ostream& operator<< (std::ostream &out,const rational &x){
    int N=x.nom,D=x.den;

    Negative(N,D);
    out<<N<<"/"<<D;

    return out;
}

