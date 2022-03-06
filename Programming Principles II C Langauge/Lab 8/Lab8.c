#include <stdio.h>
#include <math.h>

int isAscending(int array[], int array_size, int index);
int binary_search(int array[], int array_size, int num_to_search, int index);

#define MAX 20

int main(void){
    int array_elements,
        i,
        search_num;
    int array[MAX];


    printf("Input the number of elements to store in the array: ");
    scanf("%d", &array_elements);

    printf("Input %d elemnts to the array:\n", array_elements);
    for(i = 0; i < array_elements; ++i){
        printf("element - %d: ", i);
        scanf("%d", &array[i]);
    }

    if(isAscending(array, array_elements, 0)){
        printf("Input the number to search: ");
        scanf("%d", &search_num);
        printf("\nFound number %d in index %d\n\n", search_num, binary_search(array, array_elements, search_num, 0));
    }
    else{
        printf("Array not in order! Please enter array in order.\n");
    }

    return 0;
}

int isAscending(int array[], int array_size, int index){
    int return_value;

    if((array[index] < array[index + 1]) || (array[index] == array[index + 1])){
        return_value = 1;
        if(index < (array_size - 2)){
            return_value = isAscending(array, array_size, index + 1);
        }
    }
    else{
        return_value = 0;
    }
    return return_value;
}

int binary_search(int array[], int array_size, int num_to_search, int index){
    int i,
        return_value;

    if(array_size >= 1){
        if(num_to_search == array[array_size / 2]){
            return_value = array_size/2; 
        }
        /* left array */
        if(num_to_search < array[array_size / 2]){
            return_value = binary_search(array, array_size-1, num_to_search, index);
        }
        
        /* right array */
        if(num_to_search > array[(int)floor((array_size/2.0))]){
            return_value = binary_search(array, array_size+1, num_to_search, index);
        }
    }
    return return_value;
}

int ascending_order(int array[], int array_size){

    return 0;
}