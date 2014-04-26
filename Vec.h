#ifndef _VEC_H
#define _VEC_H

#include<memory>

using namespace std;
/*
我们的内存管理工作都用allocator类实现，为什么不用new和delete？
因为new会完成相当多的工作，他不仅会分配内存空间，还会把这些内存初始化。当使用new来为T类型的数组分配空间时，
他需要使用T的默认构造函数。这种方式使得我们不能为用户提供更多的灵活性。

使用new也可能会带来过多的开销，如果使用new，他总会使用T::T()来初始化T数组的每个元素，如果我们还想要自己来初始化
Vec的元素，就不得不把每个元素初始化2次：一次是new初始化，一次是使用我们的值来初始化。更为糟糕的是，我们在push_back
函数中使用的分配空间的策略，这个策略意味着，每次我们需要更多的空间时，都会把vec的大小扩张一倍，我们没有理由初始化这些额外的元素。
他们只是在push_back函数中使用，push_back()只在有新的元素构造时才使用这些空间。如果使用new，不管是否使用都会被初始化。
                                                                                                                                                                                                           
*/
template<class T>
class Vec{
public:

	typedef T* iterator;
	typedef const T* const_iterator;
	typedef size_t size_type;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T& reference;
	typedef const T& const_reference;

	Vec() { create();}
	explicit Vec(size_t n,const T& val=T()) { create(n,val); }
	

	Vec(const Vec& v) { create(v.begin(),v.end());}
	
	//assignment operator
	Vec& operator=(const Vec&);
	
	~Vec() { uncreate();}


	size_type size() const{ return avail-data;} //ptrdiff_t可以转换为size_type
	T& operator[](size_type i) {return data[i];}
	const T& operator[](size_type i) const{ return data[i];}

	//iterator
	iterator begin() { return data;}
	const_iterator begin() const { return data;}
	iterator end() { return avail;}
	const_iterator end()const { return avail;}

	void push_back(const T& val)
	{
		if(avail==limit) //get space if needed
			grow();
		unchecked_append(val);//append the new elem
	}

	void clear() { uncreate(); }
	bool empty() const { return data == avail; }
	iterator erase(iterator first, iterator last)
	{
	 
		iterator  p, q;
		p=first,q=last;
		while(q!=avail)
		{
			*p++=*q++;
		}
	    
	    for(;p<avail;p++)
		{
			alloc.destroy(p);
		}
		avail=avail-(last-first);

		return first;

	}

private:

	iterator data;//first elem in the vec
	iterator avail;//pointer to( one past) the last constcutror elem
	iterator limit;//point to the last available elem

	//facilities for memory allocation
	allocator<T> alloc;//object to handle memory allocation

	//allocate and initialize the underlying array
	void create();
	void create(size_type,const T&);
	void create(const_iterator,const_iterator);

	//destroy the elems in the array and free the memory
	void uncreate();

	//support functions for push_back
	void grow();
	void unchecked_append(const T&);

};



#endif
