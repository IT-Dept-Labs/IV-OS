#include <stdio.h>
#include <string.h>


void printTable(int process[], int n,int allocate[]){
	printf("%s\t\t%s\n","Process","Block");
	int i=0;
	for(i=0;i<n;i++){
		if(allocate[i]!=-1)
			printf("%d\t\t%d\n",process[i],allocate[i]+1);
		else
			printf("%d\t\t%s\n",process[i],"Unallocated");
	}
}



void bestFit(int block[], int blk_size, int process[], int prcs_size){
	int allocate[prcs_size];
	memset(allocate,-1,sizeof(allocate));

	int i,j,indx;
	for(i=0;i<prcs_size;i++){
		indx=-1;
		for(j=0;j<blk_size;j++){
			if(block[j]>=process[i]){
				if(indx==-1)
					indx=j;
				else if(block[indx]>=block[j])
					indx=j;
			}
		}
		if(indx!=-1){
			allocate[i]=indx;
			block[indx]=block[indx]-process[i];
		}
	}
	printTable(process,prcs_size,allocate);
}



void worstFit(int block[], int blk_size, int process[], int prcs_size){
	int allocate_new[prcs_size];
	memset(allocate_new,-1,sizeof(allocate_new));

	int i,j,indx;
	for(i=0;i<prcs_size;i++){
		indx=-1;
		for(j=0;j<blk_size;j++){
			if(block[j]>=process[i]){
				if(indx==-1)
					indx=j;
				else if(block[indx]<block[j]){
					indx=j;
					
				}
			}
		}
		if(indx!=-1){
			allocate_new[i]=indx;
			block[indx]=block[indx]-process[i];
		}
	}
	printTable(process,prcs_size,allocate_new);
}



void firstFit(int block[], int blk_size, int process[], int prcs_size){
	int allocate_new[prcs_size];
	memset(allocate_new,-1,sizeof(allocate_new));

	int i,j;
	for(i=0;i<prcs_size;i++){
		for(j=0;j<blk_size;j++){
			if(block[j]>=process[i]){
				allocate_new[i]=j;
				block[j]=block[j]-process[i];
				break;
		}
	}
	}
	printTable(process,prcs_size,allocate_new);

}



int main(){
	
	int block[]={100, 500, 200, 300, 600};
	int block1[5],block2[5],i;

	for(i=0;i<5;i++){

		block1[i]=block[i];
		block2[i]=block[i];

	}

	int process[]={212, 417, 112, 426,325};
	int blk_size=sizeof(block)/sizeof(block[0]);
	int prcs_size=sizeof(process)/sizeof(process[0]);

	printf("\n\tBlock\n\n");
	for(i=0;i<5;i++)
		printf("Block %d: \t%d\n",i,block[i]);

	printf("\n\n\tProcess\n\n");
	for(i=0;i<5;i++)
		printf("Process %d:\t%d\n",i,process[i]);

	printf("\n\n\n");
	printf(" \t%s\n\n","Best Fit " );
	bestFit(block,blk_size,process,prcs_size);

	printf("\n\tFragmentation\n\n");
	for(i=0;i<5;i++)
		printf("Block %d: \t%d\n",i,block[i]);


	printf("\n\n\n");
	printf(" \t%s\n\n","Worst Fit " );
	worstFit(block1,blk_size,process,prcs_size);

	printf("\n\tFragmentation\n\n");
	for(i=0;i<5;i++)
		printf("Block %d: \t%d\n",i,block1[i]);


	printf("\n\n\n");
	printf(" \t%s\n\n","First Fit " );
	firstFit(block2,blk_size,process,prcs_size);

	printf("\n\tFragmentation\n\n");
	for(i=0;i<5;i++)
		printf("Block %d: \t%d\n",i,block2[i]);


	return 0;

}