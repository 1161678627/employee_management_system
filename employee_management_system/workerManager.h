#pragma once	// ��ֹͷ�ļ��ظ�����
#include<iostream>
using namespace std;	// ʹ�ñ�׼�������ռ�
#include "worker.h"

// ������ԡ���������д������
class workerManager
{
public:
	workerManager();
	~workerManager();
	void showMenu();	// չʾ�˵��ĺ���
	void exitSys();		// �˳�ϵͳ����
	void addWorker();	// ���ְ��
	void writeTxt();	// ����ְ����Ϣ������
	int getEmployeeNum();	// �ӱ����ļ��л�ȡԱ������
	void init_wkarray();	// �ӱ����ļ��ָ�ְ����Ϣ���ڴ���
	void showWorker();	// ��ʾְ����Ϣ
	void delWorker();	// ɾ��ְ��
	void updateWorker();	// ����Ա����Ϣ
	void searchWorker();	// ����ְ����Ϣ
	void sortWorker();		// ְ����Ϣ����-���ձ������
	void clearWorker();		// �����������

	int m_size;		// ��¼��ǰְ������
	worker** wkarray;	// ����һ��ָ�� [ְ����������] ��ָ�룬Ϊ��ͳһά����ְͬ����һ�����������ʹ�ö�̬�и�����Թ�������ָ������ԣ�ʹ��worker���͵�ָ�����飬�������ʵ������ָ�����
	bool m_fileIsEmpty;		// ��־�ļ����Ƿ����Ա������
private:

};