/*


내거 실패해벌임 ㅜ-ㅜ,,,, BSTNode 만으로 처리하려니까 안됨,,, ㅅㅂ,,, 3시간짜리 작품인데 ;;
왜 78Line 의 insertData부터 막혀벌이냐 ,, ㅅㅂ 환규형 코드갖고와서써야지 ,,아 짜증나아아아아아 짜쯩나 !!!!!!! 진짜 짜즈안 


*/



#include <iostream>


#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
using namespace std;

int getOpCode(string cmd) {
	string command[] = { "+","-","leaf","depth" };
	int cmdSize = sizeof(command) / sizeof(command[0]);
	for (int i = 0; i < cmdSize; ++i) {
		if (cmd == command[i])
			return i;
	}
	return -1;	
}
class BTreeNode
{
public:	
	friend class BST;
	BTreeNode * LeftChild, *RightChild;
	BTreeNode * parent;
	string data;

	BTreeNode(string data) :data(data),LeftChild(NULL),RightChild(NULL) {	}		
	void setLeftChild(BTreeNode* child)	{
		this->LeftChild = child;
	}
	void setRightChild(BTreeNode* child){
		this->RightChild = child;
	}
	
};
//BTreeNode * cut_Parent(BTreeNode* node) {  // leaf 삭제하기위한 함수
//	
//}

class BST
{
public:
	BTreeNode * root;
	BST(BTreeNode* init = 0) { root = init; }
	BTreeNode * getMaxLeafNode(BTreeNode* root, int mod) {    // 어떤 리프를 올려줘야할지 찾아주는함수
		//if (root == NULL) return NULL;
		if (root->LeftChild == NULL && root->RightChild == NULL) return root;
		if (mod == 0) {
			if (root->LeftChild != NULL) return getMaxLeafNode(root->LeftChild, 1);
			return getMaxLeafNode(root->RightChild, 2);
		}
		else if (mod == 1) {
			if (root->RightChild != NULL) return getMaxLeafNode(root->RightChild, 1);
			return getMaxLeafNode(root->LeftChild, 1);
		}
		else {
			if (root->LeftChild != NULL) return getMaxLeafNode(root->RightChild, 2);
			return getMaxLeafNode(root->RightChild, 2);
		}
	}
	
	void insertData(string data) {
		BTreeNode * p = root;
		BTreeNode * q = 0;

		while (p) {
			//cout << " a";
			q = root;
			if (p->data.compare(data) == 0)
				return;
			if (p->data.compare(data) > 0)
				p = p->LeftChild;
			else
				p = p->RightChild;
		}
		p = new BTreeNode(data);
		if (!root)
			root = p;
		else if (q->data.compare(data) > 0) {
			p->parent = q;
			q->setLeftChild(p);
		}
		else {
			p->parent = q;
			q->setRightChild(p);
		}
		//cout << root->data;
	}
	BTreeNode* search(BTreeNode* root, string data) {
		if (root == NULL)return NULL;
		if (root->data == data) return root;
		if (root->data.compare(data) > 0) return search(root->LeftChild, data);
		return search(root->RightChild, data);
	}

	void deleteData(string dataa) {
		BTreeNode * cur = root;
		BTreeNode * paren = root;
		bool found = false;
		while (cur) {
			if (cur->data.compare(dataa) == 0) {
				//cout << cur->data << "  " << dataa << "   이 두개가 왜 같냐 시발년아";
				found = true;
				break;
			}
			paren = cur;
			if (cur->data.compare(dataa) > 0) 
				cur = cur->LeftChild;			
			else 
				cur = cur->RightChild;
		}
		if (cur == 0) return; //삭제할데이터없음
		if (cur == root) {
			if (cur->LeftChild == 0 && cur->RightChild == 0) {
				root = 0; return;
			}
			else {
				BTreeNode* leaf = getMaxLeafNode(cur,0);
				if (leaf->parent->LeftChild == leaf) leaf->parent->setLeftChild(0);
				else leaf->parent->setRightChild(0);
				leaf->parent = 0;
				if (cur->LeftChild != NULL) {
					leaf->setLeftChild(cur->LeftChild);
					cur->LeftChild->parent = leaf;
				}
				if (cur->RightChild != NULL) {
					leaf->setRightChild(cur->LeftChild);
					cur->RightChild->parent = leaf;
				}

				root = leaf;
			}
		}
		else {
			if (cur->LeftChild == 0 && cur->RightChild == 0) {
				root = 0; return;
			}
			else {
				BTreeNode* leaf = getMaxLeafNode(cur, 0);
				if (leaf->parent->LeftChild == leaf)
					leaf->parent->setLeftChild(0);
				else
					leaf->parent->setRightChild(0);
				
				if (cur->LeftChild != 0) { 
					leaf->setLeftChild(cur->LeftChild); 
					cur->LeftChild->parent = leaf;
				}
				else {
					leaf->setRightChild(cur->RightChild);
					cur->RightChild->parent = leaf;
				}

				leaf->parent = paren;
				if (paren->LeftChild == cur)
					paren->setLeftChild(leaf);
				else
					paren->setRightChild(leaf);
			}
		}
	}
	void print_Leaf(BTreeNode* root) {
		if (root == NULL)return;
		if (root->LeftChild == NULL && root->RightChild == NULL) {
			cout << root->data << " ";
			return;
		}
		print_Leaf(root->LeftChild);
		print_Leaf(root->RightChild);
	}
	void print_Depth(BTreeNode* root, int cur_depth, int target_depth) {
		if (root == NULL)return;
		if (cur_depth > target_depth) return;
		if (cur_depth == target_depth) {
			cout << root->data << " ";
		}
		print_Depth(root->LeftChild, cur_depth + 1, target_depth);
		print_Depth(root->RightChild, cur_depth + 1, target_depth);
	}
};
int max_depth(BTreeNode* rooter) {
	if (rooter == NULL) return 0;
	//cout << 1 << endl;
	return max(max_depth(rooter->LeftChild), max_depth(rooter->RightChild)) + 1;
}
int main() {

	ifstream inp("bst.inp");
	ofstream oup("bst.out");

	int Command_Number;
	inp >> Command_Number;
	BST tree;
	int i;
	for (i = 0; i < Command_Number; ++i) {
		//cout << i << endl;
		string cmd,word;
		int depth;
		inp >> cmd;
		cout << cmd<<endl;
		switch (getOpCode(cmd))
		{
		case 0:  // +
		{			
			inp >> word;	
			tree.insertData(word);			
			break;
		}
		case 1:  // -
		{
			inp >> word;			
			tree.deleteData(word);
			break;
		}
		case 2:  // leaf
		{			
			tree.print_Leaf( tree.root );
			cout << endl;
			break;
		}
		case 3:  // depth
		{			
			inp >> depth;
			if (depth >max_depth( tree.root ))
				cout << "NO" << endl;
			else {
			//	cout<<"이게잘못된거니";
				tree.print_Depth(tree.root, 1, depth);
			}
			break;
		}
		case -1:
		{
			cout << "There in no such command Exit zzz" << endl;;
			return 0;
		}
		}
	}
	inp.close(); oup.close();
	return 0;	
}