#include<string>
#include<iostream>
int main(void) {
    std::string str1 = "hello";
    std::string str2 = "world";
    std::string str3;
    int len;
    std::cout<<"str1="<<str1
        <<" str2="<<str2
        <<" str3="<<str3<<std::endl;

    str3=str1;
    std::cout<<"str1="<<str1
        <<" str2="<<str2
        <<" str3="<<str3<<std::endl;
    
    std::cout<<"str3 == str1 "<<(str3 == str1)<<'\n';

    str3=str1+str2;
    std::cout<<"str1="<<str1
        <<" str2="<<str2
        <<" str3="<<str3<<std::endl;
    std::cout<<"str3 == str1 "<<(str3 == str1)<<'\n';
    len = str3.size();
    std::cout<<"str3 len="<<len<<std::endl;
    return 0;
}
