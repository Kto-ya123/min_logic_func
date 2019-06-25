#include<iostream>
#include<conio.h>
#include<vector>
#include<string>

using namespace std;


struct ConstEd
{
	ConstEd(string str)
	{
		Const = str;
		string el = "";
		for (int i(0); i < str.length(); i++)
		{
			if (str[i] != ' ' && str[i] != '+')
			{
				if (str[i] == '!')
				{
					el += str[i];
					el += str[i + 1];
					i++;
					vec.push_back(el);
				}
				else
				{
					el = str[i];
					vec.push_back(el);
				}
				el = "";
			}
		}
	}

	string Const;
	vector<string> vec;

};

struct ConstZer
{
	ConstZer(string str)
	{
		Const = str;
		string el = "";
		for (int i(0); i < str.length(); i++)
		{
			if (str[i] != ' ' && str[i] != '*')
			{
				if (str[i] == '!')
				{
					el += str[i];
					el += str[i + 1];
					vec.push_back(el);
					i++;
					
				}
				else
				{
					el = str[i];
					vec.push_back(el);
				}
				el = "";
			}
		}
	}
	string Const;
	vector<string> vec;
};

struct SKNF
{
	SKNF(string str)
	{
		int num = 0;
		string ConstStr;
		for (int i(0); i < str.length(); i++)
		{			
			if (str[i] == '*')
			{
				vec.push_back(ConstEd(ConstStr));
				ConstStr = " ";
				i++;
			}
			ConstStr += str[i];
		}
		vec.push_back(ConstEd(ConstStr));
	}
	void out()
	{
		for (int i(0); i < vec.size(); i++)
		{
			for (int j(0); j < vec[i].vec.size(); j++)
			{
				cout << vec[i].vec[j];
				if (j != vec[i].vec.size() - 1)
					cout << "+";
			}
			if (i != vec.size() - 1)
				cout << "*";
		}
		cout << endl;
	}

	vector<ConstEd> vec;
};

struct SDNF
{
	SDNF(string str)
	{
		int num = 0;
		string ConstStr;
		for (int i(0); i < str.length(); i++)
		{
			if (str[i] == '+')
			{
				vec.push_back(ConstZer(ConstStr));
				ConstStr = " ";
				i++;
			}
			ConstStr += str[i];
		}
		vec.push_back(ConstZer(ConstStr));
	}
	void out()
	{
		for (int i(0); i < vec.size(); i++)
		{
			for (int j(0); j < vec[i].vec.size(); j++)
			{
				cout << vec[i].vec[j];
				if (j != vec[i].vec.size() - 1)
					cout << "*";
			}
			if (i != vec.size() - 1)
				cout << "+";
		}
		cout << endl;
	}
	vector<ConstZer>vec;

};

template<typename T = SKNF> void minfunc(T& formula)
{
	for (int i(0); i < formula.vec.size() - 1; i++) //цикл для прохода формулам
	{
		for (int j(i + 1); j < formula.vec.size(); j++) // внутренний цикл
		{
			if (formula.vec[i].vec.size() == 3 && formula.vec[j].vec.size() == 3) // если рзмеры векторов равны три то можно произвести склейку
			{
				if (formula.vec[i].vec[0] == formula.vec[j].vec[0] && formula.vec[i].vec[1] == formula.vec[j].vec[1])
				{
					formula.vec.erase(formula.vec.begin() + j, formula.vec.begin() + j + 1);
					formula.vec[i].vec.erase(formula.vec[i].vec.begin() + 2, formula.vec[i].vec.begin() + 2 + 1);
				}
				else if (formula.vec[i].vec[0] == formula.vec[j].vec[0] && formula.vec[i].vec[2] == formula.vec[j].vec[2])
				{
					formula.vec.erase(formula.vec.begin() + j, formula.vec.begin() + j + 1);
					formula.vec[i].vec.erase(formula.vec[i].vec.begin() + 1, formula.vec[i].vec.begin() + 1 + 1);

				}
				else if (formula.vec[i].vec[1] == formula.vec[j].vec[1] && formula.vec[i].vec[2] == formula.vec[j].vec[2])
				{
					formula.vec.erase(formula.vec.begin() + j, formula.vec.begin() + j + 1);
					formula.vec[i].vec.erase(formula.vec[i].vec.begin(), formula.vec[i].vec.begin() + 1);
				}
			}
		}
	}
}

template<typename T = SKNF> void table(T& formula, T& minFormula)
{
	int **arr;
	arr = new int*[minFormula.vec.size()];
	cout << minFormula.vec.size() << endl;
	cout << formula.vec.size() << endl;
	for (int i(0); i < minFormula.vec.size(); i++)
	{
		arr[i] = new int[formula.vec.size()];
	}
	for (int i = 0; i < minFormula.vec.size(); i++)
	{
		for (int j(0); j < formula.vec.size(); j++)
		{
			bool val = true;
				for (int l(0); l < minFormula.vec[i].vec.size(); l++)
				{
					if (minFormula.vec[i].vec[l] == formula.vec[j].vec[0] || minFormula.vec[i].vec[l] == formula.vec[j].vec[1] || minFormula.vec[i].vec[l] == formula.vec[j].vec[2])
					{
						;
					}
					else
					{
						val = false;
						break;
					}
				}
				if (val)
				{
					arr[i][j] = 1;
				}
				else
				{
					arr[i][j] = 0;
				}
		}
	}
	for (int i(0); i < minFormula.vec.size(); i++)
	{
		for (int j(0); j < formula.vec.size(); j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}


int main()
{
	
	string sdnf = "!a*!b*c+!a*!b*!c+a*b*!c+!a*b*!c";
	string sknf = "a+!b+c*!a+!b+c*!a+!b+!c";
	SDNF minSDNF(sdnf);
	SKNF minSKNF(sknf);
	minSDNF.out();
	minSKNF.out();

	minfunc(minSDNF);
	minfunc(minSKNF);
	minSDNF.out();
	minSKNF.out();
	SDNF tSDNF(sdnf);
	SKNF tSKNF(sknf);
	table(tSKNF, minSKNF);
	

	_getch();
	return 0;
}