#include "employee.h"
// ���캯��
emoplyee::emoplyee(int id, string name, int deptid)
{
	m_name = name;
	m_id = id;
	m_deptid = deptid;
	// Ҳ������thisȥ��ֵ
	// this->m_id = id;
}
// ���ö�̬��д����ĺ���
void emoplyee::showInfo()	// ���Բ��� virtual �ؼ���
{
	cout << "ְ�����Ϊ��" << this->m_id << "\tְ��������Ϊ��" << this->m_name << "\tְ���ĸ�λ�ǣ�" << this->getDeptName() << "\t��λְ���ǣ���ɾ����ŵ�����" << endl;
}
// ��ȡ��λ����
string emoplyee::getDeptName()
{
	return "Ա��";
}