#include "manager.h"

manager::manager(int id, string name, int deptid)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptid = deptid;
}

manager::~manager()
{
}

// ���ö�̬��д����ĺ���
void manager::showInfo()	// ���Բ��� virtual �ؼ���
{
	cout << "ְ�����Ϊ��" << this->m_id << "\tְ��������Ϊ��" << this->m_name << "\tְ���ĸ�λ�ǣ�" << this->getDeptName() << "\t��λְ���ǣ�����ϰ尲�ŵ����񣬲��·��������ͨԱ��" << endl;
}
// ��ȡ��λ����
string manager::getDeptName()
{
	return "����";
}