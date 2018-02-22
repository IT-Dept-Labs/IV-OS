#include <iostream>

using namespace std;

/* 
* Simulating the first come first serve scheduking algorithm
* @param at refers to arrival time and et refers to execution time
*/
void FCFS(int at[],int et[],int n){

	int ct[n];   		// ct is completion time
	ct[0]=et[0];

	/* Computing the completion time
	*/
	for(int i=1;i<n;i++){
		ct[i]=et[i]+ct[i-1];
	}

	/*
	* Displayng the completion time
	*/
	cout<<"\t\tCompletion Time: "<<"\n\n";
	for(int i=0;i<n;++i){
		cout<<"Process "<<i<<"\t\t"<<ct[i]<<'\n';
	}

	
	/*
	*Computing the waiting time
	*/

	int wt[n];  		//wt is waiting time

	wt[0]=at[0];
	for(int i=1;i<n;++i){
		wt[i]=ct[i-1]-at[i];

	}


	/*
	* Displayng the waiting time
	*/
	cout<<"\n\n\t\tWaiting Time: "<<"\n\n";
	for(int i=0;i<n;++i){
		cout<<"Process "<<i<<"\t\t"<<wt[i]<<'\n';
	}


	/*
	* Computing the average waiting time
	*/
	int sum=0;
	for(int i=0;i<n;i++){
		sum+=wt[i];
	}
	cout<<"\n\n\t Average: "<<(double)sum/n<<'\n';

}


/*
* Simulates the Shortest Job First Scheduking Algorithm
* @param at refers to arrival time and et refers to execution time
*/
void SJF(int[] at,int[] et, int n){

}

int main(int argc, char const *argv[])
{
	
	int at[]={0,1,2,3};
	int et[]={5,3,8,6};
	FCFS(at,et,4);
	return 0;
}