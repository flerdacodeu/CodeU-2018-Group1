#include <iostream>

struct node {
    int data;
    node *next;
};

class list {
    private:
    node *head, *tail;
    
    public:
    int listSize = 0;
    list() {
      head = nullptr;
      tail = nullptr;
    }
    void appendToList(int value) {
      node *temp = new node;
      temp->data = value;
      temp->next = nullptr;
      if(head == nullptr) {
        head = temp;
        tail = temp;
      }
      else {	
        tail->next = temp;
        tail = temp;
      }
      listSize++;
    }
    int displayKthToLast(int k) {
	    node *temp = head;
	    for (int i = 0; i < listSize - k - 1; i++) {
	    	temp = temp -> next;
	    }
	    return temp->data ;
  	} 
};

int main (void) {
	list l;
	for (int i = 0; i < 4; i++)
		l.createnode(i);
	int k; std::cin >> k;
	if (k >= l.listSize || k < 0)
		std::cout << "Not possible" << std::endl;
	else
		std::cout << l.displayKthToLast(k) << std::endl;
	return 0;
}
