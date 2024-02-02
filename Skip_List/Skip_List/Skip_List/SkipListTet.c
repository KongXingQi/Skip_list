#include "SkipList.h"


/*
	改测试无任何意义，为开发过程中针对各中情况的测试

	可自行测试
*/

void Test1()
{

	SkipList* list = Create();
	int i = 0; 
	for (i = 10; i <= 100; i++)
	{
		SkipListAdd(list, i); 
		Print(list);
	}
	/*SkipListAdd(list, 2);
	SkipListAdd(list, 8);
	SkipListAdd(list, 6);
	SkipListAdd(list, 7);
	SkipListAdd(list, 5);
	SkipListAdd(list, 4);
	SkipListAdd(list, 1);*/
	SkipListDel(list, 17);
	SkipListDel(list, 34);
	SkipListDel(list, 62);
	SkipListDel(list, 70);
	SkipListDel(list, 81);
	Print(list);
	Destroy(&list);

}

int main()
{
	Test1();

	return 0;
}