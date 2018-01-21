#pragma once
#ifndef SMART_PTR_H
#define SMART_PTR_H
#include "SmartPtrToConst.h"

template <class T>
class SmartPtr:public SmartPtrToConst<T> {
public:
	SmartPtr(T* realPtr = 0) :pointee(realPtr) {};
	~SmartPtr() { if (pointee != 0) delete pointee; }
	SmartPtr(const SmartPtr& rhs);
	SmartPtr& operator=(const SmartPtr& rhs);
	T* operator->();
	T& operator*();
	bool operator!();
	template<class NewType>
	operator SmartPtr<NewType>() { return SmartPtr<NewType>(pointee); } //ģ���Ա����ʵ�����п�����ʽת�͵���ʵ������ָ�����ʽת��(��Ҫ�Ƕ�̬��ʱ����ô�)
//private:
//	T* pointee; //�ĳɼ̳��Ի��࣬���const����

};
#endif

template<class T>
inline SmartPtr<T>::SmartPtr(const SmartPtr & rhs)
{
	//ͨ�����ö���ת��ʵ�ֿ����͸�ֵ

	pointee = rhs.pointee;
	rhs.pointee = 0;

}

template<class T>
inline SmartPtr & SmartPtr<T>::operator=(const SmartPtr & rhs)
{
	if (rhs == *this)
		return *this;
	if (pointee != 0)
		delete pointee; //������ɾ���Լ��Ķ������
	pointee = rhs.pointee;
	rhs.pointee = 0;
	return *this;
}

template<class T>
inline T * SmartPtr<T>::operator->()
{
	return pointee;
}

template<class T>
inline T & SmartPtr<T>::operator*()
{
	return *this;
}

//�����Ƿ�Ϊ��
template<class T>
inline bool SmartPtr<T>::operator!()
{
	if (pointee == 0)
		return true;
	return false;
}