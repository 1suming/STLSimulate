#ifndef  String_h
#define  String_h

#include<iostream>
using namespace std;
class String
{
private:
	char *str;
	int len;
	static int numStrings;
	 
 
public:

	String();
	String(const char *s);
	String(const String  s);

	String&  operator=(const char* s);
	String & operator=(const String & other);

	char & operator[](int i);
	const char &  operator[](int i) const;

	~String();
	int length() const {return len;}
	friend bool operator<(const String &s1,const String &s2);
	friend bool operator>(const String &s1,const String &s2);
	friend bool operator==(const String &s1,const String &s2);
	
	friend istream& operator>>(istream& is,String &s);
	friend ostream& operator<<(ostream& is,const String &s);

	static int howMany(){ return numStrings;}
};

#endif