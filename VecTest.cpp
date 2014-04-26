#include<iostream>
#include"vec.cpp"

int main()
{
	Vec<int> v; //no argument construtor
	v.push_back(1);
	cout<<v[0]<<endl;

	Vec<int> v2(5,2); //Vec(size_t n,const T& val=T())
	for(int i=0;i<v2.size();i++)
		cout<<v2[i]<<ends;
	cout<<endl;

	Vec<int> v3(v2); //copy constructor
	for(int i=0;i<v3.size();i++)
		cout<<v3[i]<<ends;
	cout<<endl;

	Vec<int> v4; 
	v4=v3;
	for(Vec<int>::const_iterator it=v4.begin();it!=v4.end();it++)
	{
		cout<<*it<<ends;
	}
	cout<<endl;

	//erase
	v4.erase(v4.begin(),v4.begin()+2);
	v4[0]=3;
	for(Vec<int>::const_iterator it=v4.begin();it!=v4.end();it++)
	{
		cout<<*it<<ends;
	}
	cout<<endl;

}
