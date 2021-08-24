#include "workerManager.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include<fstream>
#define FILENAME "example.txt"
#include<string>

// ��ķ���ʵ��������
workerManager::workerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	// 1.�洢��ʷ�û���Ϣ���ļ������ڣ����ļ���ʧ��
	if (!ifs.is_open())
	{
		// cout << "��¼�������ļ������ڣ�" << endl;
		// ��ʼ����������
		this->m_fileIsEmpty = true;
		this->m_size = 0;
		this->wkarray = NULL;
		ifs.close();
	}
	else
	{
		int num = this->getEmployeeNum();
		if (num)	// �����ʼ����Ա��
		{
			// cout << "��ʷְ��������Ϊ��" << num << endl;
			this->m_size = num;
			this->m_fileIsEmpty = false;
			// �ȳ�ʼ��һ����ǰְ��������С�� ָ������
			this->wkarray = new worker * [this->m_size];
			this->init_wkarray();
		}
		else    // �����Ա��
		{
			// cout << "���ļ���������Ա����" << endl;
			// ��ʼ����������
			this->m_fileIsEmpty = true;
			this->m_size = 0;
			this->wkarray = NULL;
		}
		ifs.close();
	}

}

workerManager::~workerManager()
{	
	// ���������ݣ��ֶ����٣����Ҳ�ֶ��ͷ���
	// ��Ϊ���� �����ڶ�����new_space���ݵ�this->wkarray�У�������ô�ͷ� wkarray����
	if (this->wkarray != NULL)
	{	
		// ���ͷ������е�ÿһ�����ݣ����ͷ���������
		for (int i = 0; i < this->m_size; i++)
		{
			delete this->wkarray[i];	// // �ͷŶ���ָ��ָ������ݺ󣬼ǵý�ָ����ΪNULLָ��
		}

		delete[] this->wkarray;	// �ͷ��������ݣ���һ��[]
		this->wkarray = NULL;
	}
}

// չʾ�˵��ĺ���
void workerManager::showMenu()
{
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

// �˳�ϵͳ�ĺ���
void workerManager::exitSys()
{
	cout << "���򼴽��˳�����ӭ�´�ʹ�ã�" << endl;
	exit(0);
}

// ����Ա������
void workerManager::addWorker()
{
	int add_num;
	cout << "������Ҫ��ӵ�ְ���ĸ�����";
	cin >> add_num;
	if (add_num > 0)
	{
		// �����¿ռ�ĳ��ȣ�������ά��Ա������������ĳ���
		int new_size = add_num + this->m_size;
		// ����������---����copyԭʼ�����е�ְ�������������ְ��
		worker** new_space = new worker * [new_size];
		// ��ԭ���ռ���ά����Ա��ָ��ŵ��µ�����ռ���
		if (this->wkarray != NULL)
		{
			for (int i = 0; i < this->m_size; i++)
			{
				new_space[i] = this->wkarray[i];
			}
		}
		// �������������
		for (int i = 0; i < add_num; i++)
		{
			int id;
			string name;
			int dselect;
			while (true)
			{
				cout << "�������" << i + 1 << "��Ա���ı�ţ�";
				cin >> id;
				// �ж�id�Ƿ��ظ�
				bool id_flag = false;
				for (int j = 0; j < this->m_size + i; j++)
				{
					if (id == new_space[j]->m_id)
					{
						id_flag = true;
					}
				}
				// ���idû���ظ���
				if (!id_flag)
				{
					break;
				}
				else
				{
					cout << "������ı���ظ��ˣ����������룡" << endl;
				}
			}
			cout << "�������" << i + 1 << "��Ա����������";
			cin >> name;
			cout << "�������" << i + 1 << "��Ա���Ĳ���(1.��ͨԱ����2.����3.�ϰ�)��";
			cin >> dselect;
			// ʵ����worker����ָ�룬Ȼ�����dselect��ѡ����� �����ָ��ָ���ĸ� ���� ��ʵ��������
			worker* new_wk = NULL;	// �ø���ָ�룬ά�������ͬ������
			switch (dselect)
			{
			case 1:
				new_wk = new emoplyee(id, name, dselect);
				break;
			case 2:
				new_wk = new manager(id, name, dselect);
				break;
			case 3:
				new_wk = new boss(id, name, dselect);
				break;
			default:
				break;
			}
			// ��������Ա��ά��������
			new_space[this->m_size + i] = new_wk;
		}
		// �ͷŸ���ά��ְ�������ԭ�пռ�
		delete[] this->wkarray;	// �ͷ����飬��Ҫ��һ��[]
		// �����¿ռ��ָ��
		this->wkarray = new_space;
		// ����ְ������
		this->m_size = new_size;
		cout << "�ɹ������" << add_num << "����Ա����" << endl;
		this->m_fileIsEmpty = false;
		this->writeTxt();
	}
	else
	{
		cout << "�������룡" << endl;
	}
	system("pause");
	system("cls");
}

// ��Ա����Ϣд�������ļ���
void workerManager::writeTxt()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_size; i++)
	{
		ofs << this->wkarray[i]->m_id << "  " << this->wkarray[i]->m_name << "  " << this->wkarray[i]->m_deptid << endl;
		// cout << this->wkarray[i]->m_id << "  " << this->wkarray[i]->m_name << "  " << this->wkarray[i]->m_deptid << endl;
	}
	ofs.close();
}

// �ӱ����ļ��жϱ����ְ������
int workerManager::getEmployeeNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int deptid;
	int num = 0;	// ��¼����
	while (ifs >> id && ifs >> name && ifs >> deptid)	// ���������ʱ���Զ�ʡ���˿ո񣬽���ÿһ�еķǿո�����
	{
		// cout << name << "xxx" << endl;	��ȷ�����ܶ�������
		num++;
	}
	return num;
}

// �ӱ����ļ��ָ�ְ����Ϣ���ڴ���
void workerManager::init_wkarray()
{
	// ��ȡ�ļ���
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int deptid;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> deptid)	// ���������ʱ���Զ�ʡ���˿ո񣬽���ÿһ�еķǿո�����
	{
		worker* temp_wk = NULL;		// ָ����ó�ʼ��һ�£�
		switch (deptid)
		{
		case 1:
			temp_wk = new emoplyee(id, name, deptid);
			break;
		case 2:
			temp_wk = new manager(id, name, deptid);
			break;
		case 3:
			temp_wk = new boss(id, name, deptid);
			break;
		default:
			break;
		}
		wkarray[index++] = temp_wk;
	}
	ifs.close();
}

// ��ʾְ����Ϣ
void workerManager::showWorker()
{
	if (this->m_fileIsEmpty)
	{
		cout << "��ǰû�п���ʾְ����Ϣ��" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_size; i++)
		{
			//cout << "������" << this->wkarray[i]->m_name << "\tID��" << this->wkarray[i]->m_id << "\tְλ��" << this->wkarray[i]->m_deptid << endl;
			// ���ö�̬�����ò�ͬ����Ա���Լ���showinfo����
			this->wkarray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

// ɾ��ְ��
void workerManager::delWorker()
{
	if (this->m_fileIsEmpty)
	{
		cout << "sry����ǰ����Чְ����Ϣ��" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "������Ҫɾ��Ա���ı�ţ�";
	int id;
	cin >> id;
	// ����ɾ��λ�õ�����
	int del_index = -1;
	for (int i = 0; i < this->m_size; i++)
	{
		if (this->wkarray[i]->m_id == id)
		{
			del_index = i;
			break;
		}
	}
	// ���û�ҵ�ɾ������λ�ã�˵���������
	if (del_index == -1)
	{
		cout << "ɾ���ı��������ȷ�Ϻ��������룡" << endl;
	}
	else
	{
		cout << "�ɹ�ɾ����ţ�" << id << "��������" << this->wkarray[del_index]->m_name << "��Ա����" << endl;
		// ��ʼִ��ɾ��
		for (int i = del_index; i < this->m_size - 1; i++)
		{
			this->wkarray[i] = this->wkarray[i + 1];
		}
		this->m_size -= 1;
		if (!this->m_size)
		{
			this->m_fileIsEmpty = true;
		}
	}
	// ɾ������֮��Ӧ������д���� txt�ļ������±��ػ���
	this->writeTxt();

	system("pause");
	system("cls");
}

// ����Ա����Ϣ
void workerManager::updateWorker()
{
	if (this->m_fileIsEmpty)
	{
		cout << "sry����ǰ����Чְ����Ϣ��" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "������Ҫ���µ�Ա���ı�ţ�";
	int id;
	cin >> id;
	// ����gengxinλ�õ�����
	int update_index = -1;
	for (int i = 0; i < this->m_size; i++)
	{
		if (this->wkarray[i]->m_id == id)
		{
			update_index = i;
			cout << "��ѡ��Ҫ����Ա����" << this->wkarray[i]->m_name << " ��ʲô��Ϣ��" << endl;
			cout << "������������1" << endl;
			cout << "���±������2" << endl;
			cout << "���²�������3" << endl;
			int update_flag;
			cin >> update_flag;
			cout << "��������º����Ϣ��" << endl;
			switch (update_flag)
			{
			case 1:
			{
				string name;
				cin >> name;
				this->wkarray[i]->m_name = name;
			}
			break;
			case 2:
			{
				int id;
				while (true)
				{
					cin >> id;
					// �ж�id�Ƿ��ظ�
					bool id_flag = false;
					for (int j = 0; j < this->m_size; j++)
					{
						if (id == this->wkarray[j]->m_id && update_index != j)
						{
							id_flag = true;
						}
					}
					// ���idû���ظ���
					if (!id_flag)
					{
						break;
					}
					else
					{
						cout << "������ı���ظ��ˣ����������룡" << endl;
						cout << "��������º����Ϣ��" << endl;
					}
				}
				this->wkarray[i]->m_id = id;
			}
			break;
			case 3:
			{
				int deptid;
				cin >> deptid;
				// this->wkarray[i]->m_deptid = deptid;
				// �����λ���ˣ���Ҫ����newһ����������ģ����ܽ���һ����ţ���Ϊ��λ�漰������showinfo�����������ϢĿǰ֮�����ڶ�������
				string name = this->wkarray[i]->m_name;
				int id = this->wkarray[i]->m_id;
				worker* temp_wk = NULL;
				if (deptid == 1)
				{
					temp_wk = new emoplyee(id, name, deptid);
				}
				else if (deptid == 2)
				{
					temp_wk = new manager(id, name, deptid);
				}
				else
				{
					temp_wk = new boss(id, name, deptid);
				}
				// ��ԭ������ָ��������ͷ�
				delete this->wkarray[i];
				this->wkarray[i] = temp_wk;
			}
			break;
			default:
				break;
			}
			break;
		}
	}
	// ���û�ҵ���������λ�ã�˵���������
	if (update_index == -1)
	{
		cout << "���µı��������ȷ�Ϻ��������룡" << endl;
	}
	this->writeTxt();
	system("pause");
	system("cls");
}

// ����ְ����Ϣ
void workerManager::searchWorker()
{
	if (this->m_fileIsEmpty)
	{
		cout << "sry����ǰ����Чְ����Ϣ��" << endl;
		system("pause");
		system("cls");
		return;
	}
	bool flag = false;
	cout << "��ѡ�����ְ���ķ�ʽ(1.���� 2.���)��";
	int choice;
	cin >> choice;
	if (choice ==1)
	{
		cout << "�����������Ա����������";
		string name;
		cin >> name;
		for (int i = 0; i < this->m_size; i++)
		{
			if (name == this->wkarray[i]->m_name)
			{
				flag = true;
				this->wkarray[i]->showInfo();
				break;
			}
		}
	}
	else
	{
		cout << "�����������Ա���ı�ţ�";
		int id;
		cin >> id;
		for (int i = 0; i < this->m_size; i++)
		{
			if (id == this->wkarray[i]->m_id)
			{
				flag = true;
				this->wkarray[i]->showInfo();
				break;
			}
		}
	}
	// û�鵽Ա�����
	if (!flag)
	{
		cout << "������Ĳ�ѯ��Ϣ������ȷ�Ϻ�ִ�в��ң�" << endl;
	}
	system("pause");
	system("cls");
}

// ְ����Ϣ����-���ձ������
void workerManager::sortWorker()
{
	if (this->m_fileIsEmpty)
	{
		cout << "sry����ǰ����Чְ����Ϣ��" << endl;
		system("pause");
		system("cls");
		return;
	}
	bool flag = false;
	cout << "��ѡ������ְ���ķ�ʽ(1.���� 2.����)��";
	int choice;
	cin >> choice;
	if (choice == 1)
	{
		for (int i = 0; i < this->m_size - 1; i++)
		{
			worker* temp_wk = NULL;
			int min_index = i;
			for (int j = i + 1; j < this->m_size; j++)
			{
				if (this->wkarray[min_index]->m_id < this->wkarray[j]->m_id)
				{
					
				}
				else
				{
					min_index = j;
				}
			}
			// �ҵ���һȦ����С��Ԫ�غ󣬽���λ��
			temp_wk = this->wkarray[min_index];
			this->wkarray[min_index] = this->wkarray[i];
			this->wkarray[i] = temp_wk;
		}
	}
	else
	{
		for (int i = 0; i < this->m_size - 1; i++)
		{
			worker* temp_wk = NULL;
			int max_index = i;
			for (int j = i + 1; j < this->m_size; j++)
			{
				if (this->wkarray[max_index]->m_id < this->wkarray[j]->m_id)
				{
					max_index = j;
				}
				else
				{
					
				}
			}
			// �ҵ���һȦ����С��Ԫ�غ󣬽���λ��
			temp_wk = this->wkarray[max_index];
			this->wkarray[max_index] = this->wkarray[i];
			this->wkarray[i] = temp_wk;
		}
	}
	this->writeTxt();
	this->showWorker();
}

// �������ְ���ļ�
void workerManager::clearWorker()
{
	if (this->m_fileIsEmpty)
	{
		cout << "sry����ǰ����Чְ����Ϣ��" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "��ȷ���Ƿ�Ҫ��������û���Ϣ������1����������2�˳���";
	int choice;
	cin >> choice;
	if (choice == 2)
	{
		return;
	}
	// ��ʼִ�����
	// ���ͷ��û������� ����ڶ���������
	// �ͷŶ��������ʱ��Ӧ���Ȱ����е�ÿһ��Ԫ�ض��ͷţ����ͷ���������
	for (int i = 0; i < this->m_size; i++)
	{
		// ��� �û���Ϣָ�벻Ϊ�գ����ͷŸ��ڴ�
		if (this->wkarray[i] != NULL)
		{
			delete this->wkarray[i];
			this->wkarray[i] = NULL;	// �ͷŶ���ָ��ָ������ݺ󣬼ǵý�ָ����ΪNULLָ��
		}
	}
	// �ͷ����ˣ�������ر���
	this->m_size = 0;
	delete[] this->wkarray;
	this->m_fileIsEmpty = true;
	this->wkarray = NULL;
	this->writeTxt();	// ����д���ļ������ļ��ÿ�
	cout << "��ճɹ���" << endl;
	system("pause");
	system("cls");
}