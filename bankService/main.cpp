#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<sstream>
#include"Bank.h"
using namespace std;

const string OPTION_MENU[]={"帳號登入","註冊新帳號","查看利率","調整利率","查看交易紀錄","時光機"};
const string OPTION_ACC[]={"活期存款","活期提款","查看利率","新增定存存單","查看定存存單","定存解約","時光機","登出"};
const int MONTH_OPTION[]={1,3,6,9,12,24,36};

int choice=0,c;
string s;
Bank myBank;
//compiler->other compiler option->"-fexec-charset=BIG-5"
//editor->encoding settings->use encoding...->UTF8
void displayOption(int i)
{
    if(choice==i)cout<<"●";
        else cout<<"  ";
}
void displayMenu()
{
    system("cls");
    cout << "歡迎來到銀行模擬系統！\n";
    cout << "現在是西元"<<myBank.getYear()<<"年"<<myBank.getMonth()<<"月\n";
    cout << "在任何地方輸入\"back\"可返回\n\n";
    for(int i=0; i<6; i++)
    {
        displayOption(i);
        cout<<OPTION_MENU[i]<<endl;
    }
}
void displayAccount(int u)
{
    system("cls");
    myBank.accessAccount(u)->print();
    cout << "現在是西元"<<myBank.getYear()<<"年"<<myBank.getMonth()<<"月\n\n";
    for(int i=0; i<8; i++)
    {
        displayOption(i);
        cout<<OPTION_ACC[i]<<endl;
    }
}
int stoi(string s)
{
    for(int i=0;i<s.length();i++)if(s[i]<'0'||s[i]>'9')return -1;
    stringstream ss;
    int i;
    ss<<s;
    ss>>i;
    return i;
}
double stod(string s)
{
    int dc=0;
    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='.')dc++;
        else if(s[i]<'0'||s[i]>'9')return -1;
        if(dc>1)return -1;
    }
    stringstream ss;
    double d;
    ss<<s;
    ss>>d;
    return d;
}
void errorMessage(string s)
{
    cout<<s;
    system("pause");
    system("cls");
}
void ignore()
{
    cin.ignore(48763,'\n');
}
void controlMenu(int optionCount)
{
    c=getch();
    switch(c)
    {
    case 72:choice--;break;
    case 80:choice++;break;
    }
    if(choice<0)choice=0;
    if(choice>optionCount-1)choice=optionCount-1;
}
int main()
{
    displayMenu();
    while(c=getch())
    {
        if(myBank.getUser()<0)
        {
            if(c==224)
            {
                controlMenu(6);
                displayMenu();
            }
            else if(c==13)
            {
                system("cls");
                switch(choice)
                {
                case 0:{
                    bool flag=1;
                    while(flag)
                    {
                        string n,p;
                        cout<<"請輸入帳號: ";
                        cin>>n;ignore();
                        if(n=="back"){choice=0;displayMenu();break;}
                        cout<<"請輸入密碼: ";
                        cin>>p;ignore();
                        if(p=="back"){choice=0;displayMenu();break;}
                        int u = myBank.loginCheck(n,p);
                        if(u<0)errorMessage("帳號或密碼錯誤！\n請重新輸入\n");
                        else
                        {
                            myBank.changeUser(u);
                            cout<<"登入成功！\n";
                            system("pause");
                            flag=0;
                            choice=0;
                            displayAccount(myBank.getUser());
                        }
                    }}
                    break;
                case 1:{
                    bool flag=1;
                    string n,p;
                    int a;
                    while(flag)
                    {
                        cout<<"請輸入帳號: ";
                        cin>>n;ignore();
                        if(myBank.checkDuplicate(n)){errorMessage("帳號已存在！\n請重新輸入\n");continue;}
                        if(n.length()>12){errorMessage("帳號最多只能有12個字元！\n請重新輸入\n");continue;}
                        flag=0;
                    }
                    if(n=="back"){choice=0;displayMenu();break;}
                    flag=1;
                    while(flag)
                    {
                        cout<<"請輸入密碼: ";
                        cin>>p;ignore();
                        if(p=="back")break;
                        if(p.length()<6){errorMessage("密碼至少要有6個字元！\n請重新輸入\n");continue;}
                        flag=0;
                    }
                    if(p=="back"){choice=0;displayMenu();break;}
                    flag=1;
                    while(flag)
                    {
                        cout<<"請輸入存入金額: ";
                        cin>>s;ignore();
                        if(s=="back")break;
                        a=stoi(s);
                        if(a==-1){errorMessage("輸入錯誤！\n請重新輸入\n");continue;}
                        if(a<1000){errorMessage("至少要存入1000元！\n請重新輸入\n");continue;}
                        flag=0;
                    }
                        if(s=="back"){choice=0;displayMenu();break;}
                        myBank.addAccount(n,p,a,myBank);
                        cout<<"註冊成功！\n";
                        system("pause");
                        myBank.generateInfo(n,a,a,myBank.getYear(),myBank.getMonth());
                        flag=0;
                        choice=0;
                        displayMenu();
                    }
                    break;
                case 2:{
                    myBank.showRate();
                    system("pause");
                    choice=0;
                    displayMenu();
                }
                break;
                case 3:{
                    double r;
                    bool flag=1;
                    choice=0;
                    cout<<"請選擇:\n\n";
                    displayOption(0);
                    cout<<"活存\n";
                    for(int i=0;i<7;i++)
                    {
                        displayOption(i+1);
                        cout<<"定存"<<MONTH_OPTION[i]<<"個月\n";
                    }
                    displayOption(8);
                    cout<<"返回\n";
                    while(c=getch())
                    {
                        if(c==224)
                        {
                            controlMenu(9);
                            system("cls");
                            cout<<"請選擇:\n\n";
                            displayOption(0);
                            cout<<"活存\n";
                            for(int i=0;i<7;i++)
                            {
                                displayOption(i+1);
                                cout<<"定存"<<MONTH_OPTION[i]<<"個月\n";
                            }
                            displayOption(8);
                            cout<<"返回\n";
                        }
                        else if(c==13){system("cls");break;}
                    }
                    if(choice==8){choice=0;displayMenu();break;}
                    while(flag)
                    {
                        cout<<"請輸入新的利率(%): ";
                        cin>>s;ignore();
                        if(s=="back")break;
                        r=stod(s);
                        if(r<=0||r>100){errorMessage("輸入錯誤！\n請重新輸入\n");continue;}
                        flag=0;
                    }
                    if(s=="back"){choice=0;displayMenu();break;}
                    if(choice==0)myBank.adjustRate(r);
                    else myBank.adjustRateCD(choice-1,r);
                    cout << "調整成功！\n";
                    system("pause");
                    choice=0;
                    displayMenu();
                }
                break;
                case 4:{
                    myBank.showInfo();
                    system("pause");
                    choice=0;
                    displayMenu();
                }
                break;
                case 5:{
                    myBank.nextMonth();
                    cout << "已到達下一個月！\n";
                    system("pause");
                    choice=0;
                    displayMenu();
                }
                break;
                }
            }
        }
        else
        {
            if(c==224)
            {
                controlMenu(8);
                displayAccount(myBank.getUser());
            }
            else if(c==13)
            {
                system("cls");
                int u=myBank.getUser();
                switch(choice)
                {
                    case 0:{
                    int a;
                    bool flag=1;
                    while(flag)
                    {
                        cout<<"請輸入存款金額: ";
                        cin>>s;ignore();
                        if(s=="back")break;
                        a=stoi(s);
                        if(a==-1){errorMessage("輸入錯誤！\n請重新輸入\n");continue;}
                        if(a<100){errorMessage("至少要存入100元！\n請重新輸入\n");continue;}
                        flag=0;
                    }
                    if(s=="back"){choice=0;displayAccount(u);break;}
                    myBank.accessAccount(u)->depositing(a);
                    myBank.generateInfo(myBank.accessAccount(u)->getAccount(),a,myBank.accessAccount(u)->getBalance(),myBank.getYear(),myBank.getMonth());
                    cout<< "存款成功！\n";
                    system("pause");
                    choice=0;
                    displayAccount(u);
                    }
                    break;
                    case 1:{
                    int a;
                    bool flag=1;
                    while(flag)
                    {
                        cout<<"請輸入提款金額: ";
                        cin>>s;ignore();
                        if(s=="back")break;
                        a=stoi(s);
                        if(a==-1){errorMessage("輸入錯誤！\n請重新輸入\n");continue;}
                        if(a>myBank.accessAccount(u)->getBalance()){errorMessage("餘額不足！\n請重新輸入\n");continue;}
                        if(a<100){errorMessage("至少要提出100元！\n請重新輸入\n");continue;}
                        flag=0;
                    }
                    if(s=="back"){choice=0;displayAccount(u);break;}
                    myBank.accessAccount(u)->withdraw(a);
                    myBank.generateInfo(myBank.accessAccount(u)->getAccount(),-a,myBank.accessAccount(u)->getBalance(),myBank.getYear(),myBank.getMonth());
                    cout<< "提款成功！\n";
                    system("pause");
                    choice=0;
                    displayAccount(u);
                    }
                    break;
                    case 2:{
                    myBank.showRate();
                    system("pause");
                    choice=0;
                    displayAccount(u);
                    }
                    break;
                    case 3:{
                    bool flag=1;
                    int a;
                    choice=0;
                    cout<<"請選擇期數:\n\n";
                    for(int i=0;i<7;i++){
                        displayOption(i);
                        cout<<MONTH_OPTION[i]<<"個月\n";
                    }
                    displayOption(7);
                    cout<<"返回\n";
                    while(c=getch())
                    {
                        if(c==224){
                            controlMenu(8);
                            system("cls");
                            cout<<"請選擇期數:\n\n";
                            for(int i=0;i<7;i++){
                                displayOption(i);
                                cout<<MONTH_OPTION[i]<<"個月\n";
                            }
                            displayOption(7);
                            cout<<"返回\n";
                        }
                        else if(c==13){system("cls");break;}
                    }
                    if(choice==7){choice=0;displayAccount(u);break;}
                    while(flag)
                    {
                        cout<<"請輸入定存金額: ";
                        cin>>s;ignore();
                        if(s=="back")break;
                        a=stoi(s);
                        if(a==-1){errorMessage("輸入錯誤！\n請重新輸入\n");continue;}
                        if(a<10000){errorMessage("至少要存入10000元！\n請重新輸入\n");continue;}
                        flag=0;
                    }
                    if(s=="back"){choice=0;displayAccount(u);break;}
                    myBank.accessAccount(u)->addDeposit(a,choice);
                    cout<< "定存成功！\n";
                    system("pause");
                    choice=0;
                    displayAccount(u);
                    }
                    break;
                    case 4:{
                        int c=myBank.accessAccount(u)->accessVector().size();
                        int j=0;
                        for(int i=0; i<c; i++)
                        {
                            if(myBank.accessAccount(u)->accessVector().at(i)!=NULL)
                                {
                                    j++;
                                    cout<<"存單"<<j<<": \n";
                                    myBank.accessAccount(u)->accessDeposit(i)->print();
                                }
                        }
                        if(j==0)cout<<"目前無存單！\n";
                        system("pause");
                        choice=0;
                        displayAccount(u);
                    }
                    break;
                    case 5:{
                        choice=0;
                        int s=myBank.accessAccount(u)->accessVector().size();
                        if(s==0){cout<<"目前無存單！\n";system("pause");}
                        else
                        {
                            cout << "請選擇存單:\n\n";
                            for(int i=0; i<s ;i++)
                            {
                                displayOption(i);
                                myBank.accessAccount(u)->accessDeposit(i)->printShort();
                            }
                            displayOption(s);
                            cout<<"返回\n";
                            while(c=getch())
                            {
                                if(c==224)
                                {
                                    controlMenu(s+1);
                                    system("cls");
                                    cout << "請選擇存單:\n\n";
                                    for(int i=0; i<s ;i++)
                                    {
                                        displayOption(i);
                                        myBank.accessAccount(u)->accessDeposit(i)->printShort();
                                    }
                                    displayOption(s);
                                    cout<<"返回\n";
                                }
                                else if(c==13)
                                {
                                    if(choice==s)break;
                                    system("cls");
                                    myBank.accessAccount(u)->cancelCD(choice);
                                    system("pause");
                                    break;
                                }
                            }
                        }
                        choice=0;
                        displayAccount(u);
                    }
                    break;
                    case 6:{
                    myBank.nextMonth();
                    cout << "已到達下一個月！\n";
                    system("pause");
                    choice=0;
                    displayAccount(u);
                    }
                    break;
                    case 7:{
                    myBank.changeUser(-1);
                    cout <<"登出成功！\n";
                    system("pause");
                    choice=0;
                    displayMenu();
                    }
                    break;
                }
            }
        }
    }
}
