#include<iostream>
#include<cmath>

using namespace std;

class Polynomial {
protected:
    class Term{
    public:
        int exponent;
        int coefficient;
        Term *next;
    protected:
        Term(int exp,int coeff, Term *n): exponent(exp),coefficient(coeff),next(n){}
        friend class Polynomial;
    };

public:

    Polynomial(){
        Head = nullptr;
    }
    Polynomial(const Polynomial &p){
        Head = nullptr;
        Term *CurrentTerm = p.Head;
        while(CurrentTerm){
            addTerm(CurrentTerm->exponent,CurrentTerm->coefficient);
            CurrentTerm = CurrentTerm->next;
        }
    }
    ~Polynomial(){
        Term *Temp=Head;
        while(Temp){
            Term *DeleteNode = Temp;
            Temp = Temp->next;
            delete DeleteNode;
        }
    }

    Polynomial& operator = (const Polynomial &p){
        Term *TempNode = Head;
        while(TempNode){
            Term *DeleteNode = TempNode;
            TempNode = TempNode->next;
            delete DeleteNode;
        }

        Term *TermP=p.Head;
        while(TermP){
            addTerm(TermP->exponent,TermP->coefficient);
            TermP = TermP -> next;
        }
        return *this;
    }

    void addTerm(int expon,int coeff){
        Term *NewTerm = new Term(expon,coeff,nullptr);
        if(!Head){
            Head= NewTerm;
            return;
        } else if (expon > Head->exponent) {
            NewTerm->next = Head;
            Head = NewTerm;
            return;
        } else if(Head->exponent == expon){
            Head->coefficient += coeff;
            delete NewTerm;
            return;
        } else {
            Term *Termptr = Head;
            while (Termptr->next && Termptr->next->exponent > expon) {
                Termptr = Termptr->next;
            }
            if (Termptr->exponent == expon) {
                Termptr->coefficient += coeff;
                delete NewTerm;
                return;
            } else if (Termptr->next && Termptr->next->exponent == expon) {
                Termptr->next->coefficient += coeff;
                delete NewTerm;
                return;
            }else {
                NewTerm->next = Termptr->next;
                Termptr->next = NewTerm;
                return;
            }
        }
    }
    double evaluate(double x){
        Term *CurrentTerm = Head;
        double Result=0;

        if(Head==nullptr) return 0;

        while(CurrentTerm){
            Result += CurrentTerm->coefficient * pow(x,CurrentTerm->exponent);
            CurrentTerm = CurrentTerm ->next;
        }

        return Result;
    }

    friend Polynomial operator+ (const Polynomial &p, const Polynomial &q){
        Polynomial Results;
        Term *TermP=p.Head,*TermQ=q.Head;
        while(TermP && TermQ){
            if(TermP->exponent==TermQ->exponent) {
                Results.addTerm(TermP->exponent,TermP->coefficient + TermQ->coefficient);
                TermP = TermP->next;
                TermQ = TermQ->next;
            }
            else if(TermP->exponent > TermQ->exponent){
                Results.addTerm(TermP->exponent, TermP->coefficient);
                TermP = TermP->next;
            }
            else {
                Results.addTerm(TermQ->exponent, TermQ->coefficient);
                TermQ = TermQ->next;
            }
        }
        while(TermP){
            Results.addTerm(TermP->exponent,TermP->coefficient);
            TermP = TermP->next;
        }
        while(TermQ){
            Results.addTerm(TermQ->exponent,TermQ->coefficient);
            TermQ = TermQ->next;
        }
        return Results;
    }
    friend Polynomial operator* (const Polynomial &p, const Polynomial &q){
        Polynomial Results;
        Term *TermP=p.Head;
        while(TermP){
            Term *TermQ=q.Head;
            while(TermQ){
                Results.addTerm(TermP->exponent+TermQ->exponent,TermP->coefficient*TermQ->coefficient);
                TermQ = TermQ->next;
            }
            TermP = TermP->next;
        }
        return Results;
    }

    friend ostream & operator<< (ostream &out, const Polynomial &p){
        Term *CurrentTerm = p.Head;
        if(CurrentTerm==nullptr) {
            out<<'0';
            return out;
        }

        while(CurrentTerm->coefficient==0){
            CurrentTerm = CurrentTerm->next;
            if(CurrentTerm==nullptr){
                out<<'0';
                return out;
            }
        }
        if(CurrentTerm->coefficient < 0)
            out << "- ";
        if(abs(CurrentTerm->coefficient) != 1)
            out << abs(CurrentTerm->coefficient);
        if(CurrentTerm->exponent == 0 && abs(CurrentTerm->coefficient) == 1)
            out << "1";
        if(CurrentTerm->exponent == 1)
            out << "x";
        else if(CurrentTerm->exponent != 0)
            out << "x^" << CurrentTerm->exponent;

        CurrentTerm = CurrentTerm->next;
        while(CurrentTerm != nullptr) {
            if(CurrentTerm->coefficient!=0){
                if(CurrentTerm->coefficient < 0) {
                    out << " - ";
                }
                else {
                    out << " + ";
                }
                if(abs(CurrentTerm->coefficient) != 1 || CurrentTerm->exponent == 0) {
                    out << abs(CurrentTerm->coefficient);
                }
                if(CurrentTerm->exponent == 1) {
                    out << "x";
                }
                else if(CurrentTerm->exponent != 0) {
                    out << "x^" << CurrentTerm->exponent;
                }
            }
            CurrentTerm = CurrentTerm->next;
        }
        return out;
    }
private:
    Term* Head;
};

