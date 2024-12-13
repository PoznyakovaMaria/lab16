#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>

#define N 100

double* full_elements(double* ptr_array, int size); //���������� ������� ���������� ����������� �������
double* calc_elements(double* ptr_array, int size); //��������� ��������� ������� (��������� ������������� ���������)
void put_elements(double* ptr_array, int size); //����� �������
double* full_random(double* ptr_array, int size); //���������� ���������� ������������� ����������
int delete_max(double* ptr_array, int* size); //�������� ��������� ��-��
double* insert(double* ptr_arr, int* size2); //��������� -999

double* full_elements(double* ptr_array, int size) {
    double sh = (4. - 2) / (size - 1);
    double x = 2.0;
    for (int i = 0; i < size; i++) {
        ptr_array[i] = pow(x, 3) + 3 * pow(x, 2) - 3;
        x += sh;
    }
    return ptr_array;
}

double* calc_elements(double* ptr_array, int size) {
    for (int i = 0; i < size; i++) {
        if (ptr_array[i] < 0) {
            ptr_array[i] = 0;
        }
    }
    return ptr_array;
}

void put_elements(double* ptr_array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%f ", ptr_array[i]);
    }
    printf("\n");
}

double* full_random(double* ptr_array, int size) {
    int XMIN = -10, XMAX = 10;
    for (int i = 0; i < size; i++) {
        ptr_array[i] = XMIN + (rand() / (double)RAND_MAX) * (XMAX - XMIN);
    }
    return ptr_array;
}

//�������� ���� ������������ ���������
int delete_max(double* ptr_array, int* size) {
    if (*size < 2) {
        return *size;
    }
    int max1_idx = 0, max2_idx = -1;

    //������� ������� ���� ������������ ���������
    for (int i = 1; i < *size; i++) {
        if (ptr_array[i] > ptr_array[max1_idx]) {
            max2_idx = max1_idx; 
            max1_idx = i;
        }
        else if (max2_idx == -1 || ptr_array[i] > ptr_array[max2_idx]) {
            max2_idx = i;
        }
    }
    //������� ��� ������������ ��������
    for (int i = max1_idx; i < (*size - 1); i++) {
        ptr_array[i] = ptr_array[i + 1];
    }
    (*size)--;
    if (max2_idx > max1_idx) {
        for (int i = max2_idx; i < (*size - 1); i++) {
            ptr_array[i] = ptr_array[i + 1];
        }
    }
    else {
        for (int i = max2_idx; i < (*size - 1); i++) {
            ptr_array[i] = ptr_array[i + 1];
        }
    }
    (*size)--;
    return *size;
}
double* insert(double* ptr_arr, int* size2) {
    int minI = 0;
    for (int i = 1; i < *size2; i++) {
        if (ptr_arr[i] < ptr_arr[minI]) {
            minI = i;
        }
    }
    int size_n = (*size2) + 2;

    double* ptr_arr_n = (double*)realloc(ptr_arr, size_n * sizeof(double));
    if (ptr_arr_n == NULL) {
        return ptr_arr;
    }

    ptr_arr = ptr_arr_n;

    for (int i = size_n - 1; i > minI + 1; --i) {
        ptr_arr[i] = ptr_arr[i - 2];
    }

    ptr_arr[minI] = -999; //��������� ����� �����������
    ptr_arr[minI + 1] = -999; //��������� ����� ������������

    *size2 = size_n;
    return ptr_arr;
}

int main() {
    setlocale(LC_ALL, "RUS");
    double* ptr_array;
    int size;
    printf("������� ����������� �������:  ");
    scanf("%d", &size);

    //��������� ������
    ptr_array = (double*)malloc(size * sizeof(double));
    if (ptr_array == NULL) {
        puts("���������� ��� ���");
        return -1;
    }
    // 1
    full_elements(ptr_array, size);
    calc_elements(ptr_array, size);
    printf("���������� ���������� ����������� �������:  \n");
    put_elements(ptr_array, size);
    free(ptr_array);
    // 2
    double* ptr_array2;
    int size1;
    printf("������� ����������� �������:    ");
    scanf("%d", &size1);

    //��������� ������
    ptr_array2 = (double*)malloc(size1 * sizeof(double));
    if (ptr_array2 == NULL) {
        puts("���������� ��� ���");
        return -1;
    }

    full_random(ptr_array2, size1);
    printf("���������� ���������� �������:   \n");
    put_elements(ptr_array2, size1);
    printf("\n");

    delete_max(ptr_array2, &size1);
    printf("�������� ���� ������������ ���������:   \n");
    put_elements(ptr_array2, size1);
    printf("\n");
    free(ptr_array2);

    printf("������� ����������� ������� > 6:   ");
    int size2;
    scanf("%d", &size2);
    double* ptr_arr = (double*)malloc(size2 * sizeof(double));
    if (ptr_arr == NULL) {
        puts("���������� ��� ���");
        return -1;
    }
    full_random(ptr_arr, size2);
    ptr_arr = insert(ptr_arr, &size2);
    printf("\n������� -999 �� � ����� ������������ �������� � �������\n");
    put_elements(ptr_arr, size2);
    free(ptr_arr);
    return 0; 
}
