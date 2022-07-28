#include"MyStack.hpp"
#include<Windows.h>

#define ROW 11
#define COL 11
enum dir
{
	p_up,p_left,p_down,p_right
};
//辅助地图
struct pathnode
{
	int dir;	//方向
	bool isfind;	//记录是否走过
};
//坐标
struct point
{
	int x;
	int y;
	bool operator==(const point& p)
	{
		if (x == p.x && y == p.y)
			return true;
		else
			return false;
	}
	friend ostream& operator<<(ostream& output, const point& t)
	{
		output << "<" << t.x << "," << t.y << ">"<<",";
		return output;
	}
};

void printmap(int(*p)[ROW], point& cur);

int main()
{
	int map[ROW][COL] =
	{
	{ 1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,1,0,0,0,1,0,1,1 },
	{ 1,0,1,1,1,1,0,0,0,0,1 },
	{ 1,0,0,1,0,0,0,1,0,1,1 },
	{ 1,1,0,0,0,1,0,1,1,1,1 },
	{ 1,0,0,1,0,1,0,0,0,0,1 },
	{ 1,1,0,1,0,1,1,1,0,1,1 },
	{ 1,0,0,0,0,0,0,1,0,0,1 },
	{ 1,0,1,1,0,1,0,1,0,1,1 },
	{ 1,0,1,0,0,1,0,0,1,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1 }
	};
	
	//起点 终点 辅助地图 初始化
	point begin;
	point end;
	begin.x = begin.y = 1;
	end.x = 7;
	end.y = 9;
	pathnode pathmap[ROW][COL]={0};//默认先往上走 
	//准备 栈
	MyStack<point> stack;
	stack.push_stack(begin);					//起点入栈
	pathmap[begin.x][begin.y].isfind = true;	//标记走过

	point cur = begin;
	point search = cur;	//试探点

	bool isFind = false;

	while (true)
	{
		search = cur;
		switch (pathmap[cur.x][cur.y].dir)
		{
		case p_up:
			search.x--;
			//判断能不能走
			if (pathmap[search.x][search.y].isfind == false 
				&& map[search.x][search.y] == 0)//可以走
			{
				pathmap[cur.x][cur.y].dir++;		//改变方向,标记当前点向上走过,下次不会再走了
				cur = search;						//走
				stack.push_stack(cur);				//入栈
				pathmap[cur.x][cur.y].isfind = true;//标记当前点走过
			}
			else//不能走
			{
				pathmap[cur.x][cur.y].dir++;		//走不通,改变方向
			}

			break;
		case p_left:
			search.y--;
			//判断能不能走
			if (pathmap[search.x][search.y].isfind == false
				&& map[search.x][search.y] == 0)//可以走
			{
				pathmap[cur.x][cur.y].dir++;		//改变方向,标记当前点向上走过,下次不会再走了
				cur = search;						//走
				stack.push_stack(cur);				//入栈
				pathmap[cur.x][cur.y].isfind = true;//标记当前点走过
			}
			else//不能走
			{
				pathmap[cur.x][cur.y].dir++;		//走不通,改变方向
			}

			break;
		case p_down:
			search.x++;
			//判断能不能走
			if (pathmap[search.x][search.y].isfind == false
				&& map[search.x][search.y] == 0)//可以走
			{
				pathmap[cur.x][cur.y].dir++;		//改变方向,标记当前点向上走过,下次不会再走了
				cur = search;						//走
				stack.push_stack(cur);				//入栈
				pathmap[cur.x][cur.y].isfind = true;//标记当前点走过
			}
			else//不能走
			{
				pathmap[cur.x][cur.y].dir++;		//走不通,改变方向
			}

			break;
		case p_right:
			search.y++;
			//判断能不能走
			if (pathmap[search.x][search.y].isfind == false
				&& map[search.x][search.y] == 0)//可以走
			{
				pathmap[cur.x][cur.y].dir++;		//改变方向,标记当前点向上走过,下次不会再走了
				cur = search;						//走
				stack.push_stack(cur);				//入栈
				pathmap[cur.x][cur.y].isfind = true;//标记当前点走过
			}
			else//不能走
			{
				stack.pop_stack();					//四个方向都走不通,回退到上一个坐标
				cur = stack.stack_top();
			}

			break;
		case 4://四个方向都标记走过了,dir加到了4
			stack.pop_stack();			
			cur = stack.stack_top();
			break;

		}//end of switch
		printmap(map, cur);
		Sleep(100);

		if (cur == end)//当前点 = 终点 找到了
		{
			isFind = true;
			break;
		}
		if (stack.empty())//搜遍了没找到
		{
			break;
		}
	}

	if (isFind == true)//找到终点  打印路径
	{
		printf("找到终点了!!!\nPATH:");
		MyStack<point>  temp;
		while (!stack.empty())
		{
			temp.push_stack(stack.stack_top());
			stack.pop_stack();
		}

		while (!temp.empty())
		{
			cout << temp.stack_top();
			temp.pop_stack();
		}
		cout << endl;
	}
	else//没找到
		printf("没找到!!!\n");

	return 0;
}

void printmap(int(*p)[ROW],point& cur)
{
	system("cls");
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (p[i][j] == 1)
				printf("墙");
			if (i == cur.x && j == cur.y)
				printf("人");
			else if (p[i][j] == 0)
				printf("  ");
		}
		printf("\n");
	}
}



