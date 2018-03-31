//iterator for BS tree traversal
// inorder threaded tree
#include<iostream>
#include<stack>
#include<queue>

using namespace std;

template <typename T>
class BinarySearchTree
{
	struct TreeNode
	{
		TreeNode *left;
		TreeNode *right;
		bool isLeftThread;
		bool isRightThread;
		T data;
		TreeNode():left(NULL), right(NULL), isLeftThread(false), isRightThread(false)
		{
		}
		TreeNode(T value):data(value), left(NULL), right(NULL), isLeftThread(false), isRightThread(false)
		{
		}
		void printData()
		{
			cout<<"data "<<data<<endl;
		}
		void setRightThread(TreeNode *node)
		{
			isRightThread = true;
			right = node;
		}
		void setLeftThread(TreeNode *node)
		{
			isLeftThread = true;
			left = node;
		}
	};
	
public:
	class iterator
	{
		TreeNode *currNode;
	public:
		iterator(TreeNode *curr):currNode(curr)
		{
			
		}
		
		iterator():currNode(NULL)
		{
			
		}
		void next()
		{
			
		}
		void hasNext()
		{
			
		}
		TreeNode* operator ->()
		{
			return currNode;
		}
		void operator ++()
		{
			currNode = currNode->right;
		}
		bool operator ==(const iterator &other)
		{
			return(this->currNode == other.currNode);
		}
		bool operator !=(const iterator &other)
		{
			return(this->currNode != other.currNode);
		}
	};
private:
	TreeNode *root;
	
public:
	BinarySearchTree()
	{
		root = new TreeNode(-1);
	}
	
	void insertNode(T data)
	{
		cout<<"inserting "<<data<<endl;
		if(root->right == NULL)
		{
			root->right = new TreeNode(data);
			root->right->setRightThread(root);
			root->right->setLeftThread(root->right);
			root->setLeftThread(root);
			return;
		}
		TreeNode *temp = root->right, *prev = NULL, *lastLeft = root, *lastRight = root;
		while(temp != NULL)
		{
			prev = temp;
			if(temp->data >= data)
			{
				
				if(temp->isLeftThread == false)
				{
					lastLeft = prev;
					temp = temp->left;
					cout<<"going left\n";
				}
				else
				{
					temp = NULL;
				}
			}
			else
			{
				if(temp->isRightThread == false)
				{
					temp = temp->right;
					lastRight = prev;
					cout<<"going right\n";
				}
				else
				{
					temp = NULL;
				}
			}
		}
		
		if(prev->data >= data)
		{
			bool isPrevLeftMostNode = false;
			if(prev->left == prev) {
				isPrevLeftMostNode = true;
			}
			temp = prev->left;
			prev->left = new TreeNode(data);
			prev->isLeftThread = false;
	    prev->left->setRightThread(prev); //prev->left->setRightThread(lastLeft);
	    prev->left->setLeftThread(isPrevLeftMostNode ? prev->left : temp);
	}
	else
	{
		cout<<"inserting right \n";
		temp = prev->right;
		prev->right = new TreeNode(data);
		prev->right->setRightThread(temp);
		prev->right->setLeftThread(prev);
		prev->isRightThread = false;
	}
	
	cout<<"inserted \n";
	
}

TreeNode *findNode(T data)
{
	
}
void deleteNode()
{
	
}

iterator start()
{
	TreeNode* temp = root->right;
	while(temp->left && temp->isLeftThread == false)
	{
		temp = temp->left;
	}
	return iterator(temp);
}
iterator end()
{
	return iterator(root);
}

void traverseInOrderUtil(TreeNode *root)
{
	if(root == NULL)
		return;
	
	if(root->left && root->isLeftThread == false)
	{
		traverseInOrderUtil(root->left);
	}
	cout<<"----"<<"\n";
	if(root->isLeftThread == true && root->left)
	{
		cout<<root->data<<" left links to "<<root->left->data<<endl;
	}
	root->printData();
	if(root->isRightThread == true && root->right)
	{
		cout<<root->data<<" right links to "<<root->right->data<<endl;
	}
	if(root->right && root->isRightThread == false)
	{
		traverseInOrderUtil(root->right);
	}
}

void traverseInOrder()
{
	traverseInOrderUtil(root->right);
}

void traverseInOrderNonRecursive()
{
	stack <TreeNode*> st;
	TreeNode *curr = root->right;
	
	
	while(1)
	{
		while(curr)
		{
			st.push(curr);
			if(curr->left && curr->isLeftThread==false)
			{
				curr=curr->left;
			}
			else
			{
				curr = NULL;
			}
		}
		
		if(!st.empty())
		{
			curr= st.top();
			st.pop();
			curr->printData();
			if(curr->right && curr->isRightThread==false)
			{
				curr= curr->right;
			}
			else
			{
				curr = NULL;
			}
		}
		else
		{
			return;
		}
		
	}
}

void traversePreOrderNonRecursive()
{
	queue <TreeNode*> q;
	TreeNode *curr = root->right;
	q.push(curr);
	
	while(!q.empty())
	{
		curr = q.front();
		q.pop();
		curr->printData();
		if(curr->left && curr->isLeftThread==false)
		{
			q.push(curr->left);
		}
		if(curr->right && curr->isRightThread==false)
		{
			q.push(curr->right);
		}
	}
	
}
};


int main()
{
	BinarySearchTree <int>t;
	
	t.insertNode(10);
	t.insertNode(1);
	t.insertNode(2);
	t.insertNode(12);
	t.insertNode(4);
	t.insertNode(3);
	t.insertNode(5);
	t.insertNode(26);
	t.insertNode(7);
	t.insertNode(8);
	t.insertNode(9);
	t.insertNode(11);
	
	
	BinarySearchTree <int> :: iterator it;
	int i =0;
	
	cout<<"Starting traversal\n";
	t.traverseInOrder();
    //t.traverseInOrderNonRecursive();
    //t.traversePreOrderNonRecursive();
	
	cout<<"Starting iterator\n";
	
	for(it = t.start(); it!=t.end();++it)
	{
		it->printData();
		if(i++>15)
			break;
	}
	
	return 0;
	
}
