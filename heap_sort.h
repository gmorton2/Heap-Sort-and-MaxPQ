​
#ifndef max_pq_heap_h
#define max_pq_heap_h
​
#include "array.h"
​
#define min_capacity 3
​
//------------------------------------------------------
template <typename t>
class max_pq_heap {
public:
    max_pq_heap() : max_pq_heap(min_capacity_) { }
    max_pq_heap(const comparator<t>& compar) : max_pq_heap(min_capacity, compar) { }
    max_pq_heap(size_t capacity, const comparator<t>& compar)
        : pq_(capacity + 1), comp(compar) {
        pq_.push_back(t());
    }  // make space for skipped-over 0 entry
    ​
        max_pq_heap(const std::initializer_list<t>& li, const comparator<t>& compar)
        : max_pq_heap(li.size() + 1, compar) {
        for (const t& el : li) {
            if (el != "-") {
                insert(el);
            }
            else { std::cout << del_max() << " "; }
        }
        std::cout << "\t(" << size() << " left on the heap)\n\n";
    }
    ~max_pq_heap() {
        //    std::cout << "destroying the max_pq_heap...\n";
    }
    ​
        t max() const {
        if (empty()) { throw new std::underflow_error("no such element\n"); }
        return pq_[1];
    }
    ​
        bool empty() const { return pq_.size() == 1; }   // leaves 0 index empty
    size_t size() const { return pq_.size() - 1; }   // ditto
    ​
        // void resize(size_t capacity)     // handled by array_ class
        ​
        void clear() {
        std::cout << "clearing max_pq_heap...\n";
        while (!empty()) {
            del_max();
        }
        std::cout << *this << "\n";
    }
    ​
        void insert(const t& value) {
        pq_.push_back(value);
        //    std::cout << "in insert, pq is: " << pq_ << "\n";
        swim(size());
    }
    t del_max() {
        t maximum = pq_[1];
        size_t n = size();
        ​
            exchange(1, n);
        pq_.pop_back();
        sink(1);
        pq_[n] = t();
        //    std::cout << "at end of del_max , pq is: " << pq_ << "\n";
        return maximum;
    }
    void swim(size_t k) {
        while (k > 1 && less(k / 2, k)) {
            exchange(k, k / 2);
            k /= 2;
        }
    }
    void sink(size_t k) {
        size_t n = size();
        ​
            while (2 * k <= n) {
                size_t j = 2 * k;
                if (j < n && less(j, j + 1)) { ++j; }
                if (!less(k, j)) { break; }
                ​
                    exchange(k, j);
                k = j;
            }
    }
    friend std::ostream& operator<<(std::ostream& os, const max_pq_heap& maxpq) {
        if (maxpq.empty()) { return os << "max_pq_heap is empty\n"; }
        return os << maxpq.pq_ << "\n";
    }
    ​
        static void test_initializer_list(const std::initializer_list<t>& li,
            const comparator<std::string>& compar = fwd_comparator<std::string>()) {
        std::cout << "\n//======================================================\ntesting max_pq_heap with alphabetical std::initializer_list...\n";
        max_pq_heap<std::string> pqheap(li, compar);
        while (!pqheap.empty()) {
            std::cout << pqheap.del_max() << " ";
        }
    }
    static void test_file(const std::string& filename,
        const comparator<std::string>& compar = fwd_comparator<std::string>()) {
        std::cout << "\n//======================================================\ntesting max_pq_heap with filename: '" << filename << "'...\n";
        ​
            max_pq_heap<std::string> pqheap(compar);
        std::string s;
        std::ifstream ifs(filename);
        if (!ifs.is_open()) {
            std::cerr << "could not open file: '" << filename << "'\n";
            throw new std::invalid_argument("invalid filename\n");
        }
        ​
            while (ifs >> s) {
                if (s != "-") {
                    pqheap.insert(s);
                }
                else {
                    std::cout << pqheap.del_max() << " ";
                }
            }
        std::cout << "\t(" << pqheap.size() << " left on the heap)\n\n";
        ifs.close();
    }
    ​
        ​
private:
    static const size_t min_capacity_;
    void exchange(size_t i, size_t j) {
        t temp = pq_[i];
        pq_[i] = pq_[j];
        pq_[j] = temp;
    }
    bool less(size_t i, size_t j) {
        return ::less(pq_[i], pq_[j], comp);
    }
        bool is_max_heap() const {
        size_t n = size();
        for (size_t i = 0; i < n; ++i) {
            if (pq_[i] == t()) { return false; }
        }
        for (size_t i = n + 1; i < size(); ++i) {
            if (pq_[i] != t()) { return false; }
        }
        if (pq_[0] != t()) { return false; }
        return is_max_heap_ordered(1);
    }
    ​
        bool is_max_heap_ordered(size_t k) {
        size_t n = size();
        if (k > n) { return true; }
        size_t left = 2 * k;
        size_t right = left + 1;
        ​
            if (left <= n && less(k, left)) { return false; }
        if (right <= n && less(k, right)) { return false; }
        ​
            return is_max_heap_ordered(left) && is_max_heap_ordered(right);
    }
    ​
private:
    array_<t> pq_;                // uses expandable array from array.h, not std::array<t>
    const comparator<t>& comp;
};
#endif /* max_pq_heap_h */