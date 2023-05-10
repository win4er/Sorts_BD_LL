#ifndef SORTS_HPP
#define SORTS_HPP
//
#include <cstring>
#include <iostream>
#include <time.h>

int get_min(const int* ar, int size);
int get_max(int* ar, int size);
void swap(int& a, int& b);
void random_Fill_ar(int* ar, int size, int min, int max);
void show_ar(int* ar, int size, char element);
void bubble_sort(int *ar, int size);
void selection_sort(int* ar, int size);
void insertion_sort(int *ar, int size);
void count_sort(int *ar, int size);
void quick_sort(int* ar, int size);
static void merge(int* ar, int size);
void merge_sort(int* ar, int size);

#endif
