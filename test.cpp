#include<iostream>
#include <openssl/sha.h>
#include <time.h>
#include <stdio.h>
using namespace std;
string sha256(const string str)
{
	char buf[2];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    std::string NewString = "";
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(buf,"%02x",hash[i]);
        NewString = NewString + buf;
    }
	return NewString;
}
time_t gettime()
{
    time_t myt=time(NULL);
    cout<<"sizeof(time_t) is: "<<(long int)(myt)<<endl;
    return myt;
}
string apentboxstr(string no,string time,string lastHash,string miracle)
{
	string str="";
	str=no+time+lastHash+miracle;
	return sha256(str);
}
int main()
{
	string no="1";
	string time="1609399589";
	string lastHash="0";
	string miracle="12";
	string str="";
	str=apentboxstr(no,time,lastHash,miracle);	
	cout<<"str="<<str<<endl;	
	return 0;
}
