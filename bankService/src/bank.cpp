#include "bank.h"

const int T[7]={1,3,6,9,12,24,36};

Bank::Bank()
{
    user= -1;
    accountCount=0;
    rate=0.002;
    rateCD[0]=0.006;
    rateCD[1]=0.0063;
    rateCD[2]=0.00795;
    rateCD[3]=0.0091;
    rateCD[4]=0.01035;
    rateCD[5]=0.0104;
    rateCD[6]=0.01065;
    year=2019;
    month=6;
}
int Bank::loginCheck(string n,string p)
{
    for(int i=0; i<accountCount; i++)
    {
          if(accounts[i].getAccount()==n&&accounts[i].getPassword()==p)
                return i;
    }
    return -1;
}
void Bank::addAccount(string n, string p, int a, Bank &b)
{
    accounts[accountCount].setName(n);
    accounts[accountCount].setPassword(p);
    accounts[accountCount].setBank(b);
    accounts[accountCount].depositing(a);
    accountCount++;
}
void Bank::adjustRate(double r)
{
    rate = r/100;
}
void Bank::adjustRateCD(int t, double r)
{
    rateCD[t] = r/100;
}
double Bank::getRate()
{
    return rate;
}
double Bank::getRateCD(int t)
{
    return rateCD[t];
}
void Bank::nextMonth()
{
    month++;
    if(month>12)
    {
        year++;
        month=1;
    }
    for(int i=0; i<accountCount; i++)
    {
        int c=rate/12*accessAccount(i)->getBalance();
        accessAccount(i)->depositing(c);
        generateInfo(accessAccount(i)->getAccount(),c,accessAccount(i)->getBalance(),year,month);
    }
    for(int i=0; i<accountCount; i++)
    {
        for(int j=0; j<accessAccount(i)->accessVector().size(); j++)
        {
            if(accessAccount(i)->accessDeposit(j)!=NULL)
            {
                accessAccount(i)->accessDeposit(j)->incrementTerm();
                if(accessAccount(i)->accessDeposit(j)->checkExpire())
                {
                    int c=accessAccount(i)->accessDeposit(j)->expireAmount();
                    accessAccount(i)->depositing(c);
                    accessAccount(i)->deleteDeposit(j);
                    generateInfo(accessAccount(i)->getAccount(),c,accessAccount(i)->getBalance(),year,month);
                }
            }
        }
    }
}
void Bank::generateInfo(string n,int c, int b, int y,int m)
{
    info i;
    i.accountName = n;
    i.change = c;
    i.balance = b;
    i.year = y;
    i.month = m;
    infos.push_back(i);
}
void Bank::showInfo()
{
    if(infos.size()==0)
        cout<<"目前無交易紀錄！\n";
    else
    {
    cout<<"帳號        收入/支出 餘額      年/月\n";
    for(int i=0; i<infos.size(); i++)
        cout<<left<<setw(12)<<infos[i].accountName<<setw(10)<<showpos<<infos[i].change<<setw(10)<<noshowpos<<infos[i].balance<<infos[i].year<<'/'<<infos[i].month<<endl;
    }
}
void Bank::showRate()
{
    cout <<"活期利率: "<<rate*100<<"%\n";
    cout <<"定存利率:\n";
    cout <<"期數(月)  利率\n";
    for(int i=0; i<7; i++)
        cout<<setw(2)<<T[i]<<"        "<<setw(5)<<rateCD[i]*100<<"%\n";
}
bool Bank::checkDuplicate(string a)
{
    for(int i=0; i<accountCount; i++)
        if(accounts[i].getAccount()==a)
        return true;
    return false;
}
int Bank::getUser()
{
    return user;
}
int Bank::getYear()
{
    return year;
}
int Bank::getMonth()
{
    return month;
}
void Bank::changeUser(int u)
{
    user = u;
}
Account* Bank::accessAccount(int a)
{
    return &accounts[a];
}
