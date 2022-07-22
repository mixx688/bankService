#ifndef ACCOUNT_H
#define ACCOUNT_H
#include<iostream>
#include<vector>
#include"deposit.h"
using namespace std;
class Bank;
class Account
{
    public:
        Account();
        Account(const Account &a);
        void addDeposit(int a,int t);
        void depositing(int a);
        void withdraw(int a);
        void cancelCD(int d);
        void setName(string n);
        void setPassword(string p);
        void print();
        string getAccount();
        string getPassword();
        int getBalance();
        Deposit* accessDeposit(int d);
        vector<Deposit*> accessVector();
        void deleteDeposit(int d);
        void setBank(Bank &b);                            //用來設定*pb
    private:
        string accountName;
        string password;
        vector<Deposit*> pdeposit;
        int balance;
        Bank *pb;            //用來存放產生這個物件的物件的位置
};

#endif // ACCOUNT_H
