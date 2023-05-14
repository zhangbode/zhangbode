#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<fstream>

using namespace std;

class Goods
{
private:
    char name[20];//商品名称
    int num;//商品代码
    char person[20];//产地
    double price;//进货价
    int amount;//库存量
    

public:
    Goods *next;
    Goods();
    Goods(int num, char *name, char *person, double price, int amount);
    void Output();
    friend class Supermarket;
};
//构造函数传递内容
Goods::Goods(int num,char *name,char *person,double price,int amount)
{
    this->num = num;
    strcpy_s(this->name, name);
    strcpy_s(this->person, person);
    this->price = price;
    this->amount = amount;
}
void Goods::Output()
{
    cout << "num\t"
         << "name\t\t\t"
         << "person\t\t\t"
         << "price\t\t"
         << "amount" << endl;
    cout << num << "\t" 
         << name << "\t\t\t" 
         << person << "\t\t\t" 
         << price << "\t\t" 
         << amount << endl;
}

class Supermarket
{
private:
    Goods *List;

public:
    Supermarket();
    ~Supermarket();
    void Add();//增加商品
    void Delete();//删除商品
    void Modify();//修改商品
    void Query();//查找商品
    void Save();//保存到文件
    void Load();//从文件中读取
    void Print();//展示所有商品
};

Supermarket::Supermarket()
{
    List = NULL;
}

Supermarket::~Supermarket()
{
    Goods *L;
    L = List;
    while (L)
    {
        L = L->next;
        delete List;
        List = L;
    }
    List = NULL;
}
void Supermarket::Add()//添加商品
{
    Goods *p;
    int num, amount;
    char name[20], person[30];
    double price;
    cout << "\n请输入新增商品（图书）信息：\n";
    cout << "商品（图书）代码:"; cin >> num;
    cout << "商品（图书）名称:"; cin >> name;
    cout << "商品（图书）产地（出版社）:"; cin >> person;
    cout << "商品（图书）单价:"; cin >> price;
    cout << "该商品（图书）库存量:"; cin >> amount;//创建新商品类结点
    p = new Goods(num, name, person, price, amount);
    p->next = NULL;
    if (List==NULL)
    {
        List = p;
    }
    else
    {
        Goods *p2 = List;
        while (p2->next)
            p2 = p2->next;
        p2->next = p;
    }
    cout << "商品添加成功！" << endl;
    system("pause");
}
void Supermarket::Delete()//从商品列表中删除商品
{
    char name[20];
    cout << "\n请输入要删除的商品（图书）名称：\n";
    cin >> name;//查找要删除的结点
    Goods *p1, *p2 = NULL;
    p1 = List;
    while (p1)
    {
        if(strcmp(p1->name,name)==0)
            break;
        else
        {
            p2 = p1;
            p1 = p1->next;
        }
    }
    //删除结点
    if(p1!=NULL)//若找到结点，则删除
    {
        if(p1==List)//若找到的结点是第一个结点
        {
            List = p1->next;
            delete p1;
        }
        else//若要删除结点是后续结点
        {
            p2->next = p1->next;
            delete p1;
        }
        cout << "找到并删除" << endl;
    }
    else
        cout << "sorry,未找到商品（图书）：" << name << endl;
}
void Supermarket::Modify()//修改商品信息
{
    int num, amount;
    char name[20], person[30];
    double price;
    cout << "\n修改商品（图书）\n请输入要修改的商品（图书）名称：";
    cin >> name;
    Goods *p1, *p2 = NULL;
    p1 = List;
    while(p1) {
        if(strcmp(p1->name,name)==0)
            break;
        else {
            p2 = p1;
            p1 = p1->next;
        }
    }//修改结点
    if (p1!=NULL)
    {
        p1->Output();
        cout<<"\n请选择要修改的信息\n1—商品（图书）代码\n2—商品（图书）名称\n3—产地（出版社）\n4—单价\n5—该商品（图书）库存量\n6—修改全部信息\n";
        cout << "请输入指令：";
        int a;
        cin >> a;
        switch (a)
        {
        case 1:
            cout << "请输入新代码：";
            cin >> num;
            strcpy(name, p1->name);
            strcpy(person, p1->person);
            price = p1->price;
            amount = p1->amount;
            break;
        case 2:
            cout << "请输入新名称：";
            num = p1->num;
            cin >> name;
            strcpy(person, p1->person);
            price = p1->price;
            amount = p1->amount;
            break;
        case 3:
            cout << "请输入新产地（出版社）：";
            num = p1->num;
            strcpy(name, p1->name);
            cin >> person;
            price = p1->price;
            amount = p1->amount;
            break;
        case 4:
            cout << "请输入新单价：";
            num = p1->num;
            strcpy(name, p1->name);
            strcpy(person, p1->person);
            cin >> price;
            amount = p1->amount;
            break;
        case 5:
            cout << "请输入新库存数据：";
            num = p1->num;
            strcpy(name, p1->name);
            strcpy(person, p1->person);
            price = p1->price;
            cin >> amount;
            break;
        case 6:
            cout << "请输入新信息：" << endl;
            cout << "商品（图书）代码：";
            cin >> num;
            cout << "商品（图书）名称：";
            cin >> name;
            cout << "商品产地（出版社）：";
            cin >> person;
            cout << "商品（图书）单价：";
            cin >> price;
            cout << "该商品库存量：";
            cin >> amount;
            break;
        default:
            break;
        }
        Goods *p3;
        p3 = new Goods(num, name, person, price, amount);
        p3->next = p1->next;
        if(p1==List){//若要替换的结点是第一个结点
            List = p3;
        }
        else//若要替换的结点时后续结点
            p2->next = p3;
        delete p1;
        cout << "修改成功！" << endl;
    }
    else
        cout << "Sorry,未找到商品（图书）！" << endl;
}
void Supermarket::Query()//查找商品
{
    cout << "\n* * * * 查找商品（图书） * * * *" << endl;
    char name[20];
    cout << "\n请输入要查找的商品（图书）名称：";
    cin >> name;
    Goods *p1 = List;
    while (p1) {
        if (strcmp(p1->name, name)==0) {
            break;
        }
        else
            p1 = p1->next;
    }
    if(p1!=NULL) {
        cout << "该商品（图书）相关信息如下：" << endl;
        cout << "该商品（图书）代码：\t" << p1->num << "\t"
             << "该商品名称：\t" << p1->name << "\t" << endl;
        cout << "该商品（图书）产地（出版社）：\t" << p1->person << "\t"
             << "该类商品（图书）单价：\t" << p1->price << "\t" << endl;
        cout << "该类商品（图书）库存量：\t" << p1->amount << "\t";
    }
    else
        cout << "Sorry,未找到该商品（图书）！" << endl;
    system("pause");
}
void Supermarket::Save()//保存到文件
{
    cout << "是否保存？[Y/N]";
    char a;
    cin >> a;
    if(a=='n' || a=='N')
        return;
    if(a=='y' || a=='Y') {
        ofstream outfile;
        outfile.open("base.txt", ios::trunc);
        outfile.close();
        outfile.open("base.txt", ios::out | ios::app);
        if (!outfile) { 
            cerr << "open error!"; exit(1); 
        }
        Goods* p = List;
        while (p) {
            outfile << p->num << "\t" << p->name << "\t" << p->person << "\t" << p->price << "\t" << p->amount << endl;
            cout << endl;
            p = p->next;  
        }
        outfile.close();
        cout << "已完成数据保存" << endl;
        system("pause");
    }
}
void Supermarket::Load()//从文件中读取
{
    Goods *p = List,*q = NULL;
    char a[1] = {'a'};
    ifstream infile("base.txt", ios::in );
    if(!infile) {
        cout << "商品数据装入失败，文件读取程序已退出" << endl;
    }
    else {
        p =new Goods(1, a, a, 1, 1);
        infile >> p->num >> p->name >> p->person >> p->price >> p->amount;
		p->next = NULL;
		q = p;
        while(infile) {
            q = new Goods(p->num, p->name, p->person, p->price, p->amount);
            q->next = NULL;
            if(List) {
                q->next = List;
                List = q;
            }
            else
            {
                List = q;
            }
            infile >> p->num >> p->name >> p->person >> p->price >> p->amount;

        }
        cout << "\n商品数据已经壮装入" << endl;
    }
    infile.close();
    system("pause");
}
void Supermarket::Print()
{
    Goods *p = List;
    if(p!=NULL)
        cout << "num\t"
             << "name\t\t\t"
             << "person\t\t\t"
             << "price\t\t"
             << "amount" << endl;
    else {
        cout << "Sorry,目录为空！" << endl;
    }
    while(p) {
        cout << p->num << "\t" 
             << p->name << "\t\t\t" 
             << p->person << "\t\t\t" 
             << p->price << "\t\t" 
             << p->amount << endl;
        p = p->next;
    }
    system("pause");
}
int main()
{
    int n;
    Supermarket L;
    cout << "注意：" << endl;
    cout << "1.请严格按照提示操作，否则进入死循环重新打开后数据会丢失；" << endl;
    cout << "2.商品代码及库存只能输入整数；" << endl;
    cout << "3.商品名称及产地不得超过20个字节，超过部分会丢失；" << endl;
    cout << "4.系统退出时会清除文件及系统保存数据，退出时请注意" << endl;
    cout << "5.本提示只出现一次！！！" << endl;
    system("pause");
    do{
        system("cls");
        cout << "\n****计算机、外围设备、办公用品、生活用品、图书管理系统****\n";
        cout << " 0—展示商品/图书\n";
        cout << " 1—增加商品/图书\n";
        cout << " 2—删除商品/图书\n";
        cout << " 3—修改商品/图书\n";
        cout << " 4—查询商品/图书\n";
        cout << " 5—读取文件中保存信息\n";
        cout << " 6—退出 \n 请选择（0—6）:";
        cin >> n;
        switch (n)
        {
        case 0:
            L.Print();
            break;
        case 1:
            L.Add();
            L.Save();
            break;
        case 2:
            L.Delete();
            L.Save();
            break;
        case 3:
            L.Modify();
            L.Save();
            break;
        case 4:
            L.Query();
            break;
        case 5:
            L.Load();
            break;
        default:
            if(n!=6)
            {
                cout << "指令错误已重置！" << endl;
                system("pause");
            }
            break;
        }
    } while (n!=6);
    ofstream outfile;
    char x;
    cout << "系统将要退出，是否保留文件数据[Y/N]" << endl;
    cout << "请输入指令：";
    cin >> x;
    if(x=='n' || x=='N')
    {
        outfile.open("base.txt", ios::trunc);
        outfile.close();
    }
    system("pause");
    return 0;
}