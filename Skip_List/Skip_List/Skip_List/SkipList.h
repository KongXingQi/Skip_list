#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_LEVEL 5

typedef struct SkipNode
{
	int val;		//ֵ
	int maxLevel;	//��ǰ�ڵ��������
	//��һ���ڵ��ָ�����顣
	struct SkipNode** next;
}SkipNode;

typedef struct
{
	int nodeNum;	//�ڵ����
	int level;		//����������ܲ���
	SkipNode* head;
}SkipList;

//������һ���µĽڵ㣬��������Լ�ֵ��������
SkipNode* BuyNode(int level, int val);

//��������
SkipList* Create();

//������һ�� target�������Ƿ���������
bool Search(SkipList* list, int target);

//��ȡ����ڵ�ʱ������Ĳ���
int GetRandomLevel();

//��val ���� ������ȥ��
void SkipListAdd(SkipList* list,int val);

//�ҵ��ڵ�Ȼ��ɾ��
void SkipListDel(SkipList* list, int target);

//��ӡһ������ṹ
void Print(SkipList* list);

//��������
void Destroy(SkipList** list);