#include<vector>
#include <algorithm>    
#include <stdlib.h>  
#include<string>
#include <fstream>
#include <sstream>

using namespace std;

bool ishu;           //判胡标志
vector<int> majiang(45), Peng_vec, Gang_vec, VecTemp, jilu, MjArray, del_jilu, compare_1, temp_vec,CA,majiang_temp;   //1号牌放在majiang[1]，2号牌放在majiang[2]，以此类推
vector<vector<int> > Chi_vec, Hu_vec, compare_2, Last_vec;
vector<int>::iterator it;
int hangshu = 0, zhangshu, count_1, ishu_flag;
int AllPai[34] =
{
	1,2,3,4,5,6,7,8,9,                      //34张牌型
	11,12,13,14,15,16,17,18,19,
	21,22,23,24,25,26,27,28,29,
	31,32,33,34,
	41,42,43
};
const char* charMap[44] =
{
	"", "一条", "二条", "三条", "四条", "五条", "六条", "七条", "八条", "九条",
	"", "一万", "二万", "三万", "四万", "五万", "六万", "七万", "八万", "九万",
	"", "一筒", "二筒", "三筒", "四筒", "五筒", "六筒", "七筒", "八筒", "九筒",
	"", "东风", "西风", "南风", "北风", "", "", "", "", "",
	"", "红中", "白板", "发财",
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
		if ((ChiPai[i] > 0) && (ChiPai[i + 1] > 0))//两连取两边
		{
			if (((i - 1) % 10 != 0) && (ChiPai[i - 1] < 4))//插入在前
			{
				jilu.push_back(i - 1);         //输出格式
				jilu.push_back(i - 1);
				jilu.push_back(i);
				jilu.push_back(i + 1);
				Chi_vec.push_back(jilu);
				jilu.clear();
			}
			if (((i + 2) % 10 != 0) && (ChiPai[i + 2] < 4))//插入在后
			{
				jilu.push_back(i + 2);
				jilu.push_back(i);
				jilu.push_back(i + 1);
				jilu.push_back(i + 2);
				Chi_vec.push_back(jilu);
				jilu.clear();
			}
		}

		if ((ChiPai[i] > 0) && (ChiPai[i + 2] > 0) && (i % 10 != 9) && (ChiPai[i + 1] < 4)) //插入在中
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

bool Is_Empty()//1,为空；0，非空。
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
		Hu_vec.push_back(VecTemp);                     //整个过程，只执行了一次
		ishu = true;
	}
	else
	{
		int i = 1;
		while (majiang[i] == 0) ++i;
		if (majiang[i] >= 3)                         //判断刻子；若有，则去掉
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
		if (majiang[i + 1] && majiang[i + 2] && i < 30) //判断顺子；若有，则去掉
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

bool CanHu(int Pai)                     //14张牌分组判断
{
	ishu = false;                       //置“胡”标志为否
	for (int i = 0; i < 44; i++)        //加一张之后，是否会出现5张相同牌的情况
	{
		if (majiang[i] == 5)
			return ishu;
	}
	for (int i = 0; i < 44; i++)
	{
		if (majiang[i] >= 2)
		{
			majiang[i] -= 2;//去将牌
			VecTemp.clear();
			VecTemp.push_back(Pai);
			VecTemp.push_back(i);
			VecTemp.push_back(i);
			huisu();                         //进入递归
			majiang[i] += 2;//还原
		}
	}
	return ishu;
}

void paixu(vector<int>&paixu_vec)      //对Hu_vec[i]进行排序
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
	sort(&a_sort[0], &a_sort[paixu_vec.size() / 3 - 1] + 1);    //对二维数组排序
	int size_now = paixu_vec.size();
	paixu_vec.erase(paixu_vec.begin() + 1, paixu_vec.end());    //只保留第一个元素
	for (int i = 0; i < size_now / 3; i++)     //将二维数组放入vector
	{
		for (int j = 0; j < 3; j++)
		{
			paixu_vec.push_back(a_sort[i][j]);
		}
	}
	//remove(paixu_vec.begin(), paixu_vec.end(), 0);    //把0移到尾部，如;1 1 2 3 4 0
	//paixu_vec.erase(paixu_vec.end() - 2, paixu_vec.end());   //去除尾部的0
}



void zhengli_sort(vector<vector<int>>&vec)    //整理Hu_vec排序，放入Last_vec中
{
	for (int i = 0; i < Hu_vec.size(); i++)
	{
		//paixu(Hu_vec[i]);
		compare_2.clear();
		for (int j = 2; j < Hu_vec[i].size(); j++)   //从将对的第二张牌开始查
		{
			if (Hu_vec[i][j] == Hu_vec[i][0])       //Hu_vec[i][0]为胡的那张牌
			{
				if (j == 2)
				{
					del_jilu.push_back(j);      //记录要删除的下标
					continue;
				}
				if (j % 3 == 0)
				{
					compare_1.push_back(Hu_vec[i][j]);
					compare_1.push_back(Hu_vec[i][j + 1]);
					compare_1.push_back(Hu_vec[i][j + 2]);
					if (!count(compare_2.begin(), compare_2.end(), compare_1))  //如果compare_2不包含compare_1
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
		for (int m = 0; m < del_jilu.size(); m++)   //Hu_vec[i]里去重
		{
			temp_vec = Hu_vec[i];
			temp_vec.erase(temp_vec.begin() + del_jilu[m]);  //擦除指定位置的元素
			if (del_jilu[m] % 3 == 2)                             //将所擦除位置末尾置0
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
			Last_vec.push_back(temp_vec);                   //擦除后的vector放入最终排序里
			temp_vec.clear();
		}
		del_jilu.clear();
	}
}

void write_hupai_jilu(vector<int>&majiang_cp)        //把能胡的牌输入hupai_jiLu.txt
{
				a_out_hupai << "手牌为:";
				for (int i = 0; i < zhangshu; i++)
				{
					a_out_hupai << charMap[MjArray[i]] << " ";
				}
				a_out_hupai << endl;

				Peng(majiang_cp);
				a_out_hupai << "可以碰的牌:";
				for (int i = 0; i < Peng_vec.size(); i++)
				{
					a_out_hupai << charMap[Peng_vec[i]] << " ";
				}
				a_out_hupai << endl;

				Gang(majiang_cp);
				a_out_hupai << "可以杠的牌:";
				for (int i = 0; i < Gang_vec.size(); i++)
				{
					a_out_hupai << charMap[Gang_vec[i]] << " ";
				}
				a_out_hupai << endl;

				Chi(majiang_cp);
				a_out_hupai << "可以吃的牌:" << endl;
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
						if (Chi_vec[i][0] != Chi_vec[i + 1][0])             //相同,则不需要换行输出
							a_out_hupai << endl;
						else
							a_out_hupai << ",";
					}
				}

				Hu_vec.clear();
				if (Chi_vec.size() == 0)
					a_out_hupai << "可以胡的牌:" << endl;
				else
					a_out_hupai << endl << "可以胡的牌:" << endl;
				for (int i = 0; i < 34; i++)
				{
					++majiang_cp[AllPai[i]];            //加一张牌,凑成能胡牌的张数
					CanHu(AllPai[i]);                //判胡
					--majiang_cp[AllPai[i]];
				}
				zhengli_sort(Hu_vec);
				sort(Last_vec.begin(), Last_vec.end());          //Last_vec排序
				Last_vec.erase(unique(Last_vec.begin(), Last_vec.end()), Last_vec.end());     //Last_vec去重
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
						if (Last_vec[i][0] != Last_vec[i + 1][0])             //胡的牌相同,则不需要换行输出
							a_out_hupai << endl;
						else
							a_out_hupai << " ";
					}
				}
				Last_vec.clear();
				a_out_hupai << endl << endl;
}

