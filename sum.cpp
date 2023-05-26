#include<iostream>
#include<omp.h>

using namespace std;

int main()
{
	int n;
	cout<<"enter the size of array ";
	cin>>n;
	int data[n];
	
	for(int i=0; i<n;i++)
	{
		cin>>data[i];
	}
	
	omp_set_num_threads(4);
	
	int min_value = INT_MAX;
	#pragma omp prallel for reduction (min:min_value)
	for(int i=0; i<n;i++)
	{
		if(data[i]<min_value)
			min_value=data[i];
	}
	
	int max_value = INT_MIN;
	#pragma omp prallel for reduction (max:max_value)
	for(int i=0; i<n;i++)
	{
		if(data[i]>max_value)
			max_value=data[i];
	}
	
	int sum=0;
	#pragma omp prallel for reduction (+:sum)
	for(int i=0; i<n;i++)
	{
		sum+=data[i];
	}
	
	double average = sum;
	
	average=average/n;
	
	cout<<"no of threads"<<omp_get_max_threads();
	cout<<"sum = "<<sum<<"\nav"<<average<<"\nmin"<<min_value<<"\nmax"<<max_value;
	return 0;
}