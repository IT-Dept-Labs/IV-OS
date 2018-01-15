#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node
{
	int size;
	struct node *next;
	char type;
	
};

void append(struct node** head_ref, int new_data)
{
    
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
 
    struct node *last = *head_ref; 
    new_node->size  = new_data;
    new_node->type = 'P';
    new_node->next = NULL;
 
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    }  
      
    while (last->next != NULL)
        last = last->next;
  
    last->next = new_node;
    return;    
}

void printProc(struct node *head){
	while(head!=NULL){
		if(head->type=='P'){
			printf("Process:%d\n",head->size );
		}
		else
			printf("Hole:%d\n",head->size );
		head=head->next;
	}
}

// void bestFit(int block[], int blk_size, int process[], int prcs_size){
// 	int allocate[prcs_size];
// 	memset(allocate,-1,sizeof(allocate));

// 	int i,j,indx;
// 	for(i=0;i<prcs_size;i++){
// 		indx=-1;
// 		for(j=0;j<blk_size;j++){
// 			if(block[j]>=process[i]){
// 				if(indx==-1)
// 					indx=j;
// 				else if(block[indx]>=block[j])
// 					indx=j;
// 			}
// 		}
// 		if(indx!=-1){
// 			allocate[i]=indx;
// 			block[indx]=block[indx]-process[i];
// 		}
// 	}
// 	printTable(process,prcs_size,allocate);
// }


int main(){
	int n=400;
	struct node *head_ref=NULL;
	
	int process[]={88,54,72,96,48,42};

	printf("Block Size: %d\n\n",n);
	printf("Initial Process:\n\n" );
	for (int i = 0; i < 6; ++i)
		printf("|  %d  ",process[i]);
	printf("|\n");

	for (int i=0;i<6;i++){
		append(&head_ref,process[i]);
	}

	printProc(head_ref);
	return 0;



}