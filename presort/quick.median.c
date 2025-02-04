#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

/*
 * Author: Matthew Louden
 *
 * Date: January 30th 2025
 *
 * Description:
 * (without #defines) Performs quicksort on integers valued 0-4095
 * in batches of increments of 5 for 2000 iterations. The timing
 * mechanism for this algorithm is possibly unoptimally implemented.
 * A simple delta is taken from the start of the sort function till
 * its end. Overhead logic for getting samples is not considered,
 * however.
 *
 * Description:
 * (with #defines) Performs quicksort on a hardset sample size of 700.
 * These randomized integers are defined over in presort.h and invsort.h
 *
 * Description:
 * (generally) does what quick.last.c does except the pivot is chosen to
 * be any of the three elements, at 0, n/2, or n - 1 on the partition which
 * satisfy being the property of being the median.
 *
*/

int last(int size) {
return size - 1;
}

int middle(int size) {
return size / 2;
}

int first(int size) {
return 0;
}

int median(int *arr, int n) {
  int i, j, k;
  i = 0;
  j = n / 2;
  k = n - 1;
  int max, min, tmp;
  min = i;
  max = i;

  min = arr[min] < arr[j] ? min : j;
  min = arr[min] < arr[k] ? min : k;

  max = arr[max] > arr[j] ? max : j;
  max = arr[max] > arr[k] ? max : k;

  tmp = max;
  if (min > max) {
  max = min;
  min = tmp;
  }

  if (min==i && max==k) {
  return j;
  }

  if (min==i && max==j) {
  return k;
  }

  if (min==j && max==k) {
  return i;
  }

}

void sort(int *arr, int *ins, int n) {

int where = median(arr, n);
int pivot = arr[where];
arr[where] = arr[last(n)];

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
    sort(arr, ins, bottom_l); // bottom
  }

  if (top_l == 1) {
    ins[bottom_l + 1] = arr[bottom_l];
  } else if (top_l == 0) {
    ;
  } else {
    sort(arr + last, ins + last + 1, top_l); // top
  }

}

int main(int arg, char **argv) {

srand(time(0));

  int *sorted;
  int *presort;
  int *arr;

  int temp;

  clock_t init, end;

  for (int SIZE = 1; SIZE < 10000; SIZE+=5) {

  arr = malloc(SIZE * 4);
  presort = malloc(SIZE * 4);
  sorted = malloc(SIZE * 4);

    for (int i = 0; i < SIZE; i++) {
    arr[i] = rand()&0b1111111111111;
    }

  #if defined(PRE) || defined(INV)
  sort(arr, presort, SIZE);
  memcpy(arr, presort, SIZE * 4);
  #endif

  #ifdef INV
    for (int i = 0; i < SIZE / 2; i++) {
    temp = arr[i];
    arr[i] = arr[SIZE - i - 1];
    arr[SIZE - i - 1] = temp;
    }
  #endif

    init = clock();
    sort(arr, sorted, SIZE);
    end = clock();

    printf("%d %d\n", end - init, SIZE);

    free(arr);
    free(sorted);
    free(presort);

  }

}
