#include <iostream>
#include <assert.h>
using namespace std;

template<class K, class V>
class BSTreeNode
{
	typedef BSTreeNode<K, V> Node;
public:
	BSTreeNode(K k = K(), V v = V()) :_key(k), _value(v), _left(nullptr), _right(nullptr),  _prev(nullptr)
	{}

	K _key;
	V _value;
	Node* _left = nullptr;
	Node* _right = nullptr;
	Node* _prev = nullptr;
};

template<class K, class V>
class BSTree
{
	typedef BSTreeNode<K, V> Node;
public:
	bool Insert(const K& key, const V& value)
	{//按照key升序
		Node* new_node = new Node(key, value);
		if (_root == nullptr)//空树
		{
			_root = new_node;
			return true;
		}
		//不是空树
		Node* cur = _root;
		while (cur)
		{
			if (new_node->_key < cur->_key)
			{//左走
				if (cur->_left == nullptr)//左子树为空
				{
					cur->_left = new_node;
					new_node->_prev = cur;
					break;
				}
				else
				{
					cur = cur->_left;
				}
			}
			else//右走
			{
				if (cur->_right == nullptr)//右子树为空
				{
					cur->_right = new_node;
					new_node->_prev = cur;
					break;
				}
				else//右子树不为空
				{
					cur = cur->_right;
				}
			}
		}
		cout << "插入成功" <<key<< endl;
		return true;
	}
	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key == key)//查找成功
			{
				return cur;
			}
			else if (cur->_key > key)//左走
			{
				cur = cur->_left;
			}
			else//右走
			{
				cur = cur->_right;
			}
		}
		if (cur == nullptr)//查找失败
		{
			//cout << "查找失败: " << key << endl;
			return nullptr;
		}
	}
	bool Erase(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key == key)//找到要删除节点
			{
				if (cur->_left == nullptr && cur->_right==nullptr)//cur没有子树
				{
					if (cur == cur->_prev->_left)//cur为parent的左子树
					{
						cur->_prev->_left = nullptr;
						delete cur;
					}
					else if (cur == cur->_prev->_right)//cur为parent右子树
					{
						cur->_prev->_right = nullptr;
						delete cur;
					}
				}
				else if (cur->_left && cur->_right == nullptr)//cur只有左子树
				{
					if (cur->_prev->_left == cur)//cur为parent左子树
					{
						cur->_prev->_left = cur->_left;
					}
					else//cur为parent右子树
					{
						cur->_prev->_right = cur->_left;
					}
					delete cur;
				}
				else if (cur->_left == nullptr && cur->_right)//cur只有右子树
				{
					if (cur->_prev->_left == cur)//cur为parent左子树
					{
						cur->_prev->_left = cur->_right;
					}
					else//cur为parent右子树
					{
						cur->_prev->_right = cur->_right;
					}
					delete cur;
				}
				//cur有左右子树
				else
				{//找右子树中最小key
					Node* right = cur->_right;
					if (!right)
					{
						cout << "right == nullptr!!" << endl;
					}
					assert(right);
					while (right->_left)
					{
						right = right->_left;
					}
					swap(cur->_key, right->_key);
					//删除right
					if (right->_prev->_left == right)//right为parent左子树
					{
						right->_prev->_left == nullptr;
					}
					else//right为parent右子树
					{
						right->_prev->_right = nullptr;
					}
					delete right;
				}
				return true;
			}
			else if (cur->_key > key)//找左子树
			{
				cur = cur->_left;
			}
			else//找右子树
			{
				cur = cur->_right;
			}
		}
		//cur == nullptr 没找到key
		return false;
	}
	
	void InOrder()//中序输出
	{
		//_MakeOrderByKey(_root);//按照val排序
		_InOrder(_root);
	}
private:


	void _InOrder(Node* root)
	{
		if (root == nullptr)//空树
		{
			return;
		}
		Node* cur = root;
		
		_InOrder(cur->_left);
		cout <<cur-> _key << " ";
		_InOrder(cur->_right);

		if (root == _root)//最后换行
		{
			cout << endl;
		}
	}
	
	Node* _root = nullptr;
};

void TestBSTree()
{
	/*BSTree<string, string> dict;
	dict.Insert("insert", "插入");
	dict.Insert("erase", "删除");
	dict.Insert("left", "左边");
	dict.Insert("string", "字符串");*/

	//string str;
	//while (cin >> str && str != "exit")
	//{
	//	auto ret = dict.Find(str);
	//	if (ret)//查找成功
	//	{
	//		cout << str << ":" << ret->_value << endl;
	//	}
	//	else//查找失败
	//	{
	//		cout << "单词拼写错误" << endl;
	//	}
	//}

	//string strs[] = { "苹果", "西瓜", "苹果", "樱桃", "苹果", "樱桃", "苹果", "樱桃", "苹果" };
	//// 统计水果出现的次
	//BSTree<string, int> countTree;
	//for (const auto& str : strs)
	//{
	//	auto ret = countTree.Find(str);
	//	if (ret == nullptr)//未找到
	//	{
	//		countTree.Insert(str, 1);
	//	}
	//	else
	//	{
	//		ret->_value++;
	//	}   
	//}
	//countTree.InOrder();

	//测试erase&insert排序功能
	BSTree<int, int> test;
	test.Insert(8, 0);
	test.Insert(3, 0);
	test.Insert(5, 0);
	test.Insert(18, 0);
	test.Insert(9, 0);
	test.Insert(11, 0);
	test.Insert(4, 0);
	test.Insert(1, 0);
	test.InOrder();
	test.Erase(18);
	test.InOrder();

}


int main()
{
	TestBSTree();
	return 0;
}
