#include"MyVector.hpp"
#include<graphics.h>
#include<string>

#define ROW 15
#define COL 15
#define gap 50

IMAGE img[8];
HWND hwnd;

enum dir
{
	p_up,p_left,p_down,p_right
};
struct MyPoint
{
	int x;
	int y;
	friend ostream& operator<<(ostream& output,const MyPoint& t)
	{
		output << "<" << t.x << "," << t.y << ">"<<",";
		return output;
	}
	bool operator==(const MyPoint & t)
	{
		if (x == t.x  && y == t.y)
			return true;
		return false;
	}
	MyPoint() { x = y = 0; };
	MyPoint(int x,int y):x(x),y(y){}
};

struct treenode
{
	MyPoint point;
	treenode* parent;
	MyVector<treenode*> child;
};

treenode* createTreeNode(const MyPoint& point);

bool canwalk(int map[ROW][COL], treenode* ptemp, bool path[ROW][COL]);
void InitGame();
void drawGame(int map[ROW][COL], const MyPoint& begin,const MyPoint&end);
void inputPoint(MyPoint& begin, MyPoint& end);

int main()
{
	InitGame();
	//初始化地图
	int map[ROW][COL] =
	{
		{ 1,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1,  1,  0,  0,  0 },
		{ 0,  0,  1,  0,  0,  1,  0,  0,  0,  0,  0,  1,  0,  1,  0 },
		{ 0,  1,  1,  1,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  1 },
		{ 0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  1,  0,  1,  0 },
		{ 0,  0,  1,  0,  0,  0,  0,  1,  0,  0,  1,  1,  0,  0,  0 },
		{ 0,  1,  1,  0,  1,  0,  1,  1,  1,  0,  0,  0,  1,  1,  0 },
		{ 0,  0,  0,  1,  1,  0,  0,  1,  0,  0,  1,  0,  1,  0,  0 },
		{ 1,  0,  1,  0,  0,  0,  0,  1,  0,  0,  1,  0,  0,  0,  0 },
		{ 1,  0,  1,  0,  0,  1,  1,  1,  0,  0,  1,  0,  0,  1,  1 },
		{ 1,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0 },
		{ 1,  1,  0,  1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0 },
		{ 0,  0,  0,  0,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0 },
		{ 0,  1,  1,  1,  1,  1,  0,  1,  0,  1,  0,  0,  0,  1,  0 },
		{ 0,  1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  1,  0,  1,  1 },
		{ 0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  1,  1,  0,  0,  0 }
	};

	//初始化 起点终点
	MyPoint begin(1,1);
	MyPoint end(12,14);
	drawGame(map, begin, end);
	inputPoint(begin, end);
	drawGame(map, begin, end);

	//初始化 辅助地图 是否找到
	bool pathmap[ROW][COL] = { false };
	bool isFind = false;		

	MyVector<treenode*> curlayer;					//当前层
	MyVector<treenode*> nextlayer;					//下一层 用于遍历

	treenode* proot = createTreeNode(begin);		//起点 入树
	pathmap[proot->point.x][proot->point.y] = true;	//标记起点走过
	curlayer.push_back(proot);
	treenode* ptemp=nullptr;						//临时变量
	while (true)
	{
		nextlayer.clear();
		for (int i = 0; i < curlayer.size(); i++)//遍历当前层
		{
			for (int dir = 0; dir < 4; dir++)//每个节点都有四个方向可以选择-->判断那个方向能走,不能走
			{
				ptemp = createTreeNode(curlayer[i]->point);//temp=当前点
				switch (dir)
				{
					case p_up:		ptemp->point.x--;break;
					case p_left:	ptemp->point.y--;break;
					case p_down:	ptemp->point.x++;break;
					case p_right:	ptemp->point.y++;break;
				}
				//判断 能不能走
				if (canwalk(map, ptemp, pathmap))//能走 
				{
					pathmap[ptemp->point.x][ptemp->point.y] = true;//标记走过 
					ptemp->parent = curlayer[i];					//赋值 孩子的parent
					curlayer[i]->child.push_back(ptemp);			//能走 作为当前层的孩子(依次)
					nextlayer.push_back(ptemp);

					if (ptemp->point == end)//找到了
					{
						isFind = true;
						break;
					}
				}
				else
				{
					delete ptemp;
					ptemp = nullptr;
				}


			}//end of for2 对当前层的每一个节点四个方向判断
			if (isFind) break;

		}//end of for1 遍历当前层
		if (isFind || nextlayer.size() == 0)//1.找到了  2.找完了也没找到
			break;
		else
			curlayer = nextlayer;			//继续找,到下一层
	}//end of while (true)

	if (isFind)//找到了
	{
		cout << "找到终点了!!!" << endl << "最短路径:";
		while (ptemp) {
			cout << "<" << ptemp->point.x << "," << ptemp->point.y<< ">"<<",";
			putimage(ptemp->point.y * gap, ptemp->point.x * gap, img + 4, SRCAND);
			putimage(ptemp->point.y * gap, ptemp->point.x * gap, img + 5, SRCPAINT);
			Sleep(100);
			ptemp = ptemp->parent;
		}
	}
	else
	{
		cout << "没找到终点!!!";
	}
	cout << endl;
	cout << "按任意键结束."<<endl;
	getchar();
	return 0;
}

void InitGame()
{
	hwnd=initgraph(ROW * gap, COL * gap, 1);
	MoveWindow(hwnd, 0,0 ,ROW*gap+12, COL*gap+35,true);
	cleardevice();
	loadimage(img + 0, L"./res/0.png", gap, gap);
	loadimage(img + 1, L"./res/1.png", gap, gap);
	loadimage(img + 2, L"./res/2.png", gap, gap);
	loadimage(img + 3, L"./res/3.png", gap, gap);
	loadimage(img + 4, L"./res/4.png", gap, gap);
	loadimage(img + 5, L"./res/5.png", gap, gap);
	loadimage(img + 6, L"./res/6.png", gap, gap);
	loadimage(img + 7, L"./res/7.png", gap, gap);
}

void drawGame(int map[ROW][COL], const MyPoint& begin, const MyPoint& end)
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j] == 1)
				putimage(j * gap, i * gap, img + 1);
			if (map[i][j] == 0)
				putimage(j * gap, i * gap, img + 0);
		}
	}
	//起点
	putimage(begin.y * gap, begin.x * gap, img + 7, SRCAND);
	putimage(begin.y * gap, begin.x * gap, img + 6, SRCPAINT);
	//终点
	putimage(end.y * gap, end.x * gap, img + 3, SRCAND);
	putimage(end.y * gap, end.x * gap, img + 2, SRCPAINT);
}

void inputPoint(MyPoint& begin, MyPoint& end)
{
	MessageBox(hwnd, L"请输入起点和终点(15×15,1~15)", L"提示", MB_OK);
	WCHAR arr[10];
	InputBox(arr, 10, L"起点(格式:2,2)(不要输入到障碍物上):");
	int x, y;
	swscanf_s(arr, L"%d,%d", &x, &y);
	begin.x = x-1;
	begin.y = y-1;
	InputBox(arr, 10, L"终点(格式:13,15)(不要输入到障碍物上):");
	swscanf_s(arr, L"%d,%d", &x, &y);
	end.x = x-1;
	end.y = y-1;
	cout << "起点:" << begin << endl << "终点" << end << endl;
}

treenode* createTreeNode(const MyPoint& point)
{
	treenode* p = new treenode;
	memset(p, 0, sizeof(treenode));
	p->point.x = point.x;
	p->point.y = point.y;
	return p;
}

bool canwalk(int map[ROW][COL], treenode* ptemp, bool path[ROW][COL])
{
	//不能走
	//1.越界 不在地图范围内
	if (ptemp->point.x > ROW-1 || ptemp->point.x<0 || ptemp->point.y>ROW-1 || ptemp->point.y < 0)
		return false;
	//2.是障碍物
	if (1 == map[ptemp->point.x][ptemp->point.y])
		return false;
	//3.走过的 
	if (path[ptemp->point.x][ptemp->point.y]==true)
		return false;
	//能走
	return true;
}
