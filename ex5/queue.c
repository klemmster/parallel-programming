

void enqueue(struct queue* q, int data) {
   node* tailSave = NULL;
   node** toChange = NULL;
   int successful = 0;

   node* n = malloc(sizeof(node));
   n->data = data;
   n->next = NULL;
   
   // insert new node at the tail
   do {
	tailSave = q->tail;
	
	if(tailSave) {
	  successful = CAS(&(tailSave->next), NULL, n);
	}
	else {
	  successful = CAS(&(q->tail), NULL, n);
	}
   } while(!successful);
   
   // correct tail pointer if needed
   do {
	tailSave = q->tail;
   } while(tailSave != NULL && tailSave->next != NULL && !CAS(&(q->tail), tailSave, tailSave->next));
   
   // set head to tail if needed
   if(!head) {
	CAS(&head, NULL, tail);
   }
}