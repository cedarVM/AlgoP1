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
 * In order for the in-place algorithm to work, the most convenient
 * pivot is chosen at the end of the sample. Unfortunately, this means
 * any logic attempting to make the pivot, say, the beginning of the
 * sample would be a nightmare, disbarring a hack found in quick.0.c
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

int pivot = arr[func(n)];

int first, last, temp;
int bottom_l, top_l;

first = 0;
last = n - 2;

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
  top_l = n - last - 1;

  //printf("%d %d\n", bottom_l, top_l);
  //fgetc(stdin);


  ins[bottom_l] = pivot;

  if (bottom_l == 1) {
    ins[0] = arr[0];
  } else if (bottom_l == 0) {
    ;
  } else {
    sort(arr, ins, bottom_l, func); // bottom
  }

  if (top_l == 1) {
    ins[bottom_l + 1] = arr[bottom_l];
  } else if (top_l == 0) {
    ;
  } else {
    sort(arr + last, ins + last + 1, top_l, func); // top
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
  sort(arr, sorted, SIZE, last);
  end = clock();

  printf("%d %d\n", end - init, SIZE);

  for (int i = 0; i < SIZE; i++) {
  //printf("%d\n", sorted[i]);
  }

}

}
