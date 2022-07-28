#include"MyStack.hpp"
#include<Windows.h>

#define ROW 11
#define COL 11
enum dir
{
	p_up,p_left,p_down,p_right
};
//������ͼ
struct pathnode
{
	int dir;	//����
	bool isfind;	//��¼�Ƿ��߹�
};
//����
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
	
	//��� �յ� ������ͼ ��ʼ��
	point begin;
	point end;
	begin.x = begin.y = 1;
	end.x = 7;
	end.y = 9;
	pathnode pathmap[ROW][COL]={0};//Ĭ���������� 
	//׼�� ջ
	MyStack<point> stack;
	stack.push_stack(begin);					//�����ջ
	pathmap[begin.x][begin.y].isfind = true;	//����߹�

	point cur = begin;
	point search = cur;	//��̽��

	bool isFind = false;

	while (true)
	{
		search = cur;
		switch (pathmap[cur.x][cur.y].dir)
		{
		case p_up:
			search.x--;
			//�ж��ܲ�����
			if (pathmap[search.x][search.y].isfind == false 
				&& map[search.x][search.y] == 0)//������
			{
				pathmap[cur.x][cur.y].dir++;		//�ı䷽��,��ǵ�ǰ�������߹�,�´β���������
				cur = search;						//��
				stack.push_stack(cur);				//��ջ
				pathmap[cur.x][cur.y].isfind = true;//��ǵ�ǰ���߹�
			}
			else//������
			{
				pathmap[cur.x][cur.y].dir++;		//�߲�ͨ,�ı䷽��
			}

			break;
		case p_left:
			search.y--;
			//�ж��ܲ�����
			if (pathmap[search.x][search.y].isfind == false
				&& map[search.x][search.y] == 0)//������
			{
				pathmap[cur.x][cur.y].dir++;		//�ı䷽��,��ǵ�ǰ�������߹�,�´β���������
				cur = search;						//��
				stack.push_stack(cur);				//��ջ
				pathmap[cur.x][cur.y].isfind = true;//��ǵ�ǰ���߹�
			}
			else//������
			{
				pathmap[cur.x][cur.y].dir++;		//�߲�ͨ,�ı䷽��
			}

			break;
		case p_down:
			search.x++;
			//�ж��ܲ�����
			if (pathmap[search.x][search.y].isfind == false
				&& map[search.x][search.y] == 0)//������
			{
				pathmap[cur.x][cur.y].dir++;		//�ı䷽��,��ǵ�ǰ�������߹�,�´β���������
				cur = search;						//��
				stack.push_stack(cur);				//��ջ
				pathmap[cur.x][cur.y].isfind = true;//��ǵ�ǰ���߹�
			}
			else//������
			{
				pathmap[cur.x][cur.y].dir++;		//�߲�ͨ,�ı䷽��
			}

			break;
		case p_right:
			search.y++;
			//�ж��ܲ�����
			if (pathmap[search.x][search.y].isfind == false
				&& map[search.x][search.y] == 0)//������
			{
				pathmap[cur.x][cur.y].dir++;		//�ı䷽��,��ǵ�ǰ�������߹�,�´β���������
				cur = search;						//��
				stack.push_stack(cur);				//��ջ
				pathmap[cur.x][cur.y].isfind = true;//��ǵ�ǰ���߹�
			}
			else//������
			{
				stack.pop_stack();					//�ĸ������߲�ͨ,���˵���һ������
				cur = stack.stack_top();
			}

			break;
		case 4://�ĸ����򶼱���߹���,dir�ӵ���4
			stack.pop_stack();			
			cur = stack.stack_top();
			break;

		}//end of switch
		printmap(map, cur);
		Sleep(100);

		if (cur == end)//��ǰ�� = �յ� �ҵ���
		{
			isFind = true;
			break;
		}
		if (stack.empty())//�ѱ���û�ҵ�
		{
			break;
		}
	}

	if (isFind == true)//�ҵ��յ�  ��ӡ·��
	{
		printf("�ҵ��յ���!!!\nPATH:");
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
	else//û�ҵ�
		printf("û�ҵ�!!!\n");

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
				printf("ǽ");
			if (i == cur.x && j == cur.y)
				printf("��");
			else if (p[i][j] == 0)
				printf("  ");
		}
		printf("\n");
	}
}



