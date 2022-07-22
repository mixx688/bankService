#ifndef DEPOSIT_H
#define DEPOSIT_H

class Deposit
{
    public:
        Deposit(int a,int t,double r);
        ~Deposit();
        void print();
        void printShort();
        void incrementTerm();
        bool checkExpire();
        int expireAmount();
        int cancelAmount(double r);
        int getTerm();

    private:
        int amount;
        double rate;
        int term;// ´Á§O
        int currentTerm;
};

#endif // DEPOSIT_H
