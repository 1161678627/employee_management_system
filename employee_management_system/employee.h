// ��ͨԱ������
#pragma once
#include<iostream>
#include "worker.h"
using namespace std;
#include<string>

class emoplyee : public worker
{
public:
	emoplyee(int id, string name, int deptid);	// ���캯��
	// ���ö�̬��д����ĺ���
	void showInfo();	// ���Բ��� virtual �ؼ���
	string getDeptName();		// ��ȡ��λ����
private:

};