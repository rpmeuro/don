#include<iostream>
#include<omp.h>

using namespace std;

void merge(int arr[],int left,int mid,int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        int *L = new int[n1];
        int *R = new int[n2];

        for(int i=0;i<n1;i++){
                L[i] = arr[left+i];
        }

        for(int j=0;j<n2;j++) {
                R[j] = arr[mid+j+1];
        }

        int i=0,j=0,k=left;
        while(i<n1 && j<n2) {
                if(L[i] <= R[j]) {
                        arr[k++] = L[i++];
                } else {
                        arr[k++] = R[j++];
                }
        }

        while(i<n1) {
                arr[k++] = L[i++];
        }

        while(j < n2) {
                arr[k++] = R[j++];
        }

        delete[] L;
        delete[] R;
}

void seq(int arr[],int l,int r) {
        if(l < r) {
                int m = (l+r)/2;
                seq(arr,l,m);
                seq(arr,m+1,r);
                merge(arr,l,m,r);
        }
}

void para(int arr[],int l,int r) {
        if(l<r) {
                int m = (l+r)/2;

                #pragma omp parallel sections
                {
                        #pragma omp section
                        para(arr,l,m);

                        #pragma omp section
                        para(arr,m+1,r);

                }
                merge(arr,l,m,r);
        }
}

int main() {
        double start,end;
        int n;
        cout<<"Enter No. of Elements : ";
        cin>>n;

        int *arr1 = new int[n];
        int *arr2 = new int[n];
        for(int i=0;i<n;i++){
                cin>>arr1[i];
                arr2[i] = arr1[i];
        }
        cout<<endl;

        start = omp_get_wtime();
        seq(arr1,0,n-1);
        end = omp_get_wtime();

        cout<<"Sequential Time : "<<end-start<<endl;

        for(int i=0;i<n;i++) {
                cout<<arr1[i]<<" ";
        }
        cout<<endl;

        start = omp_get_wtime();
        para(arr2,0,n-1);
        end = omp_get_wtime();

         cout<<"Parallel Time : "<<end-start<<endl;

        for(int i=0;i<n;i++) {
                cout<<arr2[i]<<" ";
        }
        cout<<endl;


        cout<<endl;
        delete[] arr1;
         delete[] arr2;
        return 0;
}
