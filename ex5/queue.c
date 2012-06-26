

int CAS( addressOfPtr, exspectedValue, newValue  ){
	// some magic stuff
}

void enqueue(struct queue* q, int data) {
   node* tailSave = NULL;
   node** toChange = NULL;
   int successful = 0;
	bool tailed = false;

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
		tailed = true;
	}
   } while(!successful);
   
   // correct tail pointer if needed
   do {
	tailSave = q->tail;
    if(tailSave){
		successful = CAS(&(q->tail),tailSave, tailSave->next); 
    } else {
		successful = CAS(&(q->tail),NULL, n );
	}
   } while(successful);//tailSave != NULL && tailSave->next != NULL && !CAS(&(q->tail), tailSave, tailSave->next));
   
   // set head to tail if needed
   if(!q->head) {
	CAS(&(q->head), NULL, tail);
   }
}