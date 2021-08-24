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

// 利用多态重写父类的函数
void boss::showInfo()	// 可以不加 virtual 关键字
{
	cout << "职工编号为：" << this->m_id << "\t职工的姓名为：" << this->m_name << "\t职工的岗位是：" << this->getDeptName() << "\t岗位职责是：给经理安排工作" << endl;
}
// 获取岗位名称
string boss::getDeptName()
{
	return "ceo";
}