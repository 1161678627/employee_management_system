#pragma once
#include<iostream>
using namespace std;
#include<string>

class worker
{
public:
	//worker();
	//~worker();	// ��̬��ʱ�򣬳�������й��캯�����ע�͵�������������

	virtual void showInfo() = 0;	// ��ӡ������Ϣ
	virtual string getDeptName() = 0;	//��ȡ��������		���������Ǵ��麯��������������ǳ����࣬����Ҫд.cpp�ļ������ˣ�ֱ������ȥ�̳У����������.h��.cpp�ļ�����

	int m_id;	// ְ�����
	string m_name;		// ְ������
	int m_deptid;	// ���ű��
private:

};