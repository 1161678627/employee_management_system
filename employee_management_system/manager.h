#pragma once
#include<iostream>
using namespace std;
#include<string>
#include "worker.h"

class manager : public worker
{
public:
	~manager();
	manager(int id, string name, int deptid);	// 构造函数
	// 利用多态重写父类的函数
	void showInfo();	// 可以不加 virtual 关键字
	string getDeptName();		// 获取岗位名称
private:

};