#include "boss.h"

boss::boss(int id, string name, int deptid)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptid = deptid;
}

boss::~boss()
{
}

// ���ö�̬��д����ĺ���
void boss::showInfo()	// ���Բ��� virtual �ؼ���
{
	cout << "ְ�����Ϊ��" << this->m_id << "\tְ��������Ϊ��" << this->m_name << "\tְ���ĸ�λ�ǣ�" << this->getDeptName() << "\t��λְ���ǣ��������Ź���" << endl;
}
// ��ȡ��λ����
string boss::getDeptName()
{
	return "ceo";
}