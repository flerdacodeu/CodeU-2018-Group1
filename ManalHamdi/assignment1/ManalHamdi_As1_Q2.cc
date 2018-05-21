#include <iostream>
using namespace std;
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
      head = NULL;
      tail = NULL;
    }
    void createnode(int value) {
      node *temp = new node;
      temp->data = value;
      temp->next = NULL;
      if(head == NULL) {
        head = temp;
        tail = temp;
        temp = NULL;
      }
      else {	
        tail->next = temp;
        tail = temp;
      }
      listSize++;
    }
    int displayKthToLast(int k) {
	    node *temp = new node;
	    temp = head;
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
	int k; cin >> k;
	if (k >= l.listSize)
		cout << "Not possible" << endl;
	else
		cout << l.displayKthToLast(k) << endl;
	return 0;
}