#include<vector>
#include <algorithm>    
#include <stdlib.h>  
#include<string>
#include <fstream>
#include <sstream>

using namespace std;

bool ishu;           //�к���־
vector<int> majiang(45), Peng_vec, Gang_vec, VecTemp, jilu, MjArray, del_jilu, compare_1, temp_vec,CA,majiang_temp;   //1���Ʒ���majiang[1]��2���Ʒ���majiang[2]���Դ�����
vector<vector<int> > Chi_vec, Hu_vec, compare_2, Last_vec;
vector<int>::iterator it;
int hangshu = 0, zhangshu, count_1, ishu_flag;
int AllPai[34] =
{
	1,2,3,4,5,6,7,8,9,                      //34������
	11,12,13,14,15,16,17,18,19,
	21,22,23,24,25,26,27,28,29,
	31,32,33,34,
	41,42,43
};
const char* charMap[44] =
{
	"", "һ��", "����", "����", "����", "����", "����", "����", "����", "����",
	"", "һ��", "����", "����", "����", "����", "����", "����", "����", "����",
	"", "һͲ", "��Ͳ", "��Ͳ", "��Ͳ", "��Ͳ", "��Ͳ", "��Ͳ", "��Ͳ", "��Ͳ",
	"", "����", "����", "�Ϸ�", "����", "", "", "", "", "",
	"", "����", "�װ�", "����",
};

ifstream a_in("C:\\Users\\zhaoyq\\Desktop\\majiang\\Test.log", ios::in);
ofstream a_out_hupai("C:\\Users\\zhaoyq\\Desktop\\majiang\\hupai_jilu.txt", ios::out);
ofstream a_out_all("C:\\Users\\zhaoyq\\Desktop\\majiang\\majiang_jilu.txt", ios::out);

void Gang(vector<int>&GangPai)
{
	Gang_vec.clear();
	int i = 1;
	while (i < 44)
	{
		if (GangPai[i] == 3)
		{
			Gang_vec.push_back(i);
		}
		i++;
	}
}

void Peng(vector<int>&PengPai)
{
	Peng_vec.clear();
	int i = 1;
	while (i < 44)
	{
		if (PengPai[i] == 3 || PengPai[i] == 2)
		{
			Peng_vec.push_back(i);
		}
		i++;
	}
}

void Chi(vector<int>&ChiPai)
{
	Chi_vec.clear();
	int i = 1;
	while (i < 30)
	{
		if ((ChiPai[i] > 0) && (ChiPai[i + 1] > 0))//����ȡ����
		{
			if (((i - 1) % 10 != 0) && (ChiPai[i - 1] < 4))//������ǰ
			{
				jilu.push_back(i - 1);         //�����ʽ
				jilu.push_back(i - 1);
				jilu.push_back(i);
				jilu.push_back(i + 1);
				Chi_vec.push_back(jilu);
				jilu.clear();
			}
			if (((i + 2) % 10 != 0) && (ChiPai[i + 2] < 4))//�����ں�
			{
				jilu.push_back(i + 2);
				jilu.push_back(i);
				jilu.push_back(i + 1);
				jilu.push_back(i + 2);
				Chi_vec.push_back(jilu);
				jilu.clear();
			}
		}

		if ((ChiPai[i] > 0) && (ChiPai[i + 2] > 0) && (i % 10 != 9) && (ChiPai[i + 1] < 4)) //��������
		{
			jilu.push_back(i + 1);
			jilu.push_back(i);
			jilu.push_back(i + 1);
			jilu.push_back(i + 2);
			Chi_vec.push_back(jilu);
			jilu.clear();
		}
		i++;
	}
}

bool Is_Empty()//1,Ϊ�գ�0���ǿա�
{
	int biaoji = 1;
	for (int i = 1; i < 44; ++i)
	{
		if (majiang[i] != 0)
		{
			biaoji = 0;
			break;
		}
	}
	return biaoji;
}

void huisu()
{
	if (Is_Empty())
	{
		Hu_vec.push_back(VecTemp);                     //�������̣�ִֻ����һ��
		ishu = true;
	}
	else
	{
		int i = 1;
		while (majiang[i] == 0) ++i;
		if (majiang[i] >= 3)                         //�жϿ��ӣ����У���ȥ��
		{
			majiang[i] -= 3;
			VecTemp.push_back(i);
			VecTemp.push_back(i);
			VecTemp.push_back(i);
			huisu();
			VecTemp.pop_back();
			VecTemp.pop_back();
			VecTemp.pop_back();
			majiang[i] += 3;
		}
		if (majiang[i + 1] && majiang[i + 2] && i < 30) //�ж�˳�ӣ����У���ȥ��
		{
			--majiang[i];
			--majiang[i + 1];
			--majiang[i + 2];
			VecTemp.push_back(i);
			VecTemp.push_back(i + 1);
			VecTemp.push_back(i + 2);
			huisu();
			VecTemp.pop_back();
			VecTemp.pop_back();
			VecTemp.pop_back();
			++majiang[i];
			++majiang[i + 1];
			++majiang[i + 2];
		}
	}
}

bool CanHu(int Pai)                     //14���Ʒ����ж�
{
	ishu = false;                       //�á�������־Ϊ��
	for (int i = 0; i < 44; i++)        //��һ��֮���Ƿ�����5����ͬ�Ƶ����
	{
		if (majiang[i] == 5)
			return ishu;
	}
	for (int i = 0; i < 44; i++)
	{
		if (majiang[i] >= 2)
		{
			majiang[i] -= 2;//ȥ����
			VecTemp.clear();
			VecTemp.push_back(Pai);
			VecTemp.push_back(i);
			VecTemp.push_back(i);
			huisu();                         //����ݹ�
			majiang[i] += 2;//��ԭ
		}
	}
	return ishu;
}

void paixu(vector<int>&paixu_vec)      //��Hu_vec[i]��������
{
	vector<vector<int> > a_sort(paixu_vec.size() / 3, vector<int>(3));
	for (int i = 1; i < paixu_vec.size(); i++)
	{
		if (i < 3)
			a_sort[(i - 1) / 3][(i - 1) % 3] = paixu_vec[i];
		if (i == 3)
			a_sort[0][2] = 0;
		if (i >= 3)
			a_sort[i / 3][i % 3] = paixu_vec[i];
	}
	sort(&a_sort[0], &a_sort[paixu_vec.size() / 3 - 1] + 1);    //�Զ�ά��������
	int size_now = paixu_vec.size();
	paixu_vec.erase(paixu_vec.begin() + 1, paixu_vec.end());    //ֻ������һ��Ԫ��
	for (int i = 0; i < size_now / 3; i++)     //����ά�������vector
	{
		for (int j = 0; j < 3; j++)
		{
			paixu_vec.push_back(a_sort[i][j]);
		}
	}
	//remove(paixu_vec.begin(), paixu_vec.end(), 0);    //��0�Ƶ�β������;1 1 2 3 4 0
	//paixu_vec.erase(paixu_vec.end() - 2, paixu_vec.end());   //ȥ��β����0
}



void zhengli_sort(vector<vector<int>>&vec)    //����Hu_vec���򣬷���Last_vec��
{
	for (int i = 0; i < Hu_vec.size(); i++)
	{
		//paixu(Hu_vec[i]);
		compare_2.clear();
		for (int j = 2; j < Hu_vec[i].size(); j++)   //�ӽ��Եĵڶ����ƿ�ʼ��
		{
			if (Hu_vec[i][j] == Hu_vec[i][0])       //Hu_vec[i][0]Ϊ����������
			{
				if (j == 2)
				{
					del_jilu.push_back(j);      //��¼Ҫɾ�����±�
					continue;
				}
				if (j % 3 == 0)
				{
					compare_1.push_back(Hu_vec[i][j]);
					compare_1.push_back(Hu_vec[i][j + 1]);
					compare_1.push_back(Hu_vec[i][j + 2]);
					if (!count(compare_2.begin(), compare_2.end(), compare_1))  //���compare_2������compare_1
					{
						compare_2.push_back(compare_1);
						del_jilu.push_back(j);
					}
				}
				if (j % 3 == 1)
				{
					compare_1.push_back(Hu_vec[i][j - 1]);
					compare_1.push_back(Hu_vec[i][j]);
					compare_1.push_back(Hu_vec[i][j + 1]);
					if (!count(compare_2.begin(), compare_2.end(), compare_1))
					{
						compare_2.push_back(compare_1);
						del_jilu.push_back(j);
					}
				}
				if (j % 3 == 2)
				{
					compare_1.push_back(Hu_vec[i][j - 2]);
					compare_1.push_back(Hu_vec[i][j - 1]);
					compare_1.push_back(Hu_vec[i][j]);
					if (!count(compare_2.begin(), compare_2.end(), compare_1))
					{
						compare_2.push_back(compare_1);
						del_jilu.push_back(j);
					}
				}
				compare_1.clear();
			}
		}
		for (int m = 0; m < del_jilu.size(); m++)   //Hu_vec[i]��ȥ��
		{
			temp_vec = Hu_vec[i];
			temp_vec.erase(temp_vec.begin() + del_jilu[m]);  //����ָ��λ�õ�Ԫ��
			if (del_jilu[m] % 3 == 2)                             //��������λ��ĩβ��0
			{
				temp_vec.insert(temp_vec.begin() + del_jilu[m], 0);
			}
			if (del_jilu[m] % 3 == 1)
			{
				temp_vec.insert(temp_vec.begin() + del_jilu[m] + 1, 0);
			}
			if (del_jilu[m] % 3 == 0)
			{
				temp_vec.insert(temp_vec.begin() + del_jilu[m] + 2, 0);
			}
			paixu(temp_vec);
			Last_vec.push_back(temp_vec);                   //�������vector��������������
			temp_vec.clear();
		}
		del_jilu.clear();
	}
}

void write_hupai_jilu(vector<int>&majiang_cp)        //���ܺ���������hupai_jiLu.txt
{
				a_out_hupai << "����Ϊ:";
				for (int i = 0; i < zhangshu; i++)
				{
					a_out_hupai << charMap[MjArray[i]] << " ";
				}
				a_out_hupai << endl;

				Peng(majiang_cp);
				a_out_hupai << "����������:";
				for (int i = 0; i < Peng_vec.size(); i++)
				{
					a_out_hupai << charMap[Peng_vec[i]] << " ";
				}
				a_out_hupai << endl;

				Gang(majiang_cp);
				a_out_hupai << "���Ըܵ���:";
				for (int i = 0; i < Gang_vec.size(); i++)
				{
					a_out_hupai << charMap[Gang_vec[i]] << " ";
				}
				a_out_hupai << endl;

				Chi(majiang_cp);
				a_out_hupai << "���ԳԵ���:" << endl;
				if (Chi_vec.size() > 0)
					sort(&Chi_vec[0], &Chi_vec[Chi_vec.size() - 1] + 1);
				for (int i = 0; i < Chi_vec.size(); i++)
				{
					int k = 0;
					if (i == 0)
					{
						a_out_hupai << charMap[Chi_vec[i][0]] << ":";
					}
					if (i - 1 >= 0)
					{
						if (Chi_vec[i][0] != Chi_vec[i - 1][0])
							a_out_hupai << charMap[Chi_vec[i][0]] << ":";
					}
					for (int j = 1; j < 4; j++)
					{
						if (Chi_vec[i][0] != Chi_vec[i][j])
						{
							a_out_hupai << charMap[Chi_vec[i][j]];
							k++;
							if (k == 1)
								a_out_hupai << " ";
						}
					}
					if (Chi_vec.size() > i + 1)
					{
						if (Chi_vec[i][0] != Chi_vec[i + 1][0])             //��ͬ,����Ҫ�������
							a_out_hupai << endl;
						else
							a_out_hupai << ",";
					}
				}

				Hu_vec.clear();
				if (Chi_vec.size() == 0)
					a_out_hupai << "���Ժ�����:" << endl;
				else
					a_out_hupai << endl << "���Ժ�����:" << endl;
				for (int i = 0; i < 34; i++)
				{
					++majiang_cp[AllPai[i]];            //��һ����,�ճ��ܺ��Ƶ�����
					CanHu(AllPai[i]);                //�к�
					--majiang_cp[AllPai[i]];
				}
				zhengli_sort(Hu_vec);
				sort(Last_vec.begin(), Last_vec.end());          //Last_vec����
				Last_vec.erase(unique(Last_vec.begin(), Last_vec.end()), Last_vec.end());     //Last_vecȥ��
				for (int i = 0; i < Last_vec.size(); i++)
				{
					if (i == 0)
					{
						a_out_hupai << charMap[Last_vec[i][0]] << ":";
					}
					if (i - 1 >= 0)
					{
						if (Last_vec[i][0] != Last_vec[i - 1][0])
							a_out_hupai << charMap[Last_vec[i][0]] << ":";
					}
					int k = 1;
					while (k < Last_vec[i].size())
					{
						if (Last_vec[i][k] != 0)
							a_out_hupai << charMap[Last_vec[i][k]];
						if (k % 3 == 0 && k + 1 != Last_vec[i].size())
						{
							a_out_hupai << ",";
							k++;
							continue;
						}
						k++;
						a_out_hupai << " ";
					}
					if (Last_vec.size() > i + 1)
					{
						if (Last_vec[i][0] != Last_vec[i + 1][0])             //��������ͬ,����Ҫ�������
							a_out_hupai << endl;
						else
							a_out_hupai << " ";
					}
				}
				Last_vec.clear();
				a_out_hupai << endl << endl;
}

