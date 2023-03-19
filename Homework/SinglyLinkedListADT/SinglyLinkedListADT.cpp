#include "SinglyLinkedListADT.h"




int main() {
	List head = createEmptyList();
	Item enterData;
	while (scanf("%9d",&enterData.data))
	{
		addNewNode(head, enterData);
	}
	printList(head);
	deleteList(&head);
	printList(head);
	return 0;
}