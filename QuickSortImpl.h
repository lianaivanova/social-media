#ifndef SOCIALMEDIA_QUICKSORTIMPL_H
#define SOCIALMEDIA_QUICKSORTIMPL_H
#include <vector>

template<typename T>
void swap(T *a, T *b) {
    T t = *a;
    *a = *b;
    *b = t;
}

template<typename T>
int partition(vector<T> &elements, int low, int high) {
    T pivot = elements[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (elements[j] < pivot) {
            i++;
            swap(&elements[i], &elements[j]);
        }
    }
    swap(&elements[i + 1], &elements[high]);
    return (i + 1);
}

template<typename T>
void quickSort(vector<T> &elements, int low, int high) {
    if (low < high) {
        int pi = partition(elements, low, high);

        quickSort(elements, low, pi - 1);
        quickSort(elements, pi + 1, high);
    }
}

#endif //SOCIALMEDIA_QUICKSORTIMPL_H
