#pragma once
#include<iostream>
using namespace std;

//搜索二叉树  根>左  根<右

//树节点
template<class T>
struct TreeNode
{
	T val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(const T& val):val(val)
	{
		left = right = nullptr;
	}
};

template<class T>
class MyTree
{
public:
	enum TravelType { PreOrder, MidOrder, PostOrder };
public:
	MyTree();
	~MyTree();
	void Insert(const T& val) ;						//插入
	void travel(TravelType type =PreOrder)const;	//遍历
	TreeNode<T>* find(const T& val);				//查找
	bool PopNode(const T& val);						//删除
	bool _Poproot();								//删根
private:
	TreeNode<T>* root;
private:
	//插入
	void _insert(const T& val, TreeNode<T>** root);
	//遍历
	void _PreOrder(TreeNode<T>* root)const;
	void _MidOrder(TreeNode<T>* root)const;
	void _PostOrder(TreeNode<T>* root)const;
	//查找
	TreeNode<T>* _find(const T& val,TreeNode<T>* root);
	//删除
	bool _PopNode(const T& val, TreeNode<T>* root);
	//析构
	void _delete(TreeNode<T>* root);
};

template<class T>
MyTree<T>::MyTree()
{
	root = nullptr;
}

template<class T>
MyTree<T>::~MyTree()
{
	//1.后序 左右根
	//_delete(root);
	//2.一直删根 直到为空
	while (_Poproot());
}

//遍历
template<class T>
void MyTree<T>::travel(TravelType type) const
{
	switch (type)
	{
	case PreOrder:cout << "前序:"; _PreOrder(root); cout << endl;
		break;
	case MidOrder:cout << "中序:"; _MidOrder(root); cout << endl;
		break;
	case PostOrder:cout << "后序:"; _PostOrder(root); cout << endl;
		break;
	default:
		break;
	}
}

//插入
template<class T>
void MyTree<T>::Insert(const T& val)
{
	_insert(val, &root);
}

template<class T>
void MyTree<T>::_insert(const T& val, TreeNode<T>** root)
{
	if (root == nullptr) return;
	if (nullptr == (*root))//空树
	{
		*root = new TreeNode<T>(val);
		return;
	}

	if (val >= (*(root))->val)//右边插 大于等于右边插
	{
		_insert(val, &((*(root))->right));
		return;
	}
	_insert(val, &((*(root))->left));//左边插

}

//前序
template<class T>
void MyTree<T>::_PreOrder(TreeNode<T>* root) const
{
	if (root == nullptr)
		return;
	cout << root->val << " ";
	_PreOrder(root->left);
	_PreOrder(root->right);
}

//中序
template<class T>
void MyTree<T>::_MidOrder(TreeNode<T>* root)const
{
	if (root == nullptr)
		return;
	_MidOrder(root->left);
	cout << root->val << " ";
	_MidOrder(root->right);
}

//后序
template<class T>
void MyTree<T>::_PostOrder(TreeNode<T>* root)const
{
	if (root == nullptr)
		return;
	_PostOrder(root->left);
	_PostOrder(root->right);
	cout << root->val << " ";
}

//查找
template<class T>
TreeNode<T>* MyTree<T>::find(const T& val)
{
	return _find(val,root);
}

template<class T>
TreeNode<T>* MyTree<T>::_find(const T& val,TreeNode<T>* root)
{
	if (root == nullptr)//空树
		return nullptr;

	if (val == root->val)
		return root;

	if (val > root->val)
	{
		return _find(val,root->right);	
	}
	else
	{
		return _find(val, root->left);
	}
	return nullptr;//没找到

}

//删除
template<class T>
bool MyTree<T>::PopNode(const T& val)
{
	return _PopNode(val, root);
}

template<class T>
bool MyTree<T>::_PopNode(const T& val, TreeNode<T>* root)
{
	if (root == nullptr)//空树
		return false;
	auto pdel = _find(val, root);
	if (pdel == nullptr)//没找到要删的数据
		return false;

	//删除根节点 规则:左树插到右树最左节点
	if (pdel == this->root)
	{
		if (pdel->right == nullptr)//根右为空
		{
			this->root= pdel->left;
			delete pdel;
			return true;
		}
		else//根右不为空
		{
			auto ptemp = pdel->right;
			while (ptemp->left)
			{
				ptemp = ptemp->left;
			}
			ptemp->left = pdel->left;
			this->root = pdel->right;
			delete pdel;
			return true;
		}
	}

	//删除其他节点
	auto prevdel = root; //找到pdel的父节点
	while (prevdel)
	{
		if (prevdel->val < pdel->val)
		{
			if (prevdel->right->val == pdel->val)
				break;
			prevdel = prevdel->right;

		}
		else
		{
			if (prevdel->left->val == pdel->val)
				break;
			prevdel = prevdel->left;
		}
	}

	if (pdel->right) //pdel 的左树 接到 右树(非空)的最小左节点上
	{
		auto ptemp = pdel->right;
		while (ptemp->left)
		{
			ptemp = ptemp->left;
		}
		ptemp->left = pdel->left;
	}

	if (prevdel->left == pdel)//父节点的左节点是pdel
	{
		if (pdel->right)//pdel右节点不为空
			prevdel->left = pdel->right;
		else
			prevdel->left = pdel->left;
		delete pdel;
		return true;
	}
	else//父节点的右节点是pdel
	{
		if (pdel->right)
			prevdel->right = pdel->right;
		else
			prevdel->right = pdel -> left;
		delete pdel;
		return true;
	}

}

//析构用
template<class T>
void MyTree<T>::_delete(TreeNode<T>* root)
{
	//后序删除节根点
	if (root == nullptr)
		return;
	_delete(root->left);
	_delete(root->right);
	delete root;
	root = nullptr;
}
//删根
template<class T>
bool MyTree<T>::_Poproot()
{
	if (root == nullptr)//空树
		return false;

	//删除根节点 规则:左树插到右树最左节点
	auto pdel = root;
	
	if (pdel->right == nullptr)//根右为空
	{
		this->root = pdel->left;
		delete pdel;
		return true;
	}
	else//根右不为空
	{
		auto ptemp = pdel->right;
		while (ptemp->left)
		{
			ptemp = ptemp->left;
		}
		ptemp->left = pdel->left;
		this->root = pdel->right;
		delete pdel;
		return true;
	}

}
