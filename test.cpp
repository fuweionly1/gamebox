#include<iostream>
#include <openssl/sha.h>
#include <time.h>
#include <stdio.h>
using namespace std;
//hash256函数封装
string sha256(const string hashstr)
{
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
	string strtime="";
	char temstr[1000];//临时转换的变量
    time_t myt=time(NULL);
    //cout<<"sizeof(time_t) is: "<<(long int)(myt)<<endl;
	sprintf(temstr,"%d",(long int)(myt));
	strtime=temstr;
    return strtime;
}
//根据箱子编号、时间、上一个箱子的hash、神奇数字生成自己的hash
string apentboxstr(string no,string time,string lastHash,string miracle)
{
	string str="";
	str=no+time+lastHash+miracle;
	return sha256(str);
}
//检查当前是否hash值是否满足条件
int check(string Hashstr)
{
	string checkflag="00000000";
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
	for(int box_num=1;box_num<11;box_num++)
	{
		time=gettime();
		sprintf(temstr,"%d",box_num);
		box_num_str=temstr;
		box_num_strs[box_num]=box_num_str;
		times[box_num]=time;
		for(i=0;i<654321;i++)
		{
			
			sprintf(temstr,"%d",i);
			miracle=temstr;
			str=apentboxstr(box_num_strs[box_num],times[box_num],lastHashs[box_num],miracle);
			if(check(str)==0)
			{
				cout<<"str="<<str<<endl;
				cout<<"miracle="<<miracle<<endl;
				lastHashs[box_num]=str;
				miracles[box_num]=miracle;
				break;
			}
			
        }
		cout<<" box num="<<box_num<<" open time="<<times[box_num]<<" lastHash="<<lastHashs[box_num]<<endl;
		cout<<" miracles="<<miracles[box_num]<<endl<<endl;			
	}
	
	return 0;
}
