#include <stdlib.h>
#include <stdio.h>
#include <time.h>
/*
 * Author: Matthew Louden
 *
 * Date: January 30th 2025
 *
 * Description: Performs quicksort on integers valued 0-4095
 * in batches of increments of 5 for 2000 iterations. The timing
 * mechanism for this algorithm is possibly unoptimally implemented.
 * A simple delta is taken from the start of the sort function till
 * its end. Overhead logic for getting samples is not considered,
 * however.
 *
 * In order to "choose" the pivot as the beginning member of the sample,
 * I have simply elected to exchange the beginning and end elements of
 * the array and subarrays and carry out the logic in quick.0.c.
 *
 * */

int median(int size) {
return size/2;
}

int last(int size) {
return size - 1;
}

int begin(int size) {
return 0;
}

void sort(int *arr, int *ins, int n, int func(int)) {

float pivot = (arr[begin(n)] + arr[median(n)] + arr[last(n)]) / 3.0;
char flag = 1;

  for (int i = 0; i < n; i++) {
    flag &= arr[i]==pivot;
  }

  if (flag) {
    for (int i = 0; i < n; i++) {
      ins[i] = arr[i];
    }
    return;
  }

if (n==2) {
//printf("%f %d %d\n", pivot, arr[0], arr[1]);
}

int first, last, temp;
int bottom_l, top_l;

first = 0;
last = n - 1;

  while (last > first) {
    if (arr[first] > pivot && arr[last] < pivot) {
    temp = arr[first];
    arr[first] = arr[last];
    arr[last]  = temp;
    last--;
    first++;
    }
    if (arr[last]  >= pivot) {
    last--;
    }
    if (arr[first] <= pivot) {
    first++;
    }

  }

  if (arr[last] < pivot) {
  last++;
  }

  bottom_l = last;
  top_l = n - last;

  if (bottom_l == 0) {
    ;
  } else if (bottom_l == 1) {

    ins[0] = arr[0];

  } else {
    sort(arr, ins, bottom_l, func); // bottom
  }

  if (top_l == 0) {
    ;
  } else if (top_l == 1) {

    ins[bottom_l] = arr[bottom_l];

  } else {
    sort(arr + last, ins + last, top_l, func); // top
  }

}

int main(int arg, char **argv) {

srand(time(0));

for (int SIZE = 1; SIZE < 10000; SIZE+=5) {

int *arr = malloc(SIZE * 4);
int *sorted = malloc(SIZE * 4);

clock_t init, end;

  for (int i = 0; i < SIZE; i++) {
  arr[i] = rand()&0b1111111111111;
  //printf("%d\n", arr[i]);
  }

  init = clock();
  sort(arr, sorted, SIZE, begin);
  end = clock();

  printf("%d %d\n", end - init, SIZE);

  for (int i = 0; i < SIZE; i++) {
  //printf("%d\n", sorted[i]);
  }

  free(arr);
  free(sorted);

}

}
