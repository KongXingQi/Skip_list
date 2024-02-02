#include "SkipList.h"


//创建出一个新的节点，将其层数以及值传过来。
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

//创建跳表
SkipList* Create()
{
	SkipList* list = (SkipList*)malloc(sizeof(SkipList));
	list->head = BuyNode(MAX_LEVEL, -1);	//最开始初始化开辟5层，可修改，-1无意义，头节点。
	list->level = 0;	//初始化跳表，当前层数为0.
	list->nodeNum = 0;	//初始化节点个数。
	SkipNode* headNode = BuyNode(MAX_LEVEL, -1);
	for (int i = 0; i < MAX_LEVEL; i++)
	{
		list->head->next[i] = headNode;
	}
	return list;
}


//传过来一个 target，看看是否在跳表中
bool Search(SkipList* list, int target)
{
	//从最上层开始去找
	int levelIndex = list->level - 1;
	SkipNode* cur = list->head->next[levelIndex];
	int i;
	for (i = levelIndex; i >= 0; i--)
	{
		//下一个如果小于target，就往前一直遍历
		while (cur->next[i] != NULL && cur->next[i]->val < target)
		{
			cur = cur->next[i];
		}
		//至此，要么大于，等于，或者使这一层没有。
		if (cur->next[i] == NULL)
		{
			//直接去下一层
			continue;
		}
		//再去判断是否等于
		if (cur->next[i]->val == target)
		{
			return true;
		}
	}

	return false;
}


//获取拆入节点时候，所需的层数
int GetRandomLevel()
{
	int level = 1;
	while (rand() % 2)
	{
		level++;
	}

	//如果层数大于了调表总长度，返回最大长度即可。
	return level > MAX_LEVEL ? MAX_LEVEL : level;
}



//将val 插入 跳表中去，
void SkipListAdd(SkipList* list, int val)
{
	//也是从最高层开始
	int levelIndex = list->level - 1;
	SkipNode* cur = list->head->next[levelIndex];
	//开辟一个当前层数的prev数组，其里面存放着每一层相对应的前一个节点。
	SkipNode** prevNodes = (SkipNode**)malloc(sizeof(SkipNode*) * MAX_LEVEL);	
	int i;
	for (i = levelIndex; i >= 0; i--)
	{
		while (cur->next[i] != NULL && cur->next[i] -> val < val)
		{
			cur = cur->next[i];
		}

		//至此呢，要么找到了当前层数的末尾，要么是找到了合适的位置
		prevNodes[i] = cur;
	}

	//获取随机层数
	int suitLevel = GetRandomLevel();
	if (suitLevel > list->level)
	{
		//当新节点的层数比当前层数大时候，将prevNodes[i]记录
		for (i = list -> level; i < suitLevel; i++)
		{
			prevNodes[i] = list->head->next[i];
		}

		//更新层数
		list->level = suitLevel;
	}

	//将前面每层的节点于新节点进行链接
	SkipNode* newNode = BuyNode(suitLevel, val);
	for (i = 0; i < suitLevel; i++)
	{
		newNode->next[i] = prevNodes[i]->next[i];
		prevNodes[i]->next[i] = newNode;
	}

	list->nodeNum++;
}


//打印一下跳表结构
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


//找到节点然后删除
void SkipListDel(SkipList* list, int target)
{
	if (!Search(list, target))
	{
		printf("%d -> 此节点未找到!\n", target);
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

	//将所需要删除节点的以一个和后一个链接起来
	for (i = 0; i < cur->maxLevel; i++)
	{
		prevNodes[i]->next[i] = cur->next[i];
	
	}

	//判断删除当前节点后，是否需要更新最高层
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



//销毁跳表
void Destroy(SkipList** list)
{
	//从最底层往上
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