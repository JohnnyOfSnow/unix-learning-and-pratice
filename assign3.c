#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
int** get2DArray(int row, int col);
void inputDataInArray(int **array, int row, int col);
void deletePointer(int **array, int row, int *acuArray);
void printDataArray(int **dataArray, int row, int col);
int* getAccumulateArray(int **dataArray, int row, int col, int size);
void histogramEqualization(int **dataArray, int row, int col, int *acuArray, int size);
int main(){
    int row = 2;
    int col = 3;
    int size = 256;
    // printf("please enter two number array width and length\n");
    while(scanf("%d", &row) != EOF && scanf("%d", &col) != EOF){

    // scanf("%d", &row);
    // scanf("%d", &col);

        int **myArray = get2DArray(col, row);

        inputDataInArray(myArray, col, row);
    //printf("\n");

        int *accumulateArray = getAccumulateArray(myArray, col, row, size);
        histogramEqualization(myArray, col ,row, accumulateArray, size);
        printDataArray(myArray, col, row);

        deletePointer(myArray, col, accumulateArray);
    }
    system("pause");
    return 0;
}

int** get2DArray(int row, int col){
    int **array2d = (int**) malloc( (row)*sizeof(int*) );
    int r, c;

    /** Start to create two dimision array */
    if(array2d == NULL){
        return NULL;
    }else{

        for(r = 0; r < row; ++r){
            array2d[r] = (int*) malloc( col * sizeof(int) );
            if(array2d[r] == NULL){
                for(c = r - 1; c >=0; --c)
                    free(array2d[c]);

                        free(array2d);
                        return NULL;
            }

        }
    }
    return array2d;
}

void inputDataInArray(int **array, int row, int col){
    //printf("Start to enter data\n");

    int r, c;
    int data;
    /** Start to fill data in array */
    for(r = 0; r < row; ++r){
        for(c = 0; c < col; c++){
            scanf("%d", &data);
            array[r][c] = data;
        }
    }
}

void deletePointer(int **array, int row, int *acuArray){
    int r;
    for(r = 0; r < row; ++r){
        free(array[r]);
    }
    free(array);
    free(acuArray);

}

void printDataArray(int **dataArray, int row, int col){
    //printf("Start to print data\n");
    int r, c;

    for(r = 0; r < row; r++){
        for(c = 0; c < col; c++){
            printf("%d ", dataArray[r][c]);
        }
        printf("\n");
    }
}

int* getAccumulateArray(int **dataArray, int row, int col, int size){
    int *data = (int*) malloc( sizeof(int) * size);

    if(data == NULL){
        return NULL;
    }

    int r,c;
    for(r = 0; r < size; r++){
        data[r] = 0;
    }

    for(r = 0; r < row; r++){
        for(c = 0; c < col; c++){
            data[dataArray[r][c]]++;
        }
    }
    return data;
}

void histogramEqualization(int **dataArray, int row, int col, int *acuArray, int size){
    int r, c;
    int cdfMin = 0;
    int time = 0;
    int front, back;
    int getData;
    int equalizationValue;
    int son;
    int mon;
    double temp;

    /** Do a accumulated array */
    for(r = 0; r < size; r++){
        if(acuArray[r] != 0){
            if(time == 0){
                front = r;
                time = time + 1;
            }else{
                acuArray[r] = acuArray[r] + acuArray[front];
                front = r;
            }
        }
    }

    /** Search for cdfMin */
    for(r = 0; r < size; r++){
        if(acuArray[r] != 0){
            cdfMin = acuArray[r];
            break;
        }
    }

    double doubleSize = (double)(size - 1);

    /** Start to histogram equalization */
    for(r = 0; r < row; ++r){
        for(c = 0; c < col; c++){
            getData = dataArray[r][c];
            son = acuArray[getData] - cdfMin;
            mon = (row * col) - cdfMin;
            temp = ((double)son / (double)mon);

            equalizationValue = (int) (round(temp * doubleSize));
            dataArray[r][c] = equalizationValue;
        }
    }
}
 ESCOD
    /** Do a accumulated array */
    for(r = 0; r < size; r++){
        if(acuArray[r] != 0){
            if(time == 0){
                front = r;
                time = time + 1;
            }else{
                acuArray[r] = acuArray[r] + acuArray[front];
                front = r;
            }
        }
    }

    /** Search for cdfMin */
    for(r = 0; r < size; r++){
        if(acuArray[r] != 0){
            cdfMin = acuArray[r];
            break;
        }
    }

    double doubleSize = (double)(size - 1);

    /** Start to histogram equalization */
    for(r = 0; r < row; ++r){
        for(c = 0; c < col; c++){
            getData = dataArray[r][c];
            son = acuArray[getData] - cdfMin;
            mon = (row * col) - cdfMin;
            temp = ((double)son / (double)mon);

            equalizationValue = (int) (round(temp * doubleSize));
            dataArray[r][c] = equalizationValue;
        }
    }
}
