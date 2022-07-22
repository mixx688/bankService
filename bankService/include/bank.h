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
    int change; // �s�J/��X
    int balance;// �l�B
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
        void nextMonth();                              //�ΨӼ����H�ɶ��y�ʻȦ�n�����Ʊ�
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
        double rateCD[7];         //0-6���O�N��1,3,6,9,12,24,36�Ӥ몺�Q�v
        Account accounts[1000]; //�̦h�i�s��1000�ӱb��
        int accountCount;       //�������X�ӱb��s�b
        int user;               //-1�N���n�J�A0-999�N��n�J���b����index
        int year;
        int month;
        vector<info> infos;     //�������
};

#endif // Bank_H
