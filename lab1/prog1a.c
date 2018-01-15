#include <stdio.h>
#include <string.h>

void printTable(int process[], int n,int allocate[]){
	printf("%s\t%s\n","Process","Block");
	int i=0;
	for(i=0;i<n;i++){
		if(allocate[i]!=-1)
			printf("%d\t%d\n",process[i],allocate[i]+1);
		else
			printf("%d\t%s\n",process[i],"Unallocated");
	}
}

void worstFit(int block[], int blk_size, int process[], int prcs_size){

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
	int process[]={212, 417, 112, 426};
	int blk_size=sizeof(block)/sizeof(block[0]);
	int prcs_size=sizeof(process)/sizeof(process[0]);
	printf("%s\n","Worst Fit: " );
	worstFit(block,blk_size,process,prcs_size);
	return 0;
}