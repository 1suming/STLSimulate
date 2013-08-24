#include<cstring>
#include"String.h"

int String::numStrings=0;
 
String::String()
{ 
	
	len=0;
	str=new char[1]; 
	str[0]='\0';  //为什么是new char【1】，不是new char与析构函数兼容

	numStrings++;
	//cout <<numStrings<<":"<<str<<"		object created"<<endl;

}
String::String(const char *s)
{
	len=strlen(s);
	str=new char[len+1];
	strcpy(str,s);

	numStrings++;
	//cout<<numStrings<<":"<<str<<"	object created"<<endl;
}

String::String(const String& s)
{
	
	len=s.len;
	str=new char[len+1];
	strcpy(str,s.str);

	numStrings++;
	//cout<<numStrings<<":"<<str<<"	object created"<<endl;
}


String&  String::operator=(const char* s)
{
	delete[] str;
	len=strlen(s);
	str=new char[len+1];
	strcpy(str,s);

	return *this;
}

String & String::operator=(const String &other)
{
	/*
	if(this==&other)
		return *this;
	delete[] this->str;//free old string
	char *tmp=new char[strlen(other.m_data)+1];
	strcpy(m_data,other.m_data);
	return *this;
	*/
	if(this==&other)
		return *this;
	delete [] str;//free old string
	len=other.len;
	str=new char[len+1];
	strcpy(str,other.str);
	

	return *this;
}

char& String::operator[](int i)
{
	return str[i];
}
//read-only char access for const string
const char & String::operator[](int i) const
{
	return str[i];
}

istream& operator>>(istream& is, String &s)
{
	char tmp[80];
	is.get(tmp,80);
	if(is) //如果读取失败is为false
		s=tmp;
	while(is && is.get()!='\n') //丢弃多余的字符 cin.get()读取一个char
		continue;
	return is;
}

ostream& operator<<(ostream& os,const String &s)
{
	os<<s.str;
	return os;
}
String::~String()
{
	--numStrings;
	delete[] str;
}
bool operator<(const String &s1,const String &s2)
{
	return strcmp(s1.str,s2.str)<0?true:false;
}

bool operator>(const String &s1,const String &s2)
{
	//return strcmp(s1.str,s2.str)>0?true:false; 或
	return s2<s1;
}

bool operator==(const String &s1,const String &s2)
{
	return strcmp(s1.str,s2.str)==0 ?true:false;

}