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

// 利用多态重写父类的函数
void manager::showInfo()	// 可以不加 virtual 关键字
{
	cout << "职工编号为：" << this->m_id << "\t职工的姓名为：" << this->m_name << "\t职工的岗位是：" << this->getDeptName() << "\t岗位职责是：完成老板安排的任务，并下发任务给普通员工" << endl;
}
// 获取岗位名称
string manager::getDeptName()
{
	return "经理";
}