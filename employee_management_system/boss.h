#pragma once
#include<iostream>
using namespace std;
#include<string>
#include "worker.h"

class boss : public worker
{
public:
	~boss();
	boss(int id, string name, int deptid);	// ���캯��
	// ���ö�̬��д����ĺ���
	void showInfo();	// ���Բ��� virtual �ؼ���
	string getDeptName();		// ��ȡ��λ����
private:

};