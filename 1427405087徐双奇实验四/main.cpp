#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<string>
#include<vector>
#include<regex>
using namespace std;
class user
{
private:
    string name;//用户名
    string address;//用户文件目录地址
    int count;//用户拥有的文件数目 文件数目最多为一个
public:
    user(string n,string a,int c)
    {
        name=n;
        address=a;
        count=c;
    }
    user()
    {
        name="unnamed";
        address="none";
        count=0;
    }
    string getName()
    {
        return name;
    }
    string getAddress()
    {
        return address;
    }
    int  getCount()
    {
        return count;
    }
    void setName(const string n)
    {
        name=n;
    }
    void setAddress(const string a)
    {
        address=a;
    }
    void setCount(const  int c)
    {
        count=c;
    }
};


class file
{
private:
    string name;
    bool stat;//文件状态
    user* usr;//用户指针
public:
    file()
    {
        name="unnamed";
        stat=0;
        usr=NULL;   
    }
    
};
bool run=1;
user currentUser;
vector<user> root;
void command(const string input);        
int main()
{
    cout<<"##################"<<endl;
    cout<<"###文件管理系统###"<<endl;
    cout<<"##################"<<endl;
    cout<<"请输入用户数：";
    string input;
    getline(cin,input);//to be done ,这里有个bug，输入“1  ddd”也可以
    int read=0;
    try
    {   
        read=stoi(input);//用户输入字符串input转为int类型      c++11
    }
    catch(invalid_argument)
    {
        cerr<<"输入包含非法字符!"<<endl;
        exit(1);
    }
    catch(out_of_range)
    {
        cerr<<"用户数过多!"<<endl;
        exit(1);
    }

   
       if(read<0)
    {
        cout<<"用户数小于0!"<<endl;
        exit(1);
    }
    if(read==0)
    {
        cout<<"用户数等于0!"<<endl;
        exit(1);
    }
    
    for(int i=1;i<=read;i++)
    {
        char num=i+'0';
        string str="0";
        str[0]=num;
        string name="usr"+str;
        user temp(name,"/home",0);
        root.push_back(temp);
    }
    cout<<"已创建"<<read<<"个用户"<<endl;
    vector<user>::iterator it;
    for(it=root.begin();it!=root.end();it++)
    {
        cout<<"用户名："<<(*it).getName()<<"\t";
        cout<<"用户目录地址："<<(*it).getAddress()<<"\t";
        cout<<"用户文件数目"<<(*it).getCount()<<endl;
    }
    //初始化用户
    bool rightUserName=0;
    while(!rightUserName)
    {
        rightUserName=1;//用户名正确
        cout<<"请输入用户名:"<<endl;
        getline(cin,input);
        
        for(it=root.begin();it!=root.end();it++)
        {
            if(input!=(*it).getName())
            {
                if((it+1)==root.end())
                {
                    cout<<"无此用户!"<<endl;
                    rightUserName=0;
                }
            }
            else
            {
                currentUser=*it;//当前用户设定
                break;
            }
        }

    }
    //程序循环
   
    while(run)
    {
        cout<<"#"<<currentUser.getName()<<":命令:"<<endl;
        string input;
        getline(cin,input);
        command(input);
    }
        
        
        
    return 0;
}
void command(const  string input)
{
    //退出
    if(input=="q")
    {
        cout<<"#"<<currentUser.getName()<<":已退出"<<endl;
        run=0;
    }
    else if(regex_match(input,regex("(cu)(\\s+)(\\w+)(\\s*)")))//更改用户,change user
    {
        for(vector<user>::iterator it=root.begin();it!=root.end();it++)
        {
            string str="(cu)(\\s+)";//正则表达式一部分
            str=str+(*it).getName()+"(\\s*)";//完整的正则表达式
            if(regex_match(input,regex(str)))
            {
                if(currentUser.getName()==(*it).getName())
                {
                    cout<<"#"<<currentUser.getName()<<":已经是该用户，不必再切换!"<<endl;
                    return;
                }
                currentUser=*it;
                cout<<"#"<<currentUser.getName()<<":已切换用户"<<endl;
                return;
            }
        }
        
        cout<<"#"<<currentUser.getName()<<":没有该用户"<<endl;
    }
    else
    {
        // system(input.c_str());
        cout<<"#"<<currentUser.getName()<<":非法命令:"<<input<<endl;
    }
}
