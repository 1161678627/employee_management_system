#pragma once	// 防止头文件重复包含
#include<iostream>
using namespace std;	// 使用标准的命名空间
#include "worker.h"

// 类的属性、方法定义写在这里
class workerManager
{
public:
	workerManager();
	~workerManager();
	void showMenu();	// 展示菜单的函数
	void exitSys();		// 退出系统函数
	void addWorker();	// 添加职工
	void writeTxt();	// 保存职工信息到本地
	int getEmployeeNum();	// 从本地文件中获取员工数量
	void init_wkarray();	// 从本地文件恢复职工信息到内存中
	void showWorker();	// 显示职工信息
	void delWorker();	// 删除职工
	void updateWorker();	// 更新员工信息
	void searchWorker();	// 查找职工信息
	void sortWorker();		// 职工信息排序-按照编号排序
	void clearWorker();		// 清空所有数据

	int m_size;		// 记录当前职工人数
	worker** wkarray;	// 创建一个指向 [职工类型数组] 的指针，为了统一维护不同职工到一个数组里，我们使用多态中父类可以管理子类指针的特性，使用worker类型的指针数组，存放子类实例化的指针进来
	bool m_fileIsEmpty;		// 标志文件中是否存有员工数据
private:

};