#include<stdio.h>

void swap(int *a, int *b){
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;

}

void print(int a[], int n){
	int i;

	for (i=0;i<n;i++){
		printf("%d ",a[i]);
}

	printf("\n");
}

void bubbleSort(int a[], int n){
	int i,j;

	for (i=0; i<n; i++){

		for (j=0; j<n-i-1; j++){

			if ( a[j] > a[j+1] ){
				swap(&a[j+1],&a[j]);
			}

		}

	}

	print(a,n);
}


void selectionSort(int a[], int n){
	int i,j,min_i;

	for( i=0; i<n; i++ ){
		min_i=i;

		for(j=i+1; j<n; j++ ){

			if( a[j] < a[min_i] ){
				min_i=j;
				swap(&a[j],&a[min_i]);
			}

		}
	}

	print(a,n);
}

void insertionSort(int a[], int n){
	int i,j,k;

	for (i=1; i<n; i++){
	
		k=a[i];
		j=i-1;
	
		while (j>=0 && a[j]> k){
			a[j+1]=a[j];
			j--;
		}
	
		a[j+1]=k;
	}
	
	print(a,n);
}


void main(){
	int i,a[5];
	printf("%s\n","Enter the array Elements: " );
	for (i=0;i<5;i++){
		scanf("%d",&a[i]);
	}
	printf("%s","Bubble Sort: ");
	bubbleSort(a,5);
	printf("%s","Selection Sort: ");
	selectionSort(a,5);
	printf("%s","Insertion Sort: ");
	insertionSort(a,5);
	
}