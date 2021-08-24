#include<iostream>
using namespace std;
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

void selectFunc(workerManager& wm);

int main() {
	// 测试多态是否成功
	//worker* wk1;
	//wk1 = new emoplyee(1, "张三", 1);
	//wk1->showInfo();
	//worker* wk2;
	//wk2 = new manager(1, "张三", 1);
	//wk2->showInfo();
	//worker* wk3;
	//wk3 = new boss(1, "张三", 1);
	//wk3->showInfo();

	workerManager wm;
	while (true)
	{
		wm.showMenu();
		selectFunc(wm);
	}
	
	return 0;
}

void selectFunc(workerManager& wm) {
	int choice = -1;
	cout << "请输入要进行的操作序号：";
	cin >> choice;
	switch (choice)
	{
	case 0: //退出系统
		wm.exitSys();
		break;
	case 1: //添加职工
		wm.addWorker();
		break;
	case 2: //显示职工
		wm.showWorker();
		break;
	case 3: //删除职工
		wm.delWorker();
		break;
	case 4: //修改职工
		wm.updateWorker();
		break;
	case 5: //查找职工
		wm.searchWorker();
		break;
	case 6: //排序职工
		wm.sortWorker();
		break;
	case 7: //清空文件
		wm.clearWorker();
		break;
	default:
		system("cls");	// 输入其他的都清屏刷新
		break;
	}
}