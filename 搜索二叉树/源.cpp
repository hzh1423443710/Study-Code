#include"MyTree.h"


int main()
{
	//int arr[] = { 12,5,18,2,9,15,19,17,16 };
	//int arr[] = { 61,59,87,47,73,98,35,51,93,37 };
	int arr[] = { 5,3,7,1,4,6,8,0,2,10,9,1 };
	int n = sizeof(arr) / sizeof(arr[0]);
	MyTree<int> tree;
	for (int i = 0; i < n; i++)
		tree.Insert(arr[i]);

	tree.travel(tree.PreOrder);
	tree.travel(tree.MidOrder);
	tree.travel(tree.PostOrder);
	cout << "----------------" << endl;
	for (int i = 0; i < n; i++)
	{
		tree.PopNode(arr[i]);
		tree.travel(tree.PreOrder);
		cout << endl;
	}
	
	//while(tree._Poproot());
	
#if 0
	for (int i = 0; i < n; i++)
		tree.PopNode(arr[i]);
#endif
	return 0;
}