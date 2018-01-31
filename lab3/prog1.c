#include <stdio.h>
#include <stdlib.h>

struct Node
{
 
  int size;
  struct Node *next;
  char type;
};



void allocate(struct Node** head_ref, int new_size)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
 
    struct Node *last = *head_ref;

    new_node->size  = new_size;

    new_node->type= 'P';
 
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



void merge(struct Node* ref){

    while(ref->next!=NULL){

        if(ref->type=='H' && ref->next->type=='H'){

            ref->size=ref->size+ref->next->size;

            ref->next=ref->next->next;
 
        }

        ref=ref->next;
    }

}

void deallocate(struct Node* node,int pro_size){
	struct Node* head=node;
    while(node!=NULL){

        if(node->size==pro_size){

            node->type='H';

           
        }

        node=node->next;

    }
  //  merge(head);

}


void firstFit(struct Node* node,int pro_size){

    int rem;

    while(node!=NULL){

        if(node->type=='H' && node->size>=pro_size){

            node->type='P';

            rem=node->size-pro_size;

            node->size=pro_size;

            struct Node* new_node=(struct Node*) malloc(sizeof(struct Node));

            new_node->size=rem;

            new_node->type='H';

            new_node->next=node->next;

            node->next=new_node;

            break;


        }

        node=node->next;

    }

}

void bestFit(struct Node* node,int pro_size){

    int rem;

    while(node!=NULL){

        if(node->type=='H' && node->size>=pro_size){

            node->type='P';

            rem=node->size-pro_size;

            node->size=pro_size;

            struct Node* new_node=(struct Node*) malloc(sizeof(struct Node));

            new_node->size=rem;

            new_node->type='H';

            new_node->next=node->next;

            node->next=new_node;

            break;


        }

        node=node->next;

    }

}

void worstFit(struct Node* node,int pro_size){

    int rem;

    while(node!=NULL){

        if(node->type=='H' && node->size>=pro_size){

            node->type='P';

            rem=node->size-pro_size;

            node->size=pro_size;

            struct Node* new_node=(struct Node*) malloc(sizeof(struct Node));

            new_node->size=rem;

            new_node->type='H';

            new_node->next=node->next;

            node->next=new_node;

            break;


        }

        node=node->next;

    }

}

void internalFragment(struct Node *node){

    int frag=0;

    while(node!=NULL){

        if(node->type=='H'){

            frag=frag+node->size;
        }

        node=node->next;
    }

    printf("\nTotal internal fragmentation size: %d\n",frag);

}



void print(struct Node *node)
{
  while (node != NULL)

  {    if(node->type=='P'){
   
     printf("Process size %d\n",node->size);
     }
     else{
       
        printf("Hole size %d\n",node->size);
    }
     node = node->next;
  }
}
 
int main()
{

    int totalSize=240,processSize[]={50,15,40,25,39,26,45};

    printf("Total memory available:%dKB\n\n",totalSize);

    for(int i=0;i<7;i++){

        printf("Process Number:%d   Process size:%d\n",i+1,processSize[i]);
    }

    struct Node* head=NULL;


    for(int i=0;i<7;i++){

        allocate(&head,processSize[i]);
    }

    printf("\nAfter allocating memory for each process:\n");

    print(head);

    printf("\nTerminating process numbers 2,3,5 & 7\n");

    deallocate(head,processSize[1]);

    deallocate(head,processSize[2]);

    deallocate(head,processSize[4]);

    deallocate(head,processSize[6]);

   merge(head);

    print(head);

    internalFragment(head);

    printf("\nReallocating memory for 3 processes of size 17, 35 & 48 KB\n");

    int procSize[]={17,35,48};

    int procSize1[]={48,17,35};

    int procSize2[]={17,48,35};

    printf("\nBest fit case:\n");

    for(int i=0;i<3;i++){

        bestFit(head,procSize[i]);
    }

    print(head);

    internalFragment(head);

    // deallocate(head,procSize[0]);

    // deallocate(head,procSize[1]);

    // merge(head);

    // struct Node *node=(struct Node*) malloc(sizeof(struct Node));

    // node=head;

    // while(node!=NULL){

    //     if(node->size==43){

    //         node->type='H';

    //         node->size=45;

    //         node->next=NULL;

    //     }

    //     node=node->next;

    // }

    // printf("\nWorst fit case:\n");

    // for(int i=0;i<3;i++){

    //     worstFit(head,procSize1[i]);
    // }

    // print(head);

    // internalFragment(head);


    // deallocate(head,procSize1[0]);

    // deallocate(head,procSize1[1]);

    // merge(head);

    // struct Node *node1=(struct Node*) malloc(sizeof(struct Node));

    // node1=head;

    // while(node1!=NULL){

    //     if(node1->size==38){

    //         node1->type='H';

    //         node1->size=45;

    //         node1->next=NULL;

    //     }

    //     node1=node1->next;

    // }

    // printf("\nfirst fit case:\n");

    // for(int i=0;i<3;i++){

    //     firstFit(head,procSize2[i]);
    // }

    // print(head);

    // internalFragment(head);

  return 0;
}
