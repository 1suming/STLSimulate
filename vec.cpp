#include"vec.h"
#include <algorithm>

template<class T>
void Vec<T>::create()
{
	data=avail=limit=0;
}

template<class T>
void Vec<T>::create(size_type n,const T& val)
{
	data=alloc.allocate(n);
	limit=avail=data+n;
	uninitialized_fill(data,limit,val);
}


template<class T>
void Vec<T>::create(const_iterator i,const_iterator j)
{
	data=alloc.allocate(j-i);
	limit=avail=uninitialized_copy(i,j,data);
}

/**
  注意，一定要判断if(data),因为alloc.deallocate函数需要一个非零只在，即便没有内存需要释放，因为，必须检测data是否为0.
  如果使用delete就不需要了，delete 零是合法的。
  如果data不为0，我们就必须在Vec的元素上遍历迭代器，并且调用destroy来销毁元素。为了与delete【】 行为一致，我们从后往前来逆序销毁
  元素，销毁所有元素后，调用deallocate释放所有空间
  **/
template<class T>
void Vec<T>::uncreate()
{
	if(data)
	{
		//destroy (in reversed order) the elems
		iterator it=avail;
		while(it!=data)
			alloc.destroy(--it);

		//return all the space that was allocated
		alloc.deallocate(data,limit-data);

	}
	//reset pointer to indicater the vec is empty again
	data=limit=avail=0;
}

template<class T>
void Vec<T>::grow()
{
	//when growing ,allocate twice as much space as currently in use
	//策略，每次分配时，都分配双倍的空间，当然vec当前可能为空，因为我们可以选择一个元素的空间和已有空间的2倍来比较大小。
	//由于max的2个参数必须类型相同，所有我们显式构造了ptr_diff(1)
	size_type new_size=max(2*(limit-data),ptrdiff_t(1));

	/**
	 我们首先把要分配多少元素的空间保存在new_size中，接下来分配适当大小的空间，并且调用uninitialze_copy把当前空间的元素，复制到新
	 空间中，然后调用uncreate函数来释放原先的内存，最后我们重新设置指针的值。
	 **/
	iterator new_data=alloc.allocate(new_size);
	iterator new_avail=uninitialized_copy(data,avail,new_data);

	uncreate();

	//reset pointer
	data=new_data;
	avail=new_avail;
	limit=data+new_size;
}

template<class T>
void Vec<T>::unchecked_append(const T& val)
{
	alloc.construct(avail++,val);
}


/** assignment operator
1.与copy constructor不同之处，往往需要删除掉左操作数已有的值，然后用右操作数来替换
2.需要防止自我赋值
3.在模板的生存空间中，可以省略参数类型，在。h中参数类型已经被隐士包含了。一旦我们Vec<T>::operator=后，我们
指定它时我们定义的Vec<T>的一个成员时，我们就不再需要使用模板限定词了
**/
template<class T>
Vec<T>& Vec<T>::operator=(const Vec& rhs)
{
	//check for self-assignment
	if(&rhs != this)
	{
		//free the array in the left-hand side
		uncreate();

		create(rhs.begin(),rhs.end());
	}
	return *this;
}

