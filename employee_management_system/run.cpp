#include<iostream>
using namespace std;
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

void selectFunc(workerManager& wm);

int main() {
	// ���Զ�̬�Ƿ�ɹ�
	//worker* wk1;
	//wk1 = new emoplyee(1, "����", 1);
	//wk1->showInfo();
	//worker* wk2;
	//wk2 = new manager(1, "����", 1);
	//wk2->showInfo();
	//worker* wk3;
	//wk3 = new boss(1, "����", 1);
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
	cout << "������Ҫ���еĲ�����ţ�";
	cin >> choice;
	switch (choice)
	{
	case 0: //�˳�ϵͳ
		wm.exitSys();
		break;
	case 1: //���ְ��
		wm.addWorker();
		break;
	case 2: //��ʾְ��
		wm.showWorker();
		break;
	case 3: //ɾ��ְ��
		wm.delWorker();
		break;
	case 4: //�޸�ְ��
		wm.updateWorker();
		break;
	case 5: //����ְ��
		wm.searchWorker();
		break;
	case 6: //����ְ��
		wm.sortWorker();
		break;
	case 7: //����ļ�
		wm.clearWorker();
		break;
	default:
		system("cls");	// ���������Ķ�����ˢ��
		break;
	}
}