#include"MyVector.hpp"

#define ROW 15
#define COL 15

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

int main()
{
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
		{ 1,  1,  0,  1,  0,  0,  0,  1,  0,  1,  0,  0,  0,  0,  0 },
		{ 0,  0,  0,  0,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0 },
		{ 0,  1,  1,  1,  1,  1,  0,  1,  0,  1,  0,  0,  0,  1,  0 },
		{ 0,  1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  1,  0,  1,  1 },
		{ 0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  1,  1,  0,  0,  0 }
	};
	//初始化 起点终点
	MyPoint begin(2,4);
	MyPoint end(12,14);
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
		printf("找到了!!!");
		while (ptemp) {
			cout << "(" << ptemp->point.x << "," << ptemp->point.y<< ")";
			ptemp = ptemp->parent;
		}
	}
	else
	{
		printf("没找到!!!");
	}

	cout << endl;
	return 0;
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
