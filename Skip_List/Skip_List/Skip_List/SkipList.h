#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_LEVEL 5

typedef struct SkipNode
{
	int val;		//值
	int maxLevel;	//当前节点的最大层数
	//下一个节点的指针数组。
	struct SkipNode** next;
}SkipNode;

typedef struct
{
	int nodeNum;	//节点个数
	int level;		//跳表的索引总层数
	SkipNode* head;
}SkipList;

//创建出一个新的节点，将其层数以及值传过来。
SkipNode* BuyNode(int level, int val);

//创建跳表
SkipList* Create();

//传过来一个 target，看看是否在跳表中
bool Search(SkipList* list, int target);

//获取拆入节点时候，所需的层数
int GetRandomLevel();

//将val 插入 跳表中去，
void SkipListAdd(SkipList* list,int val);

//找到节点然后删除
void SkipListDel(SkipList* list, int target);

//打印一下跳表结构
void Print(SkipList* list);

//销毁跳表
void Destroy(SkipList** list);