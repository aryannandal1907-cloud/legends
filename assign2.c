#include<stdio.h>
#include<stdlib.h>

void bubble_sort(int a[],int n){
    int i,j,temp;
    for(i=0;i<n-1;i++){
        for(j=0;j<n-1;j++){
            if(a[j]>a[j+1]){
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
}

void selection_sort(int a[],int n){
    int min_index,i,j,temp;
    for(i=0;i<n;i++){
        min_index=i;
        for(j=i+1;j<n;j++){
            if(a[j]<a[min_index]){
                min_index=j;
            }
            if(min_index!=i){
                temp=a[i];
                a[i]=a[min_index];
                a[min_index]=temp;
            }
        }
    }
}


int main(){
    int i,j,n1,n2,ch;
    printf("Enter the size of the array 1;-- ");
    scanf("%d",&n1);
    int a[n1];

    for(i=0;i<n1;i++){
        printf("The elements to be entered are;--");
        scanf("%d",&a[i]);
    }
    for(i=0;i<n1;i++){
        printf("The elements in the array are;--%d\n ",a[i]);
    }

    printf("Enter the size of the array 2;-- ");
    scanf("%d",&n2);
    int b[n2];

    for(j=0;j<n2;j++){
        printf("The elements to be entered are;-- ");
        scanf("%d",&b[j]);
    }
    for(j=0;j<n2;j++){
        printf("The elements in the array are;--%d\n ",b[j]);
    }
    while(1){
            printf("----------MENU---------\n");
            printf("1.Bubble sort\n");
            printf("2.Selection sort\n");
            printf("3.Top 5 elements\n");
            printf("4.Exit\n");
            printf("Enter your choice\n");
            scanf("%d",&ch);
            switch(ch){
                case 1:
                printf("Bubble sort");
                bubble_sort(a,n1);
                for(i=0;i<n1;i++){
                    printf("%d \t \n",a[i]);
                    printf("\n");
                }
                break;
                case 2:
                printf("Selection sort");
                selection_sort(b,n2);

                for(j=0;j<n2;j++){
                    printf("%d \t",b[j]);
                    printf("\n"); 
                }
                break;
                case 3:
                printf("The top 5 elements of array 1 are;--");
                for(i=n1-1;i=n1-5;i--){
                    printf("%d",a[i]);
                }
                printf("The top 5 elements of array 2 are;--");
                for(j=n2-1;j=n2-5;j--){
                    printf("%d",b[j]);
                }  
                 break;
                 case 4:
                 exit(0);
                 default:
                 printf("Wrong msg");
                }
    }

}
     

