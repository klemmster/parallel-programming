

void enqueue(struct queue* q, int data) {
   node* tailSave = NULL;
   node** toChange = NULL;

   node* n = malloc(sizeof(node));
   n->data = data;
   n->next = NULL;
   
   // insert new node at the tail
   do {
	tailSave = q->tail;
	toChange = NULL;
	
	if(tailSave) {
	  toChange = &(tailSave->next);
	}
	else {
	  toChange = &(q->tail);
	}
   } while(!CAS(toChange, tailSave, n));
   
   // correct tail pointer if needed
   do {
	tailSave = q->tail;
   } while(tailSave != NULL && tailSave->next != NULL && !CAS(&(q->tail), tailSave, tailSave->next));
   
   // set head to back if needed
   if(!head) {
	CAS(&front, NULL, back);
   }
}