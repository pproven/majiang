/*表示法则:
1条-9条:1-9；
1万-9万:11-19；
1筒-9筒:21-29
东南西北:31,32,33,34
中发白:41,42,43
*/
#include "func.h"
#include<iostream>
#include <algorithm>    
#include<string.h>
#include <stdlib.h>  
#include <memory.h>
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock
#include <fstream>
#include <istream>

using namespace std;

int main()
{
	if (!a_in.is_open())
	{
		return 0;
	}
	string line;
	while (getline(a_in, line))
	{
		int val;
		//vector<int> CA;       //存储136张牌
		CA.clear();
		istringstream inStream(line);
		while (inStream >> val)
		{
			CA.push_back(val);
		}

		//所有牌型，输出到txt文件
		for (count_1 = 0; count_1 < 4; count_1++)                     //4,7,10,13张牌
		{
			MjArray.clear();
			zhangshu = count_1 * 3 + 4;
			MjArray.assign(&CA[0], &CA[zhangshu]);   //把前几张牌放入MjArray
			a_out_all << "手牌为:";
			for (int i = 0; i < zhangshu; i++)
			{
				++majiang[MjArray[i]];
				a_out_all << charMap[MjArray[i]] << " ";
			}
			a_out_all << endl;

			Peng(majiang);
			a_out_all << "可以碰的牌:";
			for (int i = 0; i < Peng_vec.size(); i++)
			{
				a_out_all << charMap[Peng_vec[i]] << " ";
			}
			a_out_all << endl;

			Gang(majiang);
			a_out_all << "可以杠的牌:";
			for (int i = 0; i < Gang_vec.size(); i++)
			{
				a_out_all << charMap[Gang_vec[i]] << " ";
			}
			a_out_all << endl;

			Chi(majiang);
			a_out_all << "可以吃的牌:" << endl;
			if (Chi_vec.size() > 0)
				sort(&Chi_vec[0], &Chi_vec[Chi_vec.size() - 1] + 1);
			for (int i = 0; i < Chi_vec.size(); i++)
			{
				int k = 0;
				if (i == 0)
				{
					a_out_all << charMap[Chi_vec[i][0]] << ":";
				}
				if (i - 1 >= 0)
				{
					if (Chi_vec[i][0] != Chi_vec[i - 1][0])
						a_out_all << charMap[Chi_vec[i][0]] << ":";
				}
				for (int j = 1; j < 4; j++)
				{
					if (Chi_vec[i][0] != Chi_vec[i][j])
					{
						a_out_all << charMap[Chi_vec[i][j]];
						k++;
						if (k == 1)
							a_out_all << " ";
					}
				}
				if (Chi_vec.size() > i + 1)
				{
					if (Chi_vec[i][0] != Chi_vec[i + 1][0])             //相同,则不需要换行输出
						a_out_all << endl;
					else
						a_out_all << ",";
				}
			}


			if (Chi_vec.size() == 0)
				a_out_all << "可以胡的牌:" << endl;
			else
				a_out_all << endl << "可以胡的牌:" << endl;
			Hu_vec.clear();
			for (int i = 0; i < 34; i++)
			{
				++majiang[AllPai[i]];            //加一张牌,凑成能胡牌的张数
				CanHu(AllPai[i]);                //判胡
				if (ishu==1)
				{
					ishu_flag = ishu;                   //用来标记是否跳转
					zhengli_sort(Hu_vec);
					sort(Last_vec.begin(), Last_vec.end());          //Last_vec排序
					Last_vec.erase(unique(Last_vec.begin(), Last_vec.end()), Last_vec.end());     //Last_vec去重
					for (int i = 0; i < Last_vec.size(); i++)
					{
						if (i == 0)
						{
							a_out_all << charMap[Last_vec[i][0]] << ":";
						}
						if (i - 1 >= 0)
						{
							if (Last_vec[i][0] != Last_vec[i - 1][0])
								a_out_all << charMap[Last_vec[i][0]] << ":";
						}
						int k = 1;
						while (k < Last_vec[i].size())
						{
							if (Last_vec[i][k] != 0)
								a_out_all << charMap[Last_vec[i][k]];
							if (k % 3 == 0 && k + 1 != Last_vec[i].size())
							{
								a_out_all << ",";
								k++;
								continue;
							}
							k++;
							a_out_all << " ";
						}
						if (Last_vec.size() > i + 1)
						{
							if (Last_vec[i][0] != Last_vec[i + 1][0])             //胡的牌相同,则不需要换行输出
								a_out_all << endl;
							else
								a_out_all << " ";
						}
					}
					Last_vec.clear();
					a_out_all << endl<<endl;
				}		
				--majiang[AllPai[i]];
				Hu_vec.clear();
			}
			if(ishu_flag)
			{
				write_hupai_jilu(majiang);
				ishu_flag = 0;
			}
			memset(&majiang[0], 0, majiang.size() * 4);
			if (ishu==0)
				a_out_all <<endl;                   //没有胡的牌，需要换行
		}
	}
	a_out_hupai.close();
	a_out_all.close();
	return 1;
}


		//胡的牌输出到majiang_jilu.txt
		//for (count_1 = 0; count_1 < 4; count_1++)                     //4,7,10,13张牌
		//{
		//	MjArray.clear();
		//	zhangshu = count_1 * 3 + 4;
		//	MjArray.assign(&CA[0], &CA[zhangshu]);   //把前几张牌放入MjArray
		//	memset(&majiang[0], 0, majiang.size() * 4);
		//	for (int i = 0; i < zhangshu; i++)
		//	{
		//		++majiang[MjArray[i]];
		//	}
		//	for (int i = 0; i < 34; i++)
		//	{
		//		++majiang[AllPai[i]];            //加一张牌,凑成能胡牌的张数
		//		CanHu(AllPai[i]);                //判胡
		//		--majiang[AllPai[i]];
		//				if (ishu == 1)
		//				{
		//					a_out_hupai << "手牌为:";
		//					for (int i = 0; i < zhangshu; i++)
		//					{
		//						a_out_hupai << charMap[MjArray[i]] << " ";
		//					}
		//					a_out_hupai << endl;

		//					Peng(majiang);
		//					a_out_hupai << "可以碰的牌:";
		//					for (int i = 0; i < Peng_vec.size(); i++)
		//					{
		//						a_out_hupai << charMap[Peng_vec[i]] << " ";
		//					}
		//					a_out_hupai << endl;

		//					Gang(majiang);
		//					a_out_hupai << "可以杠的牌:";
		//					for (int i = 0; i < Gang_vec.size(); i++)
		//					{
		//						a_out_hupai << charMap[Gang_vec[i]] << " ";
		//					}
		//					a_out_hupai << endl;

		//					Chi(majiang);
		//					a_out_hupai << "可以吃的牌:" << endl;
		//					if (Chi_vec.size() > 0)
		//						sort(&Chi_vec[0], &Chi_vec[Chi_vec.size() - 1] + 1);
		//					for (int i = 0; i < Chi_vec.size(); i++)
		//					{
		//						int k = 0;
		//						if (i == 0)
		//						{
		//							a_out_hupai << charMap[Chi_vec[i][0]] << ":";
		//						}
		//						if (i - 1 >= 0)
		//						{
		//							if (Chi_vec[i][0] != Chi_vec[i - 1][0])
		//								a_out_hupai << charMap[Chi_vec[i][0]] << ":";
		//						}
		//						for (int j = 1; j < 4; j++)
		//						{
		//							if (Chi_vec[i][0] != Chi_vec[i][j])
		//							{
		//								a_out_hupai << charMap[Chi_vec[i][j]];
		//								k++;
		//								if (k == 1)
		//									a_out_hupai << " ";
		//							}
		//						}
		//						if (Chi_vec.size() > i + 1)
		//						{
		//							if (Chi_vec[i][0] != Chi_vec[i + 1][0])             //相同,则不需要换行输出
		//								a_out_hupai << endl;
		//							else
		//								a_out_hupai << ",";
		//						}
		//					}

		//					Hu_vec.clear();
		//					if (Chi_vec.size() == 0)
		//						a_out_hupai << "可以胡的牌:" << endl;
		//					else
		//						a_out_hupai << endl << "可以胡的牌:" << endl;
		//					for (int i = 0; i < 34; i++)
		//					{
		//						++majiang[AllPai[i]];            //加一张牌,凑成能胡牌的张数
		//						CanHu(AllPai[i]);                //判胡
		//						--majiang[AllPai[i]];
		//					}
		//					zhengli_sort(Hu_vec);
		//					sort(Last_vec.begin(), Last_vec.end());          //Last_vec排序
		//					Last_vec.erase(unique(Last_vec.begin(), Last_vec.end()), Last_vec.end());     //Last_vec去重
		//					for (int i = 0; i < Last_vec.size(); i++)
		//					{
		//						if (i == 0)
		//						{
		//							a_out_hupai << charMap[Last_vec[i][0]] << ":";
		//						}
		//						if (i - 1 >= 0)
		//						{
		//							if (Last_vec[i][0] != Last_vec[i - 1][0])
		//								a_out_hupai << charMap[Last_vec[i][0]] << ":";
		//						}
		//						int k = 1;
		//						while (k < Last_vec[i].size())
		//						{
		//							if (Last_vec[i][k] != 0)
		//								a_out_hupai << charMap[Last_vec[i][k]];
		//							if (k % 3 == 0 && k + 1 != Last_vec[i].size())
		//							{
		//								a_out_hupai << ",";
		//								k++;
		//								continue;
		//							}
		//							k++;
		//							a_out_hupai << " ";
		//						}
		//						if (Last_vec.size() > i + 1)
		//						{
		//							if (Last_vec[i][0] != Last_vec[i + 1][0])             //胡的牌相同,则不需要换行输出
		//								a_out_hupai << endl;
		//							else
		//								a_out_hupai << " ";
		//						}
		//					}
		//					Last_vec.clear();
		//					a_out_hupai << endl << endl;
		//					break;
		//				}
		//			}
		//		}
		//		a_out_hupai.close();

