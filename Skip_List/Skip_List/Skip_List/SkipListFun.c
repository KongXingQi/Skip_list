#include "SkipList.h"


//������һ���µĽڵ㣬��������Լ�ֵ��������
SkipNode* BuyNode(int level, int val)
{
	SkipNode* newNode = (SkipNode*)malloc(sizeof(SkipNode));
	newNode->val = val;
	newNode->maxLevel = level;
	newNode->next = (SkipNode**)malloc(sizeof(SkipNode*) * level);
	for (int i = 0; i < level; i++)
	{
		newNode->next[i] = NULL;
	}
	return newNode;
}

//��������
SkipList* Create()
{
	SkipList* list = (SkipList*)malloc(sizeof(SkipList));
	list->head = BuyNode(MAX_LEVEL, -1);	//�ʼ��ʼ������5�㣬���޸ģ�-1�����壬ͷ�ڵ㡣
	list->level = 0;	//��ʼ��������ǰ����Ϊ0.
	list->nodeNum = 0;	//��ʼ���ڵ������
	SkipNode* headNode = BuyNode(MAX_LEVEL, -1);
	for (int i = 0; i < MAX_LEVEL; i++)
	{
		list->head->next[i] = headNode;
	}
	return list;
}


//������һ�� target�������Ƿ���������
bool Search(SkipList* list, int target)
{
	//�����ϲ㿪ʼȥ��
	int levelIndex = list->level - 1;
	SkipNode* cur = list->head->next[levelIndex];
	int i;
	for (i = levelIndex; i >= 0; i--)
	{
		//��һ�����С��target������ǰһֱ����
		while (cur->next[i] != NULL && cur->next[i]->val < target)
		{
			cur = cur->next[i];
		}
		//���ˣ�Ҫô���ڣ����ڣ�����ʹ��һ��û�С�
		if (cur->next[i] == NULL)
		{
			//ֱ��ȥ��һ��
			continue;
		}
		//��ȥ�ж��Ƿ����
		if (cur->next[i]->val == target)
		{
			return true;
		}
	}

	return false;
}


//��ȡ����ڵ�ʱ������Ĳ���
int GetRandomLevel()
{
	int level = 1;
	while (rand() % 2)
	{
		level++;
	}

	//������������˵����ܳ��ȣ�������󳤶ȼ��ɡ�
	return level > MAX_LEVEL ? MAX_LEVEL : level;
}



//��val ���� ������ȥ��
void SkipListAdd(SkipList* list, int val)
{
	//Ҳ�Ǵ���߲㿪ʼ
	int levelIndex = list->level - 1;
	SkipNode* cur = list->head->next[levelIndex];
	//����һ����ǰ������prev���飬����������ÿһ�����Ӧ��ǰһ���ڵ㡣
	SkipNode** prevNodes = (SkipNode**)malloc(sizeof(SkipNode*) * MAX_LEVEL);	
	int i;
	for (i = levelIndex; i >= 0; i--)
	{
		while (cur->next[i] != NULL && cur->next[i] -> val < val)
		{
			cur = cur->next[i];
		}

		//�����أ�Ҫô�ҵ��˵�ǰ������ĩβ��Ҫô���ҵ��˺��ʵ�λ��
		prevNodes[i] = cur;
	}

	//��ȡ�������
	int suitLevel = GetRandomLevel();
	if (suitLevel > list->level)
	{
		//���½ڵ�Ĳ����ȵ�ǰ������ʱ�򣬽�prevNodes[i]��¼
		for (i = list -> level; i < suitLevel; i++)
		{
			prevNodes[i] = list->head->next[i];
		}

		//���²���
		list->level = suitLevel;
	}

	//��ǰ��ÿ��Ľڵ����½ڵ��������
	SkipNode* newNode = BuyNode(suitLevel, val);
	for (i = 0; i < suitLevel; i++)
	{
		newNode->next[i] = prevNodes[i]->next[i];
		prevNodes[i]->next[i] = newNode;
	}

	list->nodeNum++;
}


//��ӡһ������ṹ
void Print(SkipList* list)
{
	SkipNode* cur = NULL;
	for (int i = list->level - 1; i >= 0; i--)
	{
		cur = list->head->next[i];
		printf("level %d: ",i);
		while (cur -> next[i] != NULL)
		{
			printf("%d->", cur->next[i]->val);
			cur = cur->next[i];
		}
		printf("\n");
	}
	printf("\n");
}


//�ҵ��ڵ�Ȼ��ɾ��
void SkipListDel(SkipList* list, int target)
{
	if (!Search(list, target))
	{
		printf("%d -> �˽ڵ�δ�ҵ�!\n", target);
		return;
	}

	int levelIndex = list->level - 1;
	SkipNode** prevNodes = (SkipNode**)malloc(sizeof(SkipNode*) * MAX_LEVEL);
	SkipNode* cur = list->head->next[levelIndex];
	int i;
	for (i = levelIndex; i >= 0; i--)
	{
		while (cur->next[i] != NULL && cur->next[i]->val < target)
		{
			cur = cur->next[i];
		}

		prevNodes[i] = cur;
	}

	cur = cur->next[0];

	//������Ҫɾ���ڵ����һ���ͺ�һ����������
	for (i = 0; i < cur->maxLevel; i++)
	{
		prevNodes[i]->next[i] = cur->next[i];
	
	}

	//�ж�ɾ����ǰ�ڵ���Ƿ���Ҫ������߲�
	for (i = list -> level - 1; i >= 0; i--)
	{
		if (list->head->next[i]->next[i] != NULL)
		{
			break;
		}
		list->level--;
	}

	free(cur);
	list->nodeNum--;
}



//��������
void Destroy(SkipList** list)
{
	//����ײ�����
	SkipNode* cur = (*list)->head -> next[0];
	SkipNode* tmp = cur->next[0];
	free((*list)->head);
	while (cur != NULL)
	{
		tmp = cur->next[0];
		free(cur);
		cur = tmp;
	}

	free(*list);
	*list = NULL;
}