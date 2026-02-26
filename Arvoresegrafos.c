#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int arr[], int n){
    for(int i=0;i<n;i++)
        printf("%d ",arr[i]);
    printf("\n");
}

void copyArray(int origem[], int destino[], int n){
    for(int i=0;i<n;i++)
        destino[i]=origem[i];
}

void generateArray(int arr[], int n){
    for(int i=0;i<n;i++)
        arr[i]=rand()%1000;
}

void swap(int *a,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

void bubbleSort(int arr[], int n){
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(arr[j]>arr[j+1])
                swap(&arr[j],&arr[j+1]);
}

void selectionSort(int arr[], int n){
    for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i+1;j<n;j++)
            if(arr[j]<arr[min])
                min=j;
        swap(&arr[i],&arr[min]);
    }
}

void insertionSort(int arr[], int n){
    for(int i=1;i<n;i++){
        int key=arr[i];
        int j=i-1;
        while(j>=0 && arr[j]>key){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
}

int partitionQS(int arr[], int low, int high){
    int pivot=arr[high];
    int i=low-1;
    for(int j=low;j<high;j++){
        if(arr[j]<pivot){
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[i+1],&arr[high]);
    return i+1;
}

void quickSort(int arr[], int low, int high){
    if(low<high){
        int pi=partitionQS(arr,low,high);
        quickSort(arr,low,pi-1);
        quickSort(arr,pi+1,high);
    }
}

void merge(int arr[], int l, int m, int r){
    int n1=m-l+1;
    int n2=r-m;

    int *L=(int*)malloc(n1*sizeof(int));
    int *R=(int*)malloc(n2*sizeof(int));

    for(int i=0;i<n1;i++) L[i]=arr[l+i];
    for(int j=0;j<n2;j++) R[j]=arr[m+1+j];

    int i=0,j=0,k=l;

    while(i<n1 && j<n2){
        if(L[i]<=R[j])
            arr[k++]=L[i++];
        else
            arr[k++]=R[j++];
    }

    while(i<n1) arr[k++]=L[i++];
    while(j<n2) arr[k++]=R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r){
    if(l<r){
        int m=(l+r)/2;
        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);
        merge(arr,l,m,r);
    }
}

void shellSort(int arr[], int n){
    for(int gap=n/2;gap>0;gap/=2){
        for(int i=gap;i<n;i++){
            int temp=arr[i];
            int j;
            for(j=i;j>=gap && arr[j-gap]>temp;j-=gap)
                arr[j]=arr[j-gap];
            arr[j]=temp;
        }
    }
}

void testSort(void (*sortFunc)(int[],int), int arr[], int n){
    int *temp=(int*)malloc(n*sizeof(int));
    copyArray(arr,temp,n);

    printf("Array antes:\n");
    printArray(temp,n);

    clock_t start=clock();
    sortFunc(temp,n);
    clock_t end=clock();

    printf("Array depois:\n");
    printArray(temp,n);

    printf("Tempo: %.6f segundos\n\n",(double)(end-start)/CLOCKS_PER_SEC);

    free(temp);
}

void testQuick(int arr[], int n){
    int *temp=(int*)malloc(n*sizeof(int));
    copyArray(arr,temp,n);

    printf("Array antes:\n");
    printArray(temp,n);

    clock_t start=clock();
    quickSort(temp,0,n-1);
    clock_t end=clock();

    printf("Array depois:\n");
    printArray(temp,n);

    printf("Tempo: %.6f segundos\n\n",(double)(end-start)/CLOCKS_PER_SEC);

    free(temp);
}

void testMerge(int arr[], int n){
    int *temp=(int*)malloc(n*sizeof(int));
    copyArray(arr,temp,n);

    printf("Array antes:\n");
    printArray(temp,n);

    clock_t start=clock();
    mergeSort(temp,0,n-1);
    clock_t end=clock();

    printf("Array depois:\n");
    printArray(temp,n);

    printf("Tempo: %.6f segundos\n\n",(double)(end-start)/CLOCKS_PER_SEC);

    free(temp);
}

int main(){
    srand(time(NULL));

    int n;
    printf("Tamanho do array: ");
    scanf("%d",&n);

    int *arr=(int*)malloc(n*sizeof(int));
    generateArray(arr,n);

    int op;

    do{
        printf("\n=== MENU ===\n");
        printf("1 - Bubble Sort\n");
        printf("2 - Selection Sort\n");
        printf("3 - Insertion Sort\n");
        printf("4 - Quick Sort\n");
        printf("5 - Merge Sort\n");
        printf("6 - Shell Sort\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d",&op);

        switch(op){
            case 1: testSort(bubbleSort,arr,n); break;
            case 2: testSort(selectionSort,arr,n); break;
            case 3: testSort(insertionSort,arr,n); break;
            case 4: testQuick(arr,n); break;
            case 5: testMerge(arr,n); break;
            case 6: testSort(shellSort,arr,n); break;
        }

    }while(op!=0);

    free(arr);
    return 0;
}