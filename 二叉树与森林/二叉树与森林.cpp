#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

using namespace std;
//存有孩子结点索引的单链表结点
typedef struct TreeLinkNode {
	int index;
	struct TreeLinkNode *next;
} TreeLinkNode, *pTreeLinkNode;
//孩子链表结点（树结点）
typedef struct TreeNode
{
	pTreeLinkNode link;
	int data;
} TreeNode, *pTreeNode;
//森林结点
typedef struct FTreeNode
{
	pTreeNode tree;
	struct FTreeNode *next;
} FTreeNode, *pFTreeNode;
//森林链表的初始化操作
void InitFTree(pFTreeNode &fTree)
{
	fTree = (pFTreeNode)malloc(sizeof(FTreeNode));
	fTree->next = NULL;
}
//森林链表的插入操作
void InsertFTree(pFTreeNode &fTree, pTreeNode node)
{
	pFTreeNode t_node = fTree;
	pFTreeNode newnode = (pFTreeNode)malloc(sizeof(FTreeNode));

	while (t_node->next != NULL)
	{
		t_node = t_node->next;
	}

	newnode->tree = node;
	t_node->next = newnode;
	newnode->next = NULL;
}
//广义表建立树链表（孩子链表）
void GListToTree(pTreeNode &tree, int &current_index, int parent_index)
{
	char ch;
	pTreeLinkNode newnode;
	pTreeLinkNode link = (pTreeLinkNode)malloc(sizeof(TreeLinkNode));
	link->index = current_index;
	link->next = NULL;
	tree[parent_index].link = link;
	while (true)
	{
		scanf("%c", &ch);
		if (ch == '(')
		{
			parent_index = current_index;
			current_index++;
			scanf("%d", &tree[current_index].data);
			tree[current_index].link = NULL;
			GListToTree(tree, current_index, parent_index);
		}
		else if (ch == ',') {
			current_index++;
			scanf("%d", &tree[current_index].data);
			tree[current_index].link = NULL;
			newnode = (pTreeLinkNode)malloc(sizeof(TreeLinkNode));
			newnode->index = current_index;
			newnode->next = NULL;
			link->next = newnode;
			link = link->next;
		}
		else
		{
			return;
		}
	}
}
//广义表组建立森林链表
void GListToFTree(pFTreeNode &fTree) {
	char ch;
	int current_index, parent_index;
	pTreeNode tree;
	scanf("%c", &ch);
	while (ch != '#')
	{
		current_index = -1;
		tree = (pTreeNode)malloc(50 * sizeof(TreeNode));

		current_index++;
		scanf("%d", &tree[current_index].data);
		tree[current_index].link = NULL;
		scanf("%c", &ch);
		if (ch != ')') {
			parent_index = current_index;
			current_index++;
			scanf("%d", &tree[current_index].data);
			tree[current_index].link = NULL;
			GListToTree(tree, current_index, parent_index);
			scanf("%c", &ch);
		}
		InsertFTree(fTree, tree);
		scanf("%c", &ch);
	}
}
//存储先序遍历序列记录的单链表结点
typedef struct LinkNode {
	int data;
	struct LinkNode *next;
} LinkNode, *pLinkNode;
//单链表的初始化
void InitLinkList(pLinkNode &link) {
	link = (pLinkNode)malloc(sizeof(LinkNode));
	link->next = NULL;
}
//单链表的建立
void CreateLinkList(pLinkNode &link, int m) {
	int i;
	pLinkNode newnode, p_Link = link;
	printf("请输入先序遍历序列:");
	for (i = 0; i<m; i++) {
		newnode = (pLinkNode)malloc(sizeof(LinkNode));
		scanf("%d", &newnode->data);
		newnode->next = NULL;
		p_Link->next = newnode;
		p_Link = p_Link->next;
	}
}
//单链表的头删
void DeleteFirst(pLinkNode &link) {
	pLinkNode p_Link = link->next;
	if (p_Link != NULL)
	{
		link->next = p_Link->next;
		free(p_Link);
	}
}
//存储中序遍历序列的双向链表结点
typedef struct DuLinkNode {
	int data;
	bool isVisited;
	struct DuLinkNode *next;
	struct DuLinkNode *prior;
} DuLinkNode, *pDuLinkNode;
//双向链表的初始化
void InitDuLinkList(pDuLinkNode &DuLink) {
	DuLink = (pDuLinkNode)malloc(sizeof(DuLinkNode));
	DuLink->isVisited = true;
	DuLink->prior = NULL;
	DuLink->next = (pDuLinkNode)malloc(sizeof(DuLinkNode));
	DuLink->next->prior = DuLink;
	DuLink->next->isVisited = true;
	DuLink->next->next = NULL;
}
//双向链表的建立
void CreateDuLinkList(pDuLinkNode &DuLink, int m) {
	int i;
	pDuLinkNode newnode, p_DuLink = DuLink;
	printf("请输入中序遍历序列:");
	for (i = 0; i<m; i++) {
		newnode = (pDuLinkNode)malloc(sizeof(DuLinkNode));
		scanf("%d", &newnode->data);
		newnode->isVisited = false;
		newnode->next = p_DuLink->next;
		p_DuLink->next->prior = newnode;
		newnode->prior = p_DuLink;
		p_DuLink->next = newnode;
		p_DuLink = p_DuLink->next;
	}
}
//二叉树结点
typedef struct BiTreeNode {
	int data;
	struct BiTreeNode *left;
	struct BiTreeNode *right;
} BiTreeNode, *pBiTreeNode;
//二叉树
typedef struct BiTree {
	pBiTreeNode tree;
} BiTree;
//二叉树初始化
void InitBiTree(BiTree &biTree) {
	biTree.tree = NULL;
}
//先序中序重建二叉树
void CreateBiTree(pBiTreeNode &biTree, pLinkNode &link, pDuLinkNode &DuLink) {
	pLinkNode p_Link = link->next;
	pDuLinkNode p_DuLink = DuLink->next;
	if (p_Link != NULL) {
		biTree = (pBiTreeNode)malloc(sizeof(BiTreeNode));
		biTree->left = NULL;
		biTree->right = NULL;
		biTree->data = p_Link->data;
		while (p_Link->data != p_DuLink->data) {
			p_DuLink = p_DuLink->next;
		}
		p_DuLink->isVisited = true;
		DeleteFirst(link);
		if (p_DuLink->prior->isVisited == false)
		{
			CreateBiTree(biTree->left, link, DuLink);
		}
		if (p_DuLink->next->isVisited == false)
		{
			CreateBiTree(biTree->right, link, DuLink);
		}
	}
}
//二叉树转化为树，是二叉树转化为森林的子函数
void BiTreeToTree(pTreeNode &tree, pBiTreeNode &biTree, int &current_index, int parent_index)
{
	pBiTreeNode p_biTree = biTree->left;
	pTreeLinkNode newnode;

	if (p_biTree != NULL)
	{
		current_index++;
		tree[current_index].data = p_biTree->data;
		tree[current_index].link = NULL;

		newnode = (pTreeLinkNode)malloc(sizeof(TreeLinkNode));
		newnode->index = current_index;
		newnode->next = NULL;
		tree[parent_index].link = newnode;

		BiTreeToTree(tree, p_biTree, current_index, newnode->index);

		while (p_biTree->right != NULL)
		{
			p_biTree = p_biTree->right;

			current_index++;
			tree[current_index].data = p_biTree->data;
			tree[current_index].link = NULL;

			newnode->next = (pTreeLinkNode)malloc(sizeof(TreeLinkNode));
			newnode = newnode->next;
			newnode->index = current_index;
			newnode->next = NULL;

			BiTreeToTree(tree, p_biTree, current_index, newnode->index);
		}
	}
}
//二叉树转化为森林
void BiTreetoFTree(pFTreeNode &fTree, pBiTreeNode &biTree)
{
	int current_index, parent_index;
	pTreeNode newnode;
	pBiTreeNode p_biTree = biTree;
	do
	{
		newnode = (pTreeNode)malloc(sizeof(TreeNode) * 50);
		current_index = 0;
		parent_index = current_index;
		newnode[current_index].data = p_biTree->data;
		newnode[current_index].link = NULL;
		BiTreeToTree(newnode, p_biTree, current_index, parent_index);
		InsertFTree(fTree, newnode);
		p_biTree = p_biTree->right;
	} while (p_biTree != NULL);
}
//树转化为二叉树，是森林转化为二叉树的子函数
void TreeToBiTree(pTreeNode &tree, pBiTreeNode &biTree, int index)
{
	pBiTreeNode newnode = (pBiTreeNode)malloc(sizeof(BiTreeNode));
	newnode->data = tree[index].data;
	newnode->left = NULL;
	newnode->right = NULL;
	biTree = newnode;

	pTreeLinkNode link = tree[index].link;
	pBiTreeNode tempNode = biTree;

	if (link != NULL)
	{
		TreeToBiTree(tree, tempNode->left, link->index);
		link = link->next;
		tempNode = tempNode->left;
		while (link != NULL)
		{
			TreeToBiTree(tree, tempNode->right, link->index);
			link = link->next;
			tempNode = tempNode->right;
		}
	}
}
//森林转化为二叉树
void FTreeToBiTree(pFTreeNode &fTree, BiTree &biTree)
{
	pFTreeNode p_fTree = fTree->next;
	pBiTreeNode p_biTree = biTree.tree;

	while (p_fTree != NULL)
	{
		if (biTree.tree == NULL) {
			TreeToBiTree(p_fTree->tree, biTree.tree, 0);
			p_biTree = biTree.tree;
		}
		else {
			TreeToBiTree(p_fTree->tree, p_biTree->right, 0);
			p_biTree = p_biTree->right;
		}
		p_fTree = p_fTree->next;
	}
}
//树转化为广义表，是森林转化为广义表的子函数
void TreeToGList(pTreeNode &tree, int parent_index)
{
	pTreeLinkNode p_treeLink = tree[parent_index].link;

	if (p_treeLink != NULL)
	{
		printf("(");
		printf("%d", tree[p_treeLink->index].data);
		TreeToGList(tree, p_treeLink->index);
		p_treeLink = p_treeLink->next;

		while (p_treeLink != NULL)
		{
			printf(",");
			printf("%d", tree[p_treeLink->index].data);
			TreeToGList(tree, p_treeLink->index);

			p_treeLink = p_treeLink->next;
		}

		printf(")");
	}
}
//森林转化为广义表
void FTreeToGList(pFTreeNode &fTree)
{
	int parent_index;
	pFTreeNode p_fTree = fTree->next;

	while (p_fTree != NULL)
	{
		parent_index = 0;

		printf("(");
		printf("%d", p_fTree->tree[0].data);
		TreeToGList(p_fTree->tree, parent_index);
		printf(")");

		p_fTree = p_fTree->next;
	}
	printf("#");
}
//树的先跟遍历，是森林的先根遍历的子函数
void TreePreTraverse(pTreeNode &tree, int index)
{
	pTreeLinkNode link;
	printf("%d ", tree[index].data);

	link = tree[index].link;
	while (link != NULL)
	{
		TreePreTraverse(tree, link->index);
		link = link->next;
	}
}
//森林的先根遍历
void FTreePreTraverse(pFTreeNode &fTree)
{
	pFTreeNode link = fTree->next;
	while (link != NULL) {
		TreePreTraverse(link->tree, 0);
		link = link->next;
	}
}
//树的后根遍历，是森林的后根遍历的子函数
void TreePostTraverse(pTreeNode &tree, int index)
{
	pTreeLinkNode link;

	link = tree[index].link;
	while (link != NULL)
	{
		TreePostTraverse(tree, link->index);
		link = link->next;
	}
	printf("%d ", tree[index].data);
}
//森林的后根遍历
void FTreePostTraverse(pFTreeNode &fTree)
{
	pFTreeNode link = fTree->next;
	while (link != NULL)
	{
		TreePostTraverse(link->tree, 0);
		link = link->next;
	}
}
//二叉树的先序遍历
void BiTreePreTraverse(pBiTreeNode &tree) {
	if (tree != NULL) {
		printf("%d ", tree->data);
		if (tree->left != NULL) {
			BiTreePreTraverse(tree->left);
		}
		if (tree->right != NULL){
			BiTreePreTraverse(tree->right);
		}
	}
}
//二叉树的中序遍历
void BiTreeInOrderTraverse(pBiTreeNode &tree){
	if (tree != NULL){
		if (tree->left != NULL)
		{
			BiTreeInOrderTraverse(tree->left);
		}

		printf("%d ", tree->data);

		if (tree->right != NULL)
		{
			BiTreeInOrderTraverse(tree->right);
		}
	}
}
//主函数
int main(void)
{


	printf("\n##################################################################\n");
	printf("\n树（森林）的广义表（括号表示法）重建树（森林）\n");
	printf("请输入树（森林）的广义表（括号表示法）（以#结束）：\n");

	pFTreeNode fTree1;
	InitFTree(fTree1);
	GListToFTree(fTree1);

	printf("\n树（森林）的广义表（括号表示法）重建树（森林）后的遍历\n");
	printf("树（森林）的先根遍历：\n");
	FTreePreTraverse(fTree1);
	printf("\n");
	printf("树（森林）的后根遍历：\n");
	FTreePostTraverse(fTree1);
	printf("\n");

	printf("\n##################################################################\n");
	printf("\n树（森林）转化成二叉树：\n\n");
	BiTree biTree1;
	InitBiTree(biTree1);
	FTreeToBiTree(fTree1, biTree1);

	printf("树（森林）转换成二叉树后二叉树的遍历\n");
	printf("树（森林）转换成的二叉树的先序遍历：\n");
	BiTreePreTraverse(biTree1.tree);
	printf("\n树（森林）转换成的二叉树的中序遍历：\n");
	BiTreeInOrderTraverse(biTree1.tree);
	printf("\n");

	printf("\n##################################################################\n");
	printf("\n由树的先序遍历序列和树的中序遍历序列重建二叉树：\n");
	int m;
	printf("请输入二叉树的结点数：");
	scanf("%d", &m);

	pLinkNode link;
	InitLinkList(link);
	CreateLinkList(link, m);

	pDuLinkNode DuLink;
	InitDuLinkList(DuLink);
	CreateDuLinkList(DuLink, m);

	BiTree biTree2;
	InitBiTree(biTree2);
	CreateBiTree(biTree2.tree, link, DuLink);

	printf("\n重建二叉树后的先序遍历：\n");
	BiTreePreTraverse(biTree2.tree);
	printf("\n重建二叉树后的中序遍历：\n");
	BiTreeInOrderTraverse(biTree2.tree);
	printf("\n");

	printf("\n##################################################################\n");
	pFTreeNode fTree2;
	InitFTree(fTree2);
	printf("\n重建的二叉树转化成树（森林）：\n\n");
	BiTreetoFTree(fTree2, biTree2.tree);
	printf("重建的二叉树转换成树（森林）后，树（森林）的遍历：\n");
	printf("树（森林）的先根遍历：\n");
	FTreePreTraverse(fTree2);
	printf("\n树（森林）的后根遍历：\n");
	FTreePostTraverse(fTree2);
	printf("\n\n");

	printf("##################################################################\n");
	printf("\n上面生成的树(森林)生成其相应的广义表（括号表示法）\n");
	FTreeToGList(fTree2);
	printf("\n\n##################################################################\n");

	return 0;
}
