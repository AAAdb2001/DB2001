#include<iostream>
#include<omp.h>
using namespace std;

int main()
{
	int arr[20];
	int i,j,n,first;
	cout<<"enter size :";
	cin>>n;
	for(int i=0; i<n;i++)
	{
		cin>>arr[i];
	}
for(int i=0; i<n;i++)
	{
		cout<<arr[i];
	}

	cout<<"\n";
	#pragma omp parallel for shared(arr,n,first)
	for(i=0;i<n;i++)
	{
		first=i%2;
		
		for(j=first;j<n-1;j++)
		{
			if(arr[j]>arr[j+1])
			{
				int temp = arr[j];
				arr[j]=arr[j+1];
				arr[j+1]= temp;
			}
		}
	}
	
	for(int k=0;k<n;k++)
		cout<<arr[k]<<" ";
		
	return 0;
}