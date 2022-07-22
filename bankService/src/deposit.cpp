#include "deposit.h"
#include "bank.h"
const int T[7]={1,3,6,9,12,24,36};

Deposit::Deposit(int a,int t,double r)
{
    amount = a;
    currentTerm = 0;
    term = T[t];
    rate = r;
}
void Deposit::print()
{
    cout<<"金額: $"<<amount<<"\n期數: "<<currentTerm<<'/'<<term<<"個月\n利率: "<<rate*100<<"%\n";
}
void Deposit::printShort()
{
    cout<<'$'<<amount<<' '<<currentTerm<<'/'<<term<<"月\n";
}
void Deposit::incrementTerm()
{
    currentTerm++;
}
bool Deposit::checkExpire()
{
    if(currentTerm==term)return true;
    return false;
}
int Deposit::expireAmount()
{
    for(int i=0;i<term;i++)amount+=amount*rate/12;
    return amount;
 // return amount+amount*rate*term/12;
}
int Deposit::cancelAmount(double r)
{
    int a=amount;
    for(int i=0;i<currentTerm;i++)amount+=amount*r/12;
    return a+(amount-a)*0.8;
//  return amount+amount*r*currentTerm/12*0.8;
}
int Deposit::getTerm()
{
    return currentTerm;
}

