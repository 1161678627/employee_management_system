#pragma once
#include<iostream>
using namespace std;
#include<string>

class worker
{
public:
	//worker();
	//~worker();	// 多态的时候，抽象类的中构造函数最好注释掉，否则会出错误

	virtual void showInfo() = 0;	// 打印个人信息
	virtual string getDeptName() = 0;	//获取部门名称		这两个都是纯虚函数，所以这个类是抽象类，不需要写.cpp文件定义了，直接子类去继承，定义子类的.h和.cpp文件即可

	int m_id;	// 职工编号
	string m_name;		// 职工姓名
	int m_deptid;	// 部门编号
private:

};