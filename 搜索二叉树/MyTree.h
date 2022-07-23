#pragma once
#include<iostream>
using namespace std;

//����������  ��>��  ��<��

//���ڵ�
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
	void Insert(const T& val) ;						//����
	void travel(TravelType type =PreOrder)const;	//����
	TreeNode<T>* find(const T& val);				//����
	bool PopNode(const T& val);						//ɾ��
	bool _Poproot();								//ɾ��
private:
	TreeNode<T>* root;
private:
	//����
	void _insert(const T& val, TreeNode<T>** root);
	//����
	void _PreOrder(TreeNode<T>* root)const;
	void _MidOrder(TreeNode<T>* root)const;
	void _PostOrder(TreeNode<T>* root)const;
	//����
	TreeNode<T>* _find(const T& val,TreeNode<T>* root);
	//ɾ��
	bool _PopNode(const T& val, TreeNode<T>* root);
	//����
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
	//1.���� ���Ҹ�
	//_delete(root);
	//2.һֱɾ�� ֱ��Ϊ��
	while (_Poproot());
}

//����
template<class T>
void MyTree<T>::travel(TravelType type) const
{
	switch (type)
	{
	case PreOrder:cout << "ǰ��:"; _PreOrder(root); cout << endl;
		break;
	case MidOrder:cout << "����:"; _MidOrder(root); cout << endl;
		break;
	case PostOrder:cout << "����:"; _PostOrder(root); cout << endl;
		break;
	default:
		break;
	}
}

//����
template<class T>
void MyTree<T>::Insert(const T& val)
{
	_insert(val, &root);
}

template<class T>
void MyTree<T>::_insert(const T& val, TreeNode<T>** root)
{
	if (root == nullptr) return;
	if (nullptr == (*root))//����
	{
		*root = new TreeNode<T>(val);
		return;
	}

	if (val >= (*(root))->val)//�ұ߲� ���ڵ����ұ߲�
	{
		_insert(val, &((*(root))->right));
		return;
	}
	_insert(val, &((*(root))->left));//��߲�

}

//ǰ��
template<class T>
void MyTree<T>::_PreOrder(TreeNode<T>* root) const
{
	if (root == nullptr)
		return;
	cout << root->val << " ";
	_PreOrder(root->left);
	_PreOrder(root->right);
}

//����
template<class T>
void MyTree<T>::_MidOrder(TreeNode<T>* root)const
{
	if (root == nullptr)
		return;
	_MidOrder(root->left);
	cout << root->val << " ";
	_MidOrder(root->right);
}

//����
template<class T>
void MyTree<T>::_PostOrder(TreeNode<T>* root)const
{
	if (root == nullptr)
		return;
	_PostOrder(root->left);
	_PostOrder(root->right);
	cout << root->val << " ";
}

//����
template<class T>
TreeNode<T>* MyTree<T>::find(const T& val)
{
	return _find(val,root);
}

template<class T>
TreeNode<T>* MyTree<T>::_find(const T& val,TreeNode<T>* root)
{
	if (root == nullptr)//����
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
	return nullptr;//û�ҵ�

}

//ɾ��
template<class T>
bool MyTree<T>::PopNode(const T& val)
{
	return _PopNode(val, root);
}

template<class T>
bool MyTree<T>::_PopNode(const T& val, TreeNode<T>* root)
{
	if (root == nullptr)//����
		return false;
	auto pdel = _find(val, root);
	if (pdel == nullptr)//û�ҵ�Ҫɾ������
		return false;

	//ɾ�����ڵ� ����:�����嵽��������ڵ�
	if (pdel == this->root)
	{
		if (pdel->right == nullptr)//����Ϊ��
		{
			this->root= pdel->left;
			delete pdel;
			return true;
		}
		else//���Ҳ�Ϊ��
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

	//ɾ�������ڵ�
	auto prevdel = root; //�ҵ�pdel�ĸ��ڵ�
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

	if (pdel->right) //pdel ������ �ӵ� ����(�ǿ�)����С��ڵ���
	{
		auto ptemp = pdel->right;
		while (ptemp->left)
		{
			ptemp = ptemp->left;
		}
		ptemp->left = pdel->left;
	}

	if (prevdel->left == pdel)//���ڵ����ڵ���pdel
	{
		if (pdel->right)//pdel�ҽڵ㲻Ϊ��
			prevdel->left = pdel->right;
		else
			prevdel->left = pdel->left;
		delete pdel;
		return true;
	}
	else//���ڵ���ҽڵ���pdel
	{
		if (pdel->right)
			prevdel->right = pdel->right;
		else
			prevdel->right = pdel -> left;
		delete pdel;
		return true;
	}

}

//������
template<class T>
void MyTree<T>::_delete(TreeNode<T>* root)
{
	//����ɾ���ڸ���
	if (root == nullptr)
		return;
	_delete(root->left);
	_delete(root->right);
	delete root;
	root = nullptr;
}
//ɾ��
template<class T>
bool MyTree<T>::_Poproot()
{
	if (root == nullptr)//����
		return false;

	//ɾ�����ڵ� ����:�����嵽��������ڵ�
	auto pdel = root;
	
	if (pdel->right == nullptr)//����Ϊ��
	{
		this->root = pdel->left;
		delete pdel;
		return true;
	}
	else//���Ҳ�Ϊ��
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
