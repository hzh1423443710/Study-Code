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
	//��ʼ����ͼ
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

	//��ʼ�� ����յ�
	MyPoint begin(1,1);
	MyPoint end(12,14);
	drawGame(map, begin, end);
	inputPoint(begin, end);
	drawGame(map, begin, end);

	//��ʼ�� ������ͼ �Ƿ��ҵ�
	bool pathmap[ROW][COL] = { false };
	bool isFind = false;		

	MyVector<treenode*> curlayer;					//��ǰ��
	MyVector<treenode*> nextlayer;					//��һ�� ���ڱ���

	treenode* proot = createTreeNode(begin);		//��� ����
	pathmap[proot->point.x][proot->point.y] = true;	//�������߹�
	curlayer.push_back(proot);
	treenode* ptemp=nullptr;						//��ʱ����
	while (true)
	{
		nextlayer.clear();
		for (int i = 0; i < curlayer.size(); i++)//������ǰ��
		{
			for (int dir = 0; dir < 4; dir++)//ÿ���ڵ㶼���ĸ��������ѡ��-->�ж��Ǹ���������,������
			{
				ptemp = createTreeNode(curlayer[i]->point);//temp=��ǰ��
				switch (dir)
				{
					case p_up:		ptemp->point.x--;break;
					case p_left:	ptemp->point.y--;break;
					case p_down:	ptemp->point.x++;break;
					case p_right:	ptemp->point.y++;break;
				}
				//�ж� �ܲ�����
				if (canwalk(map, ptemp, pathmap))//���� 
				{
					pathmap[ptemp->point.x][ptemp->point.y] = true;//����߹� 
					ptemp->parent = curlayer[i];					//��ֵ ���ӵ�parent
					curlayer[i]->child.push_back(ptemp);			//���� ��Ϊ��ǰ��ĺ���(����)
					nextlayer.push_back(ptemp);

					if (ptemp->point == end)//�ҵ���
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


			}//end of for2 �Ե�ǰ���ÿһ���ڵ��ĸ������ж�
			if (isFind) break;

		}//end of for1 ������ǰ��
		if (isFind || nextlayer.size() == 0)//1.�ҵ���  2.������Ҳû�ҵ�
			break;
		else
			curlayer = nextlayer;			//������,����һ��
	}//end of while (true)

	if (isFind)//�ҵ���
	{
		cout << "�ҵ��յ���!!!" << endl << "���·��:";
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
		cout << "û�ҵ��յ�!!!";
	}
	cout << endl;
	cout << "�����������."<<endl;
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
	//���
	putimage(begin.y * gap, begin.x * gap, img + 7, SRCAND);
	putimage(begin.y * gap, begin.x * gap, img + 6, SRCPAINT);
	//�յ�
	putimage(end.y * gap, end.x * gap, img + 3, SRCAND);
	putimage(end.y * gap, end.x * gap, img + 2, SRCPAINT);
}

void inputPoint(MyPoint& begin, MyPoint& end)
{
	MessageBox(hwnd, L"�����������յ�(15��15,1~15)", L"��ʾ", MB_OK);
	WCHAR arr[10];
	InputBox(arr, 10, L"���(��ʽ:2,2)(��Ҫ���뵽�ϰ�����):");
	int x, y;
	swscanf_s(arr, L"%d,%d", &x, &y);
	begin.x = x-1;
	begin.y = y-1;
	InputBox(arr, 10, L"�յ�(��ʽ:13,15)(��Ҫ���뵽�ϰ�����):");
	swscanf_s(arr, L"%d,%d", &x, &y);
	end.x = x-1;
	end.y = y-1;
	cout << "���:" << begin << endl << "�յ�" << end << endl;
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
	//������
	//1.Խ�� ���ڵ�ͼ��Χ��
	if (ptemp->point.x > ROW-1 || ptemp->point.x<0 || ptemp->point.y>ROW-1 || ptemp->point.y < 0)
		return false;
	//2.���ϰ���
	if (1 == map[ptemp->point.x][ptemp->point.y])
		return false;
	//3.�߹��� 
	if (path[ptemp->point.x][ptemp->point.y]==true)
		return false;
	//����
	return true;
}
