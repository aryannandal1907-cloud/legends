#include<stdio.h>
#include<stdlib.h>

int linear_search(int a[],int key,int size);
int binary_search(int a[],int key,int size);

int main(){
    int ch,key,i;
    int size=5;
    int a[5];
    for(i=0;i<size;i++){
    printf("Enter the element int array;-");
    scanf("%d",&a[i]);
    }
     
    for(i=0;i<size;i++){
        printf("The elements in the array are:--%d\n",a[i]);
    }

    printf("Enter the key to be find--");
    scanf("%d",&key);



    do{
        printf("-----------Menu-----------\n");
        printf("1.Linear search\n");
        printf("2.Binary search\n");
        printf("3.Exit\n");
        printf("Enter your choice-\n");
        scanf("%d",&ch);
        switch(ch){
            case 1:
            printf("Linear search\n");
            printf("The key is found at %d position\n",linear_search(a,key,size));
            break;
            case 2:
            printf("Binary search\n");
            printf("The key to be found at %d position\n",binary_search(a,key,size));
            break;
            case 3:
            exit(0);
            default:
            printf("wrong msg");
        }   
    }while(ch!=3);
    return 0;
}


    int linear_search(int a[],int key,int size){
        int i;
        for(i=0;i<size;i++){
            if(key==a[i]){
                return i;
            }
        }
        return -1;
     }
    int binary_search(int a[],int key,int size){
        int high,low,mid;
        high=size-1;
        low=0;
        while(low<=high){
            mid=(low+high)/2;
            if(key==a[mid]){
                return mid;
            }
            else if(key<a[mid]){
                high=mid-1;
            }
            else{
                low=mid+1; 
            }

        }
        
    }
