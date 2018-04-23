// graph lab1.cpp : Defines the entry point for the console application.
//

#include <sstream>
#include <iostream>
#include <vector>
#include <strstream>
#include <fstream>
#include <set>
#include <math.h>
#include <locale.h>
#include <string>
#include <tuple>
/*
1. Ввод/вывод из файла данных, представляющих простой граф формата:
• Матрица смежности
• Списки смежных вершин
• Список ребер
2. Добавление/удаление ребра графа
3. Изменение веса ребра графа
4. Преобразование одного представления в другое
*/
using namespace std;

class DSU  {
	

	vector<int> p;
	vector<int> rank;
public:
	DSU(int n)
	{
		for (int i = 0; i <= n; i++)
		{
			p.push_back(i);
			rank.push_back(0);
			// p[i] = i;
			// r[i] = 0;
		}
	}
	
	int find(int x)
	{
		return (x == p[x] ? x : p[x] = find(p[x]));
	}

	void unite(int x, int y)
	{
		if ((x = find(x)) == (y = find(y)))
			return;

		if (rank[x] <  rank[y])
			p[x] = y;
		else {
			p[y] = x;
			if (rank[x] == rank[y])
				++rank[x];
		}
	} 

};

class Graph {

	int orientation;
	int weighted;
	int N;
	int M;
	char type;

	vector < vector <int> > adjmatrix;  // матрица смежности
	vector<set<pair<int, int>>>  alist; // список смежных вершин для невзвешенного графа
	vector<set<tuple<int, int, int>>>  awlist;  // список смежных вершин для взвешенного графа
	//vector<set<pair<int, int>>> b1; // список смежных вершин для невзвешенного графа
	//vector<set<tuple<int, int, int>>> b2; // список смежных вершин для взвешенного графа
	set<pair<int, int>> edges; // список ребер для невзвешенного графа
	set<tuple<int, int, int>> wedges; // список ребер для взвешенного графа
	
	

public:
	// конструктор без параметров
	Graph()
	{
	}

	// конструктор взвешенного ориентированного графа с N изолированными вершинами
	Graph(int n)
	{
		vector <int> a1;
		type = 'C';
		N = n;
		M = 0;
		orientation = 0;
		weighted = 1;
		adjmatrix.clear();
		a1.clear();
		for (int i = 0; i < N; i++)
		{
			a1.clear();
			for (int j = 0; j < N; j++)
			{
				a1.push_back(0);
			}
			adjmatrix.push_back(a1);
		}
	}
	void readGraph(string fileName)
	{
		ifstream fin;
		vector<string> st;
		string s, s1;
		int k;
		fin.open(fileName, ios::in);

		if (!fin)
			cout << "Ошибка, файл не найден " << endl;
		else
		{
			fin >> type >> N; // считывается индикатор и кол-во вершин в графе
			if (type == 'E')
				fin >> M; // считывается кол-во ребер в графе
			else
				M = 0;

			fin >> orientation >> weighted; // считывается индикатор на не/ориентированность и не/взвешенность
			if (type == 'C' || type == 'L')
				k = N; // кол-во вершин
			else
				k = M; // кол-во ребер

			getline(fin, s1);
			for (int i = 0; i < k; i++)
			{
				getline(fin, s1); // считывается строка представления графа из файла
				st.push_back(s1);
			}
			fin.close();

			if (type == 'C')
				// заполняем матрицу смежности
			{ adjmatrix.resize(st.size());
			int vertice;
			for (int i = 0; i < st.size(); i++)
			{
				istringstream strst(st[i]);
				adjmatrix[i].resize(st.size());
				int j = 0;
				while (strst >> vertice) {
					adjmatrix[i][j] = vertice;
					j++;
				}
			}
		}
			else
			{
				if (type == 'L')
				{
					if (weighted == 0)
						 
					{
						alist.resize(st.size());
						int edge;
						for (int i = 0; i < st.size(); i++) {
							istringstream strst(st[i]);
							while (strst >> edge)
								alist[i].insert(make_pair(i + 1, edge));
						}
					}
					// заполняем список смежности для невзвешенного графа
					else
					{
						awlist.resize(st.size());
						int edge = 0, weight = 0;
						for (int i = 0; i < st.size(); i++) {
							istringstream strst(st[i]);
							while (strst >> edge >> weight)
								awlist[i].insert(make_tuple(i + 1, edge, weight));
						}

					} // заполняем список смежности для взвешенного графа
				}
				else
				{
					if (weighted == 0)
					{
						int from = 0, to = 0;
						for (int i = 0; i < st.size(); i++) {
							istringstream strst(st[i]);
							while (strst >> from >> to)
								edges.insert(make_pair(from, to));
						}
					}
					// инициализируем список ребер для невзвешенного графа
					else
					{
						int from = 0, to = 0, weight = 0;
						for (int i = 0; i < st.size(); i++) {
							istringstream strst(st[i]);
							while (strst >> from >> to >> weight)
								wedges.insert(make_tuple(from, to, weight));
						}
					}// инициализируем список ребер для взвешенного графа
				}
			}
		}
	}

	//void readGraph(std::string fileName)
	//{ 
	//	char buff[50];
	//	ifstream fin(fileName);
	//	fin >> buff;
	//	type = buff[0];
	//	fin >> buff;
	//	N = atoi(buff);
	//	fin >> buff;
	//	orientation = (atoi(buff) == 1);
	//	fin >> buff;
	//	weighted = (atoi(buff) == 1);
	//	if (type == 'C') {
	//		vector < vector <int> > matrix_bff(N, vector <int>(N));
	//		for (int i = 0; i < N; i++) {
	//			for (int j = 0; j < N; j++) {
	//				fin >> buff;
	//				int a = atoi(buff);
	//				if (weighted) matrix_bff[i][j] = a;
	//				else matrix_bff[i][j] = 1;
	//			}
	//		}
	//		fin.close();
	//		matrix = matrix_bff;
	//	}
	//	else if (type == 'L') {
	//		if (!weighted) {
	//			vector <set < int> > awlist_bff(N);
	//			for (int i = 0; i < N; i++) {
	//				set <int> buss;
	//				char line[20000];
	//				if (i==0) fin.getline(line, 20000, '\n');
	//					fin.getline(line,20000,'\n');  
	//					
	//					int t = 1;
	//					int k=0;
	//					for each (char var in line)
	//					{  
	//						if (var!=' ' && var !='\0'){ k += (var - '0')*t;
	//						t++;
	//						}
	//						else { 
	//							buss.insert(k);
	//							t = 1;
	//							k = 0;
	//						}

	//					}
	//	//				buss.insert(k);
	//					awlist_bff[i]=buss;
	//					cout << line<< endl;
	//			}
	//		}
	//	}
	//}	
	void addEdge(int from, int to, int weight)
	{
		if (weighted == 0)
			weight = 1;
		if (type == 'C')
		{
			if (orientation == 1) adjmatrix[from -1 ][to - 1] = weight;
			else
			{
				adjmatrix[from -1 ][to - 1] = weight;
				adjmatrix[to - 1][from - 1 ] = weight;
			}
		}
		else
		{
			if (type == 'L')
			{
				if (weighted == 0) //граф невзвшенный
				{
					alist[from - 1].insert(make_pair(from, to));
					if (orientation == 0)
						alist[to - 1].insert(make_pair(to, from));
				}
				else  // граф взвешенный
				{
					awlist[from - 1].insert(make_tuple(from, to, weight));
					if (orientation == 0)
						awlist[to - 1].insert(make_tuple(to, from, weight));
				}
			}
			else
			{
				if (weighted == 0) //граф невзвешенный
				{
					edges.insert(make_pair(from, to));
					M++;
					if (orientation == 0) { // граф неориентированный
						edges.insert(make_pair(to, from));
						M++;
					}
				}
				else // граф невзвешенный
				{
					wedges.insert(make_tuple(from, to, weight));
					M++;
					if (orientation == 0) { // граф неориентированный
						wedges.insert(make_tuple(to, from, weight));
						M++;
					}
				}
			}
		}
	}
	void removeEdge(int from, int to)
	{
		int weight;
		int a1, a2, a3;
		if (type == 'C')
		{
			if (orientation==1) adjmatrix[from -1 ][to - 1] = 0;
			else
			{
				adjmatrix[from - 1][to - 1 ] = 0;
				adjmatrix[to - 1][from - 1] = 0;
			}
		}
		else
		{
			if (type == 'L')
			{
				if (weighted == 0) // граф невзвешенный
				{
					alist[from - 1].erase(make_pair(from, to));
					if (orientation == 0) // граф неориентированный
					{
						alist[to - 1].erase(make_pair(to, from));
					}
				}
				else // граф взвешенный
				{
					for (set<tuple<int, int, int>>::iterator i = awlist[from - 1].begin(); i != awlist[from - 1].end(); i++)
					{
						tie(a1, a2, a3) = (*i);
						if (a1 == from && a2 == to)
						{
							weight = a3;
							awlist[from - 1].erase(*i);
							break;
						}
					}
					if (orientation == 0) // граф неориентированный
					{
						for (set<tuple<int, int, int>>::iterator i = awlist[to - 1].begin(); i != awlist[to - 1].end(); i++)
						{
							tie(a1, a2, a3) = (*i);
							if (a1 == to && a2 == from)
							{
								awlist[to - 1].erase(*i);
								break;
							}
						}
					}
				}
			}
			else // индикатор = Е
			{
				if (weighted == 0) // граф невзешенный
				{
					edges.erase(make_pair(from, to));
					if (orientation == 0) { // граф неориентированный
						edges.erase(make_pair(to, from));
						M--;
					}
					M--;
				}
				else // граф взвешенный ориентированный
				{
					for (set<tuple<int, int, int>>::iterator i = wedges.begin(); i != wedges.end(); i++)
					{
						tie(a1, a2, a3) = (*i);
						if (a1 == from && a2 == to)
						{
							weight = a3;
							wedges.erase(*i);
							M--;
							break;
						}
					}
					if (orientation == 0) // граф взвешенный неориентированный
						for (set<tuple<int, int, int>>::iterator i = wedges.begin(); i != wedges.end(); i++)
						{
							tie(a1, a2, a3) = (*i);
							if (a1 == to && a2 == from)
							{
								wedges.erase(*i);
								M--;
								break;
							}
						}
				}
			}
		}
	}
	int changeEdge(int from, int to, int newWeight)
	{
		int weight;
		int a1, a2, a3;
		weight = 0;
		if (weighted == 1) //граф взвешенный
		{
			if (type == 'C')
			{    
				weight = adjmatrix[from - 1][to - 1];
				if (orientation == 1) adjmatrix[from][to] = newWeight;
				else
				{
					adjmatrix[from][to] = newWeight;
					adjmatrix[to][from] = newWeight;
				}
			}
			else
			{
				if (type == 'L')
				{
					for (set<tuple<int, int, int>>::iterator i = awlist[from - 1].begin(); i != awlist[from - 1].end(); i++)
					{
						tie(a1, a2, a3) = (*i);
						if (a1 == from && a2 == to)
						{
							weight = a3;
							awlist[from - 1].erase(*i);
							awlist[from - 1].insert(make_tuple(from, to, newWeight));
							break;
						}
					}
					if (orientation == 0) // граф неориентированный
						for (set<tuple<int, int, int>>::iterator i = awlist[to - 1].begin(); i != awlist[to - 1].end(); i++)
						{
							tie(a1, a2, a3) = (*i);
							if (a1 == to && a2 == from)
							{
								awlist[to - 1].erase(*i);
								awlist[to - 1].insert(make_tuple(to, from, newWeight));
								break;
							}
						}
				}
				else // indicator = e/E
				{
					for (set<tuple<int, int, int>>::iterator i = wedges.begin(); i != wedges.end(); i++)
					{
						tie(a1, a2, a3) = (*i);
						if (a1 == from && a2 == to)
						{
							weight = a3;
							wedges.erase(*i);
							wedges.insert(make_tuple(from, to, newWeight));
							break;
						}
					}
					if (orientation == 0) //граф неориентированный
						for (set<tuple<int, int, int>>::iterator i = wedges.begin(); i != wedges.end(); i++)
						{
							tie(a1, a2, a3) = (*i);
							if (a1 == to && a2 == from)
							{
								wedges.erase(*i);
								wedges.insert(make_tuple(to, from, newWeight));
								break;
							}
						}
				}
			}
		}
		return weight;
	}
	void transformToAdjList() {
		if (type == 'C')
		{
			if (weighted == 0)
			{
				set <pair<int, int>> b1;
				alist.clear();
				b1.clear();
				for (int i = 0; i<adjmatrix.size(); i++)
				{
					b1.clear();
					for (int j = 0; j<adjmatrix[i].size(); j++)
					{
						if (adjmatrix[i][j]>0)
						{
							b1.insert(make_pair(i + 1, j + 1));
						}
					}
					alist.push_back(b1);
				}
				adjmatrix.clear();
			}
			else
			{
				set<tuple<int, int, int>> b1;
				awlist.clear();
				b1.clear();
				for (int i = 0; i < adjmatrix.size(); i++)
				{
					b1.clear();
					for (int j = 0; j < adjmatrix[i].size(); j++)
					{
						if (adjmatrix[i][j] > 0)
						{
							b1.insert(make_tuple(i + 1, j + 1, adjmatrix[i][j]));
						}
					}
					awlist.push_back(b1);
				}
				adjmatrix.clear();
			}
		}
		if (type == 'E')
		{
			M = 0;
			if (weighted == 0)  
			{
				set<pair<int, int>> b1;
				alist.clear();
				b1.clear();
				for (int i = 0; i < N; i++)
					alist.push_back(b1);
				for (set<pair<int, int>>::iterator j = edges.begin(); j != edges.end(); j++)
					alist[(*j).first - 1].insert((*j));
				edges.clear();
			}
			else
			{
				int a1, a2, a3;
				set<tuple<int, int, int>> b1;
				awlist.clear();
				b1.clear();
				for (int i = 0; i < N; i++)
					awlist.push_back(b1);
				for (set<tuple<int, int, int>>::iterator j = wedges.begin(); j != wedges.end(); j++)
				{
					tie(a1, a2, a3) = (*j);
					awlist[a1 - 1].insert((*j));
				}
				wedges.clear();
			}
		}
		if (type == 'C' || type == 'E')
			type = 'L';
	}
	void transformToAdjMatrix() {
		if (type == 'L')
		{
			if (weighted == 0)
			{
				vector<int> b1;
				adjmatrix.clear();
				b1.clear();
				for (int i = 0; i < alist.size(); i++)
				{
					b1.clear();
					for (int j = 0; j < alist.size(); j++)
					{
						b1.push_back(0);
					}
					for (set<pair<int, int>>::iterator j = alist[i].begin(); j != alist[i].end(); j++)
					{
						b1[(*j).second - 1] = 1;
					}
					adjmatrix.push_back(b1);
				}
				alist.clear();
			}
			else
			{
				vector<int> b1;
				int a1, a2, a3;
				adjmatrix.clear();
				b1.clear();
				for (int i = 0; i < awlist.size(); i++)
				{
					b1.clear();
					for (int j = 0; j < awlist.size(); j++)
					{
						b1.push_back(0);
					}
					for (set<tuple<int, int, int>>::iterator j = awlist[i].begin(); j != awlist[i].end(); j++)
					{
						tie(a1, a2, a3) = (*j);
						b1[a2 - 1] = a3;
					}
					adjmatrix.push_back(b1);
				}
				awlist.clear();
			}
		}
		if (type == 'E')
		{
			M = 0;
			if (weighted == 0)
			{
				vector<int> b1;
				adjmatrix.clear();
				b1.clear();
				for (int i = 0; i < N; i++)
				{
					b1.clear();
					for (int j = 0; j < N; j++)
					{
						b1.push_back(0);
					}
					adjmatrix.push_back(b1);
				}
				for (set<pair<int, int>>::iterator j = edges.begin(); j != edges.end(); j++)
				{
					adjmatrix[(*j).first - 1][(*j).second - 1] = 1;
					if (orientation == 0)
						adjmatrix[(*j).second - 1][(*j).first - 1] = 1;
				}
				edges.clear();
			}
			else
			{
				vector<int> b1;
				int a1, a2, a3;
				adjmatrix.clear();
				b1.clear();
				for (int i = 0; i<N; i++)
				{
					b1.clear();
					for (int j = 0; j < N; j++)
						b1.push_back(0);
					adjmatrix.push_back(b1);
				}
				for (set<tuple<int, int, int>>::iterator j = wedges.begin(); j != wedges.end(); j++)
				{

					tie(a1, a2, a3) = (*j);
					adjmatrix[a1 - 1][a2 - 1] = a3;
					if (orientation == 0)
						adjmatrix[a2 - 1][a1 - 1] = a3;
				}
				wedges.clear();
			}

		}
		if (type == 'L' || type == 'E')
			type = 'C';
	}
	void transformToListOfEdges() {
		if (type == 'C')
		{
			if (weighted== 0)
			{
				edges.clear();
				M = 0;
				for (int i = 0; i < adjmatrix.size(); i++)
				{
					for (int j = 0; j < adjmatrix[i].size(); j++)
					{
						if (adjmatrix[i][j] > 0)
						{
							M++;
							edges.insert(make_pair(i + 1, j + 1));
						}
					}
				}
				adjmatrix.clear();
			}
			else
			{
				wedges.clear();
				M = 0;
				for (int i = 0; i < adjmatrix.size(); i++)
				{
					for (int j = 0; j < adjmatrix[i].size(); j++)
					{
						if (adjmatrix[i][j] > 0)
						{
							M++;
							wedges.insert(make_tuple(i + 1, j + 1, adjmatrix[i][j]));
						}
					}
				}
				adjmatrix.clear();
			}
		}
		if (type  == 'L')
		{
			if (weighted == 0)
			{
				edges.clear();
				M = 0;
				for (int i = 0; i < alist.size(); i++)
				{
					for (set<pair<int, int>>::iterator j = alist[i].begin(); j != alist[i].end(); j++)
					{
						M++;
						edges.insert((*j));
					}
				}
				alist.clear();
			}
			else
			{
				wedges.clear();
				M = 0;
				for (int i = 0; i < awlist.size(); i++)
				{
					for (set<tuple<int, int, int>>::iterator j = awlist[i].begin(); j != awlist[i].end(); j++)
					{
						M++;
						wedges.insert((*j));
					}
				}
				awlist.clear();
			}
		}

		if (type == 'C' || type == 'L')
			type = 'E';
	}
	void writeGraph(string fileName)
	{
		
		int a1, a2, a3;
		ofstream fout(fileName, ios::out);
		fout << type << " ";
		fout << N;
		if (type == 'E' && orientation == 0)
			fout << " " << M / 2;
		else
			if (type =='E') fout << " " << M;
		fout << endl;
		fout << orientation << " " << weighted<< endl;
		if (type == 'C')
		{
			for (int i = 0; i < adjmatrix.size(); i++)
			{
				//fout << " ";
				for (int j = 0; j < adjmatrix[i].size(); j++)
					if (j != adjmatrix[i].size() - 1)
						fout << adjmatrix[i][j] << " ";
					else
						fout << adjmatrix[i][j] << endl;
				//fout << endl;
			}
		}
		else
		{
			if (type == 'L')
			{
				if (orientation == 0)
				{
					for (int i = 0; i < alist.size(); i++)
					{
						//fout << " ";
						int k = 0;
						for (set<pair<int, int>>::iterator j = alist[i].begin(); j != alist[i].end(); ++j, k++)
							if (k == alist[i].size() - 1)
								fout << (*j).second;
							else
								fout << (*j).second << " ";
						fout << endl;
					}
				}
				else
				{
					for (int i = 0; i < awlist.size(); i++)
					{
						//fout << " ";
						int k = 0;
						for (set<tuple<int, int, int>>::iterator j = awlist[i].begin(); j != awlist[i].end(); j++, k++)
						{
							tie(a1, a2, a3) = (*j);
							if (k == awlist[i].size() - 1)
								fout << a2 << " " << a3;
							else
								fout << a2 << " " << a3 << " ";
						}
						fout << endl;
					}
				}
			}
			else
			{
				if (weighted == 0)
				{
					for (set<pair<int, int>>::iterator i = edges.begin(); i != edges.end(); i++)
						if ((orientation == 0 && (*i).first < (*i).second) || (orientation == 1)) {
							fout << (*i).first << " " << (*i).second << endl;
						}
				}
				else
					for (set<tuple<int, int, int>>::iterator i = wedges.begin(); i != wedges.end(); i++)
					{
						tie(a1, a2, a3) = (*i);
						if ((orientation == 0 && a1 < a2) || (orientation == 1)) {
							fout << a1 << " " << a2 << " " << a3 << endl;
						}
					}

			}
		}
		fout.close();
	}

	Graph getSpaingTreePrima() {
		
		vector<int> visited; // посещ.
		vector<int> left; // не посещ
		int weigthmin;
		Graph bff = Graph(N);
		vector<vector<int>> b;
		int i1, j1;
		char type1;
		type1 = type;
		transformToAdjMatrix();
		b = adjmatrix;
		visited.push_back(1);
		for (int i = 1; i < N; i++)
		{
			left.push_back(i + 1);
		}
		for (int t = 0; t < N - 1; t++)
		{
			weigthmin = 0;
			i1 = -1;
			j1 = -1;
			for (int i = 0; i < visited.size(); i++)
			{
				for (int j = 0; j < left.size(); j++)
				{
					if ((b[visited[i] - 1][left[j] - 1]>0 && weigthmin > b[visited[i] - 1][left[j] - 1]) ||
						(b[visited[i] - 1][left[j] - 1]>0 && weigthmin == 0))
					{
						weigthmin = b[visited[i] - 1][left[j] - 1];
						i1 = i;
						j1 = j;
					}
				}
			}
			b[visited[i1] - 1][left[j1] - 1] = 0;
			b[left[j1] - 1][visited[i1] - 1] = 0;
			bff.addEdge(visited[i1], left[j1], weigthmin);
			visited.push_back(left[j1]);
			left.erase(left.begin() + j1);
		}
		if (type1 == 'L')
		{
			transformToAdjList();
		}
		if (type1 == 'E')
		{
			transformToListOfEdges();
		}
		
		return bff;

	}
	void SortVectorTuple(vector <tuple<int, int, int>> &a)
	{
		vector <tuple<int, int, int>> b;
		int a1, a2, a3;
		int weigthmax;
		int i1;
		b.clear();
		while (a.size()>0)
		{
			tie(a1, a2, a3) = a[0];
			weigthmax = a3;
			i1 = 0;
			for (int i = 0; i<a.size(); i++)
			{
				tie(a1, a2, a3) = a[i];
				if (weigthmax<a3)
				{
					i1 = i;
					weigthmax = a3;
				}
			}
			b.push_back(a[i1]);
			a.erase(a.begin() + i1);
		}
		a.clear();
		for (int i = 0; i<b.size(); i++)
		{
			a.push_back(b[i]);
		}
	}

	Graph getSpaingTreeKruscal() {
		DSU b = DSU(N);
		Graph bff = Graph(N);
		vector <tuple<int, int, int>> edg;
		tuple<int, int, int> q;
		int a1, a2, a3;
		int i1;
		char type1;
		type1 = type;
		transformToAdjMatrix();
		for (int i = 0; i < N; i++)
		{
			for (int j = i; j < N; j++)
			{
				if (adjmatrix[i][j] != 0)
				{
					edg.push_back(make_tuple(i + 1, j + 1, adjmatrix[i][j]));
				}
			}
		}
		SortVectorTuple(edg);
		i1 = 0;
		while (i1 < N - 1 && edg.size() > 0)
		{
			tie(a1, a2, a3) = edg[edg.size() - 1];
			edg.pop_back();
			if (b.find(a1) != b.find(a2))
			{
				i1++;
				bff.addEdge(a1, a2, a3);
				b.unite(a1, a2);
			}
		}
		if (type1 == 'L')
		{
			transformToAdjList();
		}
		if (type1 == 'E')
		{
			transformToListOfEdges();
		}
		return bff;
	}

	void MinEdge(set <tuple<int, int, int>> a, tuple<int, int, int> &w)
	{
		tuple<int, int, int> b;
		int a1, a2, a3;
		int weigthmin;
		tie(a1, a2, a3) = (*a.begin());
		b = (*a.begin());
		weigthmin = a3;
		for (set <tuple<int, int, int>>::iterator i = a.begin(); i != a.end(); i++)
		{
			tie(a1, a2, a3) = (*i);
			if (weigthmin>a3)
			{
				b = (*i);
				weigthmin = a3;
			}
		}
		w = b;
	}
	Graph getSpaingTreeBoruvka() {
		DSU b = DSU(N);
		Graph bff = Graph(N);
		char type1;
		type1 = type;
		transformToAdjList();
		vector <set<tuple<int, int, int>>> Edges;
		vector <tuple<int, int, int>> cheapestEdge;
		set<tuple<int, int, int>> s1, s2;
		set<tuple<int, int, int>> s;
		tuple<int, int, int> u;
		int a1, a2, a3;
		int i1;
		int u1, u2;
		int q;
		for (int i = 0; i<N; i++)
		{
			Edges.push_back(awlist[i]);
		}
		i1 = 0;
		while (i1<N - 1)
		{
			for (int i = 0; i<N; i++)
			{
				if (!Edges[i].empty())
				{
					MinEdge(Edges[i], u);
					cheapestEdge.push_back(u);
				}
			}
			SortVectorTuple(cheapestEdge);
			while (i1<N - 1 && cheapestEdge.size()>0)
			{
				tie(a1, a2, a3) = cheapestEdge[cheapestEdge.size() - 1];
				cheapestEdge.pop_back();
				if (b.find(a1) != b.find(a2))
				{
					i1++;
					u1 = b.find(a1);
					u2 = b.find(a2);
					bff.addEdge(a1, a2, a3);
					b.unite(a1, a2);
					q = b.find(u1);
					s.clear();
					s1.clear();
					s2.clear();
					s1 = Edges[u1 - 1];
					s2 = Edges[u2 - 1];
					Edges[u1 - 1].clear();
					Edges[u2 - 1].clear();
					for (set<tuple<int, int, int>>::iterator i = s1.begin(); i != s1.end(); i++)
					{
						tie(a1, a2, a3) = (*i);
						if (b.find(a1) != b.find(a2))
						{
							s.insert((*i));
						}
					}
					for (set<tuple<int, int, int>>::iterator i = s2.begin(); i != s2.end(); i++)
					{
						tie(a1, a2, a3) = (*i);
						if (b.find(a1) != b.find(a2))
						{
							s.insert((*i));
						}
					}
					Edges[q - 1] = s;
				}
			}
		}


		if (type1 == 'C')
		{
			transformToAdjMatrix();
		}
		if (type1 == 'E')
		{
			transformToListOfEdges();
		}
		return bff;
	}


};
  

int main()
{
	//Graph ver;
	//ver.readGraph("input.txt");
	
	Graph g;
	g.readGraph("input.txt");
 //   g.addEdge(2, 0, 3);
//	g.changeEdge(1, 2, 6);
//	g.removeEdge(0, 1);
	Graph b = g.getSpaingTreeKruscal();
    b.writeGraph("output.txt");
	
	
	return 0;
}