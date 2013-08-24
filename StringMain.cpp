#include"String.h"
#include<cassert>
#include<string>


int main()
{
  
	
	//copy constrtor 
	String s1("abc");
	cout<<s1<<endl;

	String s2(s1);
	cout<<s2<<endl;

	// operator=(const char* s);
	s1="helloworld";
	cout<<s1<<endl;
    // operator=(const String & other);
	String s3("youcan");
	s1=s3;
	cout<<s1<<endl;
    
	//调用赋值构造函数
	String s4="dddd";
	cout<<s4<<endl;
	cout<<s1.howMany()<<endl;//输出4

	String s5="helloworld";
	cout<<s5[0]<<endl;
	s5[0]='z';
	cout<<s5<<endl;
	const String s6("const");
	cout<<s6[0]<<endl;
  
}