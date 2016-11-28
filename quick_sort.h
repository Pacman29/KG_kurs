#ifndef QUICK_SORT_H
#define QUICK_SORT_H
#include <omp.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>


//template <class T>
//inline int get_pivot(T *a, size_t first, size_t last)
//{
//    int half = (first + last) / 2;
//        if(a[first] < a[half])
//        {
//            if(a[last] < a[first])
//                return first;
//            else
//                if(a[last] < a[half])
//                    return last;
//            return half;
//        }
//        else
//        {
//            if(a[last] < a[half])
//                return half;
//            else
//                if(a[last] < a[first])
//                    return last;
//            return first;
//        }
//}


//template <class T>
//inline size_t partition(T* arr, size_t begin, size_t end)
//{
//    size_t pivotIndex = get_pivot(arr, begin, end);
//    if(begin != pivotIndex)
//        std::swap(arr[begin], arr[pivotIndex]);

//    size_t i = begin + 1;
//    size_t j = end;

//    while (true)
//    {
//        while (arr[i] < arr[begin])
//            i++;

//        while (arr[begin] < arr[j])
//            j--;

//        if (i < j)
//        {
//            std::swap(arr[i],arr[j]);
//            ++i;
//            --j;
//        }
//        else
//        {
//            if(begin != i-1)
//                std::swap(arr[begin],arr[i - 1]);
//            return i - 1;
//        }
//    }
//}

//template<class T>
//inline void insertion_sort(T *data, int left, int right)
//{
//    for (int i = left + 1; i < right; i++)
//    {
//        int l = 0, r = i;
//        if (data[i] < data[i - 1])
//        {
//            while (l < r)
//            {
//                int middle = (l + r) / 2;
//                if (data[middle] < data[i])
//                    l = middle + 1;
//                else
//                    r = middle;
//            }
//        }
//        else
//            continue;

//        for(int m = i-1; m>=r;--m)
//            std::swap(data[m],data[m+1]);
//    }
//}


//template <class T>
//inline void parallel_quick_sort(T *arr, int first, int last)
//{

//    if (last - first <= 10)
//    {
//        insertion_sort(arr + first, 0, last - first + 1);
//        return;
//    }
//    int p = partition( arr, first, last )-1;
//    int pp = p+2;

//    #pragma omp parallel sections shared(arr)
//    {
//        #pragma omp critical section
//            parallel_quick_sort(arr,first,pp);
//        #pragma omp critical section
//            parallel_quick_sort(arr,p,last);
//        #pragma omp nowait
//    }

//    return;
//}

//template <class T>
//void ParallelQuickSort(std::vector<T> array)
//{
//    int n = array.size();
//    #pragma omp parallel shared(array)
//    {
//        #pragma omp single nowait
//        {
//            parallel_quick_sort(array.data(),0,n-1);
//        }
//    }
//    #pragma omp barrier
//}


template <class T>
void ParallelQuickSort(std::vector<T> array)
{
    int n = array.size();
    quickSort(array.data(),0,n-1);
}

template <class T>
void quickSort(T *data, int left, int right)
{
    int left1 = left;
    int right1 = right;
    double p;
    double ref = data[(left+right)/2];

    do{
        while(data[left1] < ref)left1++;
        while(data[right1] > ref)right1--;
        if(left1<=right1){
            if(data[left1] > data[right1])
                data[left1]  = (p = data[right1], data[right1] = data[left1], p);
            left1++;
            right1--;
        }
    }while (left1 <= right1);

      #pragma omp parallel sections
      {
         #pragma omp section
    if(left1 < right)
        quickSort(data, left1, right);

         #pragma omp section
    if(left < right1)
        quickSort(data, left, right1);
      }
}

#endif // QUICK_SORT_H
