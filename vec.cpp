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
  ע�⣬һ��Ҫ�ж�if(data),��Ϊalloc.deallocate������Ҫһ������ֻ�ڣ�����û���ڴ���Ҫ�ͷţ���Ϊ��������data�Ƿ�Ϊ0.
  ���ʹ��delete�Ͳ���Ҫ�ˣ�delete ���ǺϷ��ġ�
  ���data��Ϊ0�����Ǿͱ�����Vec��Ԫ���ϱ��������������ҵ���destroy������Ԫ�ء�Ϊ����delete���� ��Ϊһ�£����ǴӺ���ǰ����������
  Ԫ�أ���������Ԫ�غ󣬵���deallocate�ͷ����пռ�
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
	//���ԣ�ÿ�η���ʱ��������˫���Ŀռ䣬��Ȼvec��ǰ����Ϊ�գ���Ϊ���ǿ���ѡ��һ��Ԫ�صĿռ�����пռ��2�����Ƚϴ�С��
	//����max��2����������������ͬ������������ʽ������ptr_diff(1)
	size_type new_size=max(2*(limit-data),ptrdiff_t(1));

	/**
	 �������Ȱ�Ҫ�������Ԫ�صĿռ䱣����new_size�У������������ʵ���С�Ŀռ䣬���ҵ���uninitialze_copy�ѵ�ǰ�ռ��Ԫ�أ����Ƶ���
	 �ռ��У�Ȼ�����uncreate�������ͷ�ԭ�ȵ��ڴ棬���������������ָ���ֵ��
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
1.��copy constructor��֮ͬ����������Ҫɾ��������������е�ֵ��Ȼ�����Ҳ��������滻
2.��Ҫ��ֹ���Ҹ�ֵ
3.��ģ�������ռ��У�����ʡ�Բ������ͣ��ڡ�h�в��������Ѿ�����ʿ�����ˡ�һ������Vec<T>::operator=������
ָ����ʱ���Ƕ����Vec<T>��һ����Աʱ�����ǾͲ�����Ҫʹ��ģ���޶�����
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

