#pragma once
#include<iostream>
using namespace std;
#include<string>
#include "worker.h"

class manager : public worker
{
public:
	~manager();
	manager(int id, string name, int deptid);	// ���캯��
	// ���ö�̬��д����ĺ���
	void showInfo();	// ���Բ��� virtual �ؼ���
	string getDeptName();		// ��ȡ��λ����
private:

};