#include "workerManager.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include<fstream>
#define FILENAME "example.txt"
#include<string>

// 类的方法实现在这里
workerManager::workerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	// 1.存储历史用户信息的文件不存在，即文件打开失败
	if (!ifs.is_open())
	{
		// cout << "记录人数的文件不存在！" << endl;
		// 初始化部分属性
		this->m_fileIsEmpty = true;
		this->m_size = 0;
		this->wkarray = NULL;
		ifs.close();
	}
	else
	{
		int num = this->getEmployeeNum();
		if (num)	// 如果初始化有员工
		{
			// cout << "历史职工的人数为：" << num << endl;
			this->m_size = num;
			this->m_fileIsEmpty = false;
			// 先初始化一个当前职工人数大小的 指针数组
			this->wkarray = new worker * [this->m_size];
			this->init_wkarray();
		}
		else    // 如果无员工
		{
			// cout << "有文件，但是无员工！" << endl;
			// 初始化部分属性
			this->m_fileIsEmpty = true;
			this->m_size = 0;
			this->wkarray = NULL;
		}
		ifs.close();
	}

}

workerManager::~workerManager()
{	
	// 堆区的数据，手动开辟，最好也手动释放下
	// 因为最后把 开辟在堆区的new_space传递到this->wkarray中，所以我么释放 wkarray即可
	if (this->wkarray != NULL)
	{	
		// 先释放数组中的每一个数据，再释放整个数组
		for (int i = 0; i < this->m_size; i++)
		{
			delete this->wkarray[i];	// // 释放堆区指针指向的数据后，记得将指针置为NULL指针
		}

		delete[] this->wkarray;	// 释放数组数据，加一个[]
		this->wkarray = NULL;
	}
}

// 展示菜单的函数
void workerManager::showMenu()
{
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

// 退出系统的函数
void workerManager::exitSys()
{
	cout << "程序即将退出，欢迎下次使用！" << endl;
	exit(0);
}

// 新增员工函数
void workerManager::addWorker()
{
	int add_num;
	cout << "请输入要添加的职工的个数：";
	cin >> add_num;
	if (add_num > 0)
	{
		// 计算新空间的长度，即用于维护员工个数的数组的长度
		int new_size = add_num + this->m_size;
		// 开辟新数组---用于copy原始数组中的职工，和添加新增职工
		worker** new_space = new worker * [new_size];
		// 将原来空间中维护的员工指针放到新的数组空间下
		if (this->wkarray != NULL)
		{
			for (int i = 0; i < this->m_size; i++)
			{
				new_space[i] = this->wkarray[i];
			}
		}
		// 批量添加新数据
		for (int i = 0; i < add_num; i++)
		{
			int id;
			string name;
			int dselect;
			while (true)
			{
				cout << "请输入第" << i + 1 << "个员工的编号：";
				cin >> id;
				// 判断id是否重复
				bool id_flag = false;
				for (int j = 0; j < this->m_size + i; j++)
				{
					if (id == new_space[j]->m_id)
					{
						id_flag = true;
					}
				}
				// 如果id没有重复的
				if (!id_flag)
				{
					break;
				}
				else
				{
					cout << "您输入的编号重复了，请重新输入！" << endl;
				}
			}
			cout << "请输入第" << i + 1 << "个员工的姓名：";
			cin >> name;
			cout << "请输入第" << i + 1 << "个员工的部门(1.普通员工，2.经理，3.老板)：";
			cin >> dselect;
			// 实例化worker父类指针，然后根据dselect的选择决定 将这个指针指向哪个 子类 的实例化对象
			worker* new_wk = NULL;	// 用父类指针，维护多个不同的子类
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
			// 将新增的员工维护到数组
			new_space[this->m_size + i] = new_wk;
		}
		// 释放该类维护职工数组的原有空间
		delete[] this->wkarray;	// 释放数组，需要加一个[]
		// 更新新空间的指向
		this->wkarray = new_space;
		// 更新职工人数
		this->m_size = new_size;
		cout << "成功添加了" << add_num << "名新员工！" << endl;
		this->m_fileIsEmpty = false;
		this->writeTxt();
	}
	else
	{
		cout << "错误输入！" << endl;
	}
	system("pause");
	system("cls");
}

// 将员工信息写到本地文件中
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

// 从本地文件判断保存的职工人数
int workerManager::getEmployeeNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int deptid;
	int num = 0;	// 记录人数
	while (ifs >> id && ifs >> name && ifs >> deptid)	// 这样读入的时候自动省略了空格，仅读每一行的非空格数据
	{
		// cout << name << "xxx" << endl;	的确依次能读到数据
		num++;
	}
	return num;
}

// 从本地文件恢复职工信息到内存中
void workerManager::init_wkarray()
{
	// 读取文件流
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int deptid;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> deptid)	// 这样读入的时候自动省略了空格，仅读每一行的非空格数据
	{
		worker* temp_wk = NULL;		// 指针最好初始化一下！
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

// 显示职工信息
void workerManager::showWorker()
{
	if (this->m_fileIsEmpty)
	{
		cout << "当前没有可显示职工信息！" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_size; i++)
		{
			//cout << "姓名：" << this->wkarray[i]->m_name << "\tID：" << this->wkarray[i]->m_id << "\t职位：" << this->wkarray[i]->m_deptid << endl;
			// 利用多态，调用不同类型员工自己的showinfo函数
			this->wkarray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

// 删除职工
void workerManager::delWorker()
{
	if (this->m_fileIsEmpty)
	{
		cout << "sry，当前无有效职工信息！" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "请输入要删除员工的编号：";
	int id;
	cin >> id;
	// 先找删除位置的索引
	int del_index = -1;
	for (int i = 0; i < this->m_size; i++)
	{
		if (this->wkarray[i]->m_id == id)
		{
			del_index = i;
			break;
		}
	}
	// 如果没找到删除索引位置，说明编号有误
	if (del_index == -1)
	{
		cout << "删除的编号有误，请确认后重新输入！" << endl;
	}
	else
	{
		cout << "成功删除编号：" << id << "，姓名：" << this->wkarray[del_index]->m_name << "的员工！" << endl;
		// 开始执行删除
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
	// 删除完了之后，应该重新写入下 txt文件，更新本地缓存
	this->writeTxt();

	system("pause");
	system("cls");
}

// 更新员工信息
void workerManager::updateWorker()
{
	if (this->m_fileIsEmpty)
	{
		cout << "sry，当前无有效职工信息！" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "请输入要更新的员工的编号：";
	int id;
	cin >> id;
	// 先找gengxin位置的索引
	int update_index = -1;
	for (int i = 0; i < this->m_size; i++)
	{
		if (this->wkarray[i]->m_id == id)
		{
			update_index = i;
			cout << "请选择要更新员工：" << this->wkarray[i]->m_name << " 的什么信息：" << endl;
			cout << "更新姓名输入1" << endl;
			cout << "更新编号输入2" << endl;
			cout << "更新部门输入3" << endl;
			int update_flag;
			cin >> update_flag;
			cout << "请输入更新后的信息：" << endl;
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
					// 判断id是否重复
					bool id_flag = false;
					for (int j = 0; j < this->m_size; j++)
					{
						if (id == this->wkarray[j]->m_id && update_index != j)
						{
							id_flag = true;
						}
					}
					// 如果id没有重复的
					if (!id_flag)
					{
						break;
					}
					else
					{
						cout << "您输入的编号重复了，请重新输入！" << endl;
						cout << "请输入更新后的信息：" << endl;
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
				// 如果岗位换了，是要重新new一个对象出来的，不能仅改一个编号，因为岗位涉及到他的showinfo方法，这个信息目前之关联在对象类上
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
				// 将原来堆区指向的数据释放
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
	// 如果没找到更新索引位置，说明编号有误
	if (update_index == -1)
	{
		cout << "更新的编号有误，请确认后重新输入！" << endl;
	}
	this->writeTxt();
	system("pause");
	system("cls");
}

// 查找职工信息
void workerManager::searchWorker()
{
	if (this->m_fileIsEmpty)
	{
		cout << "sry，当前无有效职工信息！" << endl;
		system("pause");
		system("cls");
		return;
	}
	bool flag = false;
	cout << "请选择查找职工的方式(1.姓名 2.编号)：";
	int choice;
	cin >> choice;
	if (choice ==1)
	{
		cout << "请输入待查找员工的姓名：";
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
		cout << "请输入待查找员工的编号：";
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
	// 没查到员工编号
	if (!flag)
	{
		cout << "您输入的查询信息有误，请确认后执行查找！" << endl;
	}
	system("pause");
	system("cls");
}

// 职工信息排序-按照编号排序
void workerManager::sortWorker()
{
	if (this->m_fileIsEmpty)
	{
		cout << "sry，当前无有效职工信息！" << endl;
		system("pause");
		system("cls");
		return;
	}
	bool flag = false;
	cout << "请选择排序职工的方式(1.升序 2.降序)：";
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
			// 找到这一圈的最小的元素后，交换位置
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
			// 找到这一圈的最小的元素后，交换位置
			temp_wk = this->wkarray[max_index];
			this->wkarray[max_index] = this->wkarray[i];
			this->wkarray[i] = temp_wk;
		}
	}
	this->writeTxt();
	this->showWorker();
}

// 清空所有职工文件
void workerManager::clearWorker()
{
	if (this->m_fileIsEmpty)
	{
		cout << "sry，当前无有效职工信息！" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "请确认是否要清空所有用户信息，输入1继续，输入2退出：";
	int choice;
	cin >> choice;
	if (choice == 2)
	{
		return;
	}
	// 开始执行清空
	// 先释放用户数组中 存放在堆区的数据
	// 释放堆区数组的时候，应该先把其中的每一个元素都释放，再释放整个数组
	for (int i = 0; i < this->m_size; i++)
	{
		// 如果 用户信息指针不为空，则释放该内存
		if (this->wkarray[i] != NULL)
		{
			delete this->wkarray[i];
			this->wkarray[i] = NULL;	// 释放堆区指针指向的数据后，记得将指针置为NULL指针
		}
	}
	// 释放完了，重置相关变量
	this->m_size = 0;
	delete[] this->wkarray;
	this->m_fileIsEmpty = true;
	this->wkarray = NULL;
	this->writeTxt();	// 重新写入文件，将文件置空
	cout << "清空成功！" << endl;
	system("pause");
	system("cls");
}