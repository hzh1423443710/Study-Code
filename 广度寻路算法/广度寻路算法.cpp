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
		{ 1,  1,  0,  1,  0,  0,  0,  1,  0,  1,  0,  0,  0,  0,  0 },
		{ 0,  0,  0,  0,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0 },
		{ 0,  1,  1,  1,  1,  1,  0,  1,  0,  1,  0,  0,  0,  1,  0 },
		{ 0,  1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  1,  0,  1,  1 },
		{ 0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  1,  1,  0,  0,  0 }
	};
	//��ʼ�� ����յ�
	MyPoint begin(2,4);
	MyPoint end(12,14);
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
		printf("�ҵ���!!!");
		while (ptemp) {
			cout << "(" << ptemp->point.x << "," << ptemp->point.y<< ")";
			ptemp = ptemp->parent;
		}
	}
	else
	{
		printf("û�ҵ�!!!");
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
