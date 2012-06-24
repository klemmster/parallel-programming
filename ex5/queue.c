

void enqueue(struct queue* q, int data) {
   node* tailSave = NULL;
   node** toChange = NULL;

   node* n = malloc(sizeof(node));
   n->data = data;
   n->next = NULL;
   
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
   
   do {
	tailSave = q->tail;
   } while(tailSave != NULL && tailSave->next != NULL && !CAS(&(q->tail), tailSave, tailSave->next));
   
   if(!head) {
	CAS(&front, NULL, back);
   }
}