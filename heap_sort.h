#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include "utils.h"
#include "assert.h"
#include <iostream>
#include "array.h"


template <typename T>
class heap_sort {
public:
    static void sort(T* pq, int n, const comparator<T>& comp = fwd_comparator<T>()) {
       
        // heapify phase
        for (int k = n / 2; k >= 1; k--)
            sink(pq, k, n, comp);

        // sortdown phase
        int k = n;
        while (k > 1) {
            exchange(pq, 1, k--);
            sink(pq, 1, k, comp);
        }
    }

private:
    static void sink(T* pq, int k, int n, const comparator<T>& comp) {
        while (2 * k <= n) {
            int j = 2 * k;
            if (j < n && less(pq, j, j + 1, comp)) j++;
            if (!less(pq, k, j, comp)) break;
            exchange(pq, k, j);
            k = j;
        }
    }
    static bool less(T* pq, int i, int j, const comparator<T>& comp) {
        return compare(pq[i - 1], pq[j - 1], comp) < 0;
    }

    static void exchange(T* pq, int i, int j) {
        T swap = pq[i - 1];
        pq[i - 1] = pq[j - 1];
        pq[j - 1] = swap;
    }

};

template <typename T>
class MaxPQ {
public:
    
    MaxPQ() : MaxPQ(MIN_CAPACITY_) {}

    MaxPQ(size_t cap) : pq(cap) {
        pq.push_back(NULL);
    }

    MaxPQ(T* keys) {
        pq.size() = keys.size();
        pq = new T[keys.size() - 1];
        for (int i = 0; i < n; i++) {
            pq[i + 1] = keys[i];
        }
        for (int k = n / 2; k >= 1; k--) {
            sink(k);
        }
        //assert isMaxHeap();
    }

    bool isEmpty() {
        return n == 0;
    }

    int size() {
        return n;
    }

    T max() {
        if (isEmpty()) std::cout << "Priority queue underflow\n";
        return pq[1];
    }
    // was private
    void insert(const T& x, int noe) {
        if (n == noe-1) resize(2 * noe);

        pq[++n] = x;
        swim(n);
        //assert isMaxHeap();
    }
    T delMax(int noe) {
        if (isEmpty()) std::cout << "Priority queue underflow";
        T max = pq[1];
        exchange(1, n--);
        sink(1);
        pq[n + 1] = 0;
        if ((n > 0) && (n == noe - 1) / 4) resize(noe);
        //assert isMaxHeap();
        return max;
    }
private:
    
    void resize(int capacity) {
        //assert capacity > n;
        T* temp = new T[capacity];
        for (int i = 1; i <= n; i++) {
            temp[i] = pq[i];
        }
        pq = temp;
    }

    void swim(int k) {
        while (k > 1 && less(k / 2, k)) {
            exchange(k, k / 2);
            k = k / 2;
        }
    }

    void sink(int k) {
        while (2 * k <= n) {
            int j = 2 * k;
            if (j < n && less(j, j + 1)) j++;
            if (!less(k, j)) break;
            exchange(k, j);
            k = j;
        }
    }

    bool less(int i, int j) {
        if (comp == NULL) {
            return ((comparator<T>) pq[i]).compare(pq[i]) < 0;
        }
        else {
            return comp.compare(pq[i], pq[j]) < 0;
        }
    }

    void exchange(int i, int j) {
        T swap = pq[i];
        pq[i] = pq[j];
        pq[j] = swap;
    }

    bool isMaxHeap() {
        for (int i = 1; i <= n; i++) {
            if (pq[i] == NULL) return false;
        }
        for (int i = n + 1; i < pq.size(); i++) {
            if (pq[i] != NULL) return false;
        }
        if (pq[0] != NULL) return false;
        return isMaxHeapOrdered(1);
    }

    bool isMaxHeapOrdered(int k) {
        if (k > n) return true;
        int left = 2 * k;
        int right = 2 * k + 1;
        if (left <= n && less(k, left)) return false;
        if (right <= n && less(k, right)) return false;
        return isMaxHeapOrdered(left) && isMaxHeapOrdered(right);
    }

    array_<T> pq;
    const comparator<T>& comp;
    static const int MIN_CAPACITY_ = 10;
    int n = pq.size();
};

#endif