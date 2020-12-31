#include<iostream>
#include <openssl/sha.h>
#include <time.h>
#include <stdio.h>
using namespace std;

#define Box_Max 10
#define Num_Max 2147483647
//hash256函数封装
string sha256(const string hashstr)
{
    //这个函数为C++ Hash256自带的示例函数，不作为修改
    char Hashbuf[2];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, hashstr.c_str(), hashstr.size());
    SHA256_Final(hash, &sha256);
    std::string MyBoxHashString = "";
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(Hashbuf,"%02x",hash[i]);
        MyBoxHashString = MyBoxHashString + Hashbuf;
    }
    return MyBoxHashString;
}

//获取当前时间
string gettime()
{
    string stime="";//string类型的time，前缀模式s开头
    char temstr[1000];//临时转换的变量，C的int和string互转的函数部分版本不兼容，故采用标准的流打印，后面相同
    time_t ltime=time(NULL);//long类型的time，前缀模式l开头
    //cout<<"sizeof(time_t) is: "<<(long int)(ltime)<<endl;
    sprintf(temstr,"%d",(long int)(ltime));
    stime=temstr;
    return stime;
}
//根据箱子编号、时间、上一个箱子的hash、神奇数字生成自己的hash
string apentboxstr(string sNum,string sTime,string sHash,string sMiracle)
{
    string Temstr="";//临时转换的变量
    Temstr=sNum+sTime+sHash+sMiracle;
    return sha256(Temstr);
}
//检查当前是否hash值是否满足条件，校验前5位是否是0
int check(string Hashstr)
{
    string checkflag="00000000";//校验前5位是否是0，多定义3位
    //cout<<"Hashstr="<<Hashstr<<endl;
    return Hashstr.compare(0,5,checkflag,0,5);    
}
int main()
{
    int i=0;
    char temstr[1000];//临时转换的变量
    //10个箱子的集合,从1开始到10,0作为第0个箱子
    string box_num_strs[11];
    string times[11];
    string lastHashs[11]="0";
    string miracles[11]="12";
    //单个箱子的字段
    string box_num_str="1";
    string time="1609399589";
    string lastHash="0";
    string miracle="12";
    string str="";
    //str=apentboxstr(box_num,time,lastHash,miracle);    
    //cout<<"str="<<str<<endl;
    for(int box_num=1;box_num<=Box_Max;box_num++)
    {
        time=gettime();
        sprintf(temstr,"%d",box_num);
        box_num_str=temstr;
        box_num_strs[box_num]=box_num_str;
        times[box_num]=time;
        for(i=0;i<Num_Max;i++)
        {
            
            sprintf(temstr,"%d",i);
            miracle=temstr;
            str=apentboxstr(box_num_strs[box_num],times[box_num],lastHashs[box_num],miracle);
            if(check(str)==0)
            {
                //cout<<"str="<<str<<endl;
                //cout<<"miracle="<<miracle<<endl;
                lastHashs[box_num]=str;
                miracles[box_num]=miracle;
                break;
            }
            
        }
        if(i!=Num_Max)//如果=Num_Max，说明这次没找到（在int的范围内没找到）
        {
            cout<<" box num="<<box_num<<" open time="<<times[box_num]<<" Hash="<<lastHashs[box_num]<<endl;
            cout<<" miracles="<<miracles[box_num]<<endl<<endl;    
        }        
    }
    
    return 0;
}
