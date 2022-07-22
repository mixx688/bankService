#include "account.h"
#include "bank.h"
const int T[7]={1,3,6,9,12,24,36};

Account::Account()
{
    accountName = "";
    password = "";
    balance=0;
}
Account::Account(const Account &a)
{
    accountName=a.accountName;
    password=a.password;
    balance=a.balance;
    pb=a.pb;
    for(int i=0; i<pdeposit.size(); i++)
        *pdeposit[i] = *a.pdeposit[i];
}
void Account::addDeposit(int a,int t)
{
    double r = pb->getRateCD(t);
    Deposit *d = new Deposit(a,t,r);
    pdeposit.push_back(d);
}
void Account::depositing(int a)
{
    balance+=a;
}
void Account::withdraw(int a)
{
    balance-=a;
}
void Account::cancelCD(int d)
{
    int t=accessDeposit(d)->getTerm();
    int i=0;
    while(t>=T[i])i++;
    double r=pb->getRateCD(i-1);
    int c=accessDeposit(d)->cancelAmount(r);
    depositing(c);
    deleteDeposit(d);
    pb->generateInfo(getAccount(),c,getBalance(),pb->getYear(),pb->getMonth());
    cout<<"定存解約成功！\n本金加利息$"<<c<<"已經歸還至帳戶！\n";
}
void Account::setName(string n)
{
    accountName = n;
}
void Account::setPassword(string p)
{
    password = p;
}
void Account::print()
{
    cout <<"歡迎!使用者為"<<getAccount();
    cout <<"\n存款餘額: $"<<getBalance()<<"\n";
}
string Account::getAccount()
{
    return accountName;
}
string Account::getPassword()
{
    return password;
}
int Account::getBalance()
{
    return balance;
}
Deposit* Account::accessDeposit(int d)
{
    return pdeposit[d];
}
vector<Deposit*> Account::accessVector()
{
    return pdeposit;
}
void Account::deleteDeposit(int d)
{
    pdeposit.erase(pdeposit.begin()+d);
}
void Account::setBank(Bank &b)
{
    pb = &b;
}
