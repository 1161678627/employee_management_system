#include "employee.h"
// 构造函数
emoplyee::emoplyee(int id, string name, int deptid)
{
	m_name = name;
	m_id = id;
	m_deptid = deptid;
	// 也可以用this去赋值
	// this->m_id = id;
}
// 利用多态重写父类的函数
void emoplyee::showInfo()	// 可以不加 virtual 关键字
{
	cout << "职工编号为：" << this->m_id << "\t职工的姓名为：" << this->m_name << "\t职工的岗位是：" << this->getDeptName() << "\t岗位职责是：完成经理安排的任务" << endl;
}
// 获取岗位名称
string emoplyee::getDeptName()
{
	return "员工";
}