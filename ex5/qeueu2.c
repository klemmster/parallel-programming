
int CAS( address, expectedValue, newValue){};

class Node {

    Node(int);
    int data;
    Node* next;
}

class Queue{

    Queue(){
        head = new Node();
        tail = head;
    }

    void enqueue(int data) {

        Node *newNode = new Node(data);

         while(!CAS(tail->next, NULL, newNode)){
         }
         tail = newNode;
    }

    int dequeue(){

        Node *nextNode;

        do{
            Node *dummyNode = head;
            nextNode = dummyNode->next;
            if( tail == dummyNode ){
                return NULL;
            }
        } while(!CAS(head, dummyNode, nextNode));

        return nextNode.data;
    }

    Node *head;
    Node *tail;
}


