#ifndef BANK_H
#define BANK_H
#include<iostream>
#include<vector>
#include<iomanip>
#include<cstddef>
#include"account.h"
using namespace std;

struct info
{
    string accountName;
    int change; // 存入/領出
    int balance;// 餘額
    int year;
    int month;
};

class Bank
{
    public:
        Bank();
        int loginCheck(string n,string p);
        void addAccount(string n,string p, int a, Bank &b);
        void adjustRate(double r);
        void adjustRateCD(int t, double r);
        double getRate();
        double getRateCD(int t);
        void nextMonth();                              //用來模擬隨時間流動銀行要做的事情
        void generateInfo(string n, int c, int b, int y, int m);
        void showInfo();
        void showRate();
        bool checkDuplicate(string a);
        int getUser();
        int getYear();
        int getMonth();
        void changeUser(int u);
        Account* accessAccount(int a);
    private:
        double rate;
        double rateCD[7];         //0-6分別代表1,3,6,9,12,24,36個月的利率
        Account accounts[1000]; //最多可存放1000個帳戶
        int accountCount;       //紀錄有幾個帳戶存在
        int user;               //-1代表未登入，0-999代表登入的帳號的index
        int year;
        int month;
        vector<info> infos;     //交易紀錄
};

#endif // Bank_H
