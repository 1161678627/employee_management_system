// 普通员工的类
#pragma once
#include<iostream>
#include "worker.h"
using namespace std;
#include<string>

class emoplyee : public worker
{
public:
	emoplyee(int id, string name, int deptid);	// 构造函数
	// 利用多态重写父类的函数
	void showInfo();	// 可以不加 virtual 关键字
	string getDeptName();		// 获取岗位名称
private:

};