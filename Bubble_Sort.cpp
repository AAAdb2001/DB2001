#include<iostream>
#include<omp.h>
using namespace std;


void swap(int &a,int &b){
	
	int temp;
	temp=a;
	a=b;
	b=temp;
}



void bubble(int array[],int n){
		
	double start = omp_get_wtime();
	for(int i=0;i<n-1;i++){
			
		for(int j=0;j<n-i-1;j++){
				
			if(array[j+1]<array[j]){
					swap(array[j+1],array[j]);
					
				}
		}
	}
	
	double end = omp_get_wtime();
    cout << "Sequential Bubble Sort:\n";
     for(int i = 0 ; i < n; i++){
         cout << array[i] << " ";
     }
    cout << endl;
    cout << "Time Required: " << end - start << endl;
}

void parallel_bubble(int arr[],int size){
	
    int array[size];
    for(int i = 0 ; i < size; i++){
        array[i] = arr[i];
    }
    
    double start = omp_get_wtime();
    for(int k = 0; k < size;k ++){
        if(k % 2 == 0){
            #pragma omp parallel for
                for(int i = 1; i < size - 1; i += 2){
                    if(array[i] > array[i+1]){
                        swap(array[i],array[i+1]);
                    }
                }
        }
        else{
            #pragma omp parallel for
                for(int i = 0; i < size - 1; i += 2){
                    if(array[i] > array[i+1]){
                        swap(array[i],array[i+1]);
                    }
                }
        }
    }
    double end = omp_get_wtime();
    cout << "Parallel Bubble Sort:\n";
     for(int i = 0 ; i < size; i++){
         cout << array[i] << " ";
     }
    cout << endl;
    cout << "Time Required: " << end - start << endl;

}

int main(){
	
	int n;
	cout<<"Enter the size of array"<<endl;
	cin>>n;
	
	
	int array[n];
	cout<<"Enter the value of array"<<endl;
	for(int i=0;i<n;i++){
		
		cin>>array[i];
	}
	
	bubble(array,n);
	parallel_bubble(array,n);
	

	

}
