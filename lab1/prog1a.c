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
	/*int allocate_new[prcs_size];
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
	printTable(process,prcs_size,allocate_new);*/

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
	/*int allocation[prcs_size];
 
    // Initially no block is assigned to any process
    memset(allocation, -1, sizeof(allocation));
 
    // pick each process and find suitable blocks
    // according to its size ad assign to it
    for (int i=0; i<prcs_size; i++)
    {
        for (int j=0; j<blk_size; j++)
        {
            if (block[j] >= process[i])
            {
                // allocate block j to p[i] process
                allocation[i] = j;
 
                // Reduce available memory in this block.
                block[j] -= process[i];
 
                break;
            }
        }
    }*/
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