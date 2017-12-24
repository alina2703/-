#include <iostream>

template <typename T>
class List {
private:
    struct Node {
        T val;
        Node* next;
        Node() : next (NULL) {}
        Node (const T& _val) : val (_val), next (NULL) {}
    };
    Node* head;
    Node* prev;
public:
    List() : head(NULL), prev(NULL) {}
    ~List() {}
    class Iter{
    private:
        Node* node;
    public:
        Iter (Node* _node) : node (_node) {}
        T& operator *() {
            return node->val;
        }
        void operator ++ () {
            node = node->next;
        }
        bool operator != (const Iter& other) {
            return node != other.node;
        }
    };
    Iter begin() {
        return Iter(head);
    }
    Iter end() {
        return Iter(NULL);
    }
    size_t size() {
        size_t len = 0;
        for (auto it = begin(); it != end(); ++it) {
            len++;
        }
        return len;
    }
    void push(const T& el) {
        Node* new_node = new Node (el);
        if (head == NULL)
            head = new_node;
        else
            prev->next = new_node;
        prev = new_node;
    }
};

List<long long>::Iter midIter (List<long long>::Iter first, size_t len) {
    for (size_t i = 0; i != len / 2; ++i) {
        ++first;
    }
    return first;
}
void merge (List<long long>::Iter& it1, List<long long>::Iter& it2, List<long long>::Iter& last) {
    auto mid = it2, first = it1;
    List <long long> res;
    while (it1 != mid && it2 != last) {
        if (*it1 > *it2) {
            res.push(*it2);
            ++it2;
        } else {
            res.push(*it1);
            ++it1;
        }
    }
    while (it1 != mid) {
        res.push(*it1);
        ++it1;
    }
    while (it2 != last) {
        res.push(*it2);
        ++it2;
    }
    for (auto it = first, itRes = res.begin(); it != last; ++it, ++itRes) {
        *it = *itRes;
    }
}
void MergeSort (List<long long>::Iter first, List<long long>::Iter last, size_t len) {
    if (len == 1)
        return;
    auto mid = midIter(first, len);
    MergeSort(first, mid, len / 2);
    MergeSort(mid, last, len - len / 2);
    merge (first, mid, last);
}

int main() {
    size_t n;
    std::cin >> n;
    List <long long> list;
    for (size_t i = 0; i < n; ++i) {
        long long new_el;
        std::cin >> new_el;
        list.push(new_el);
    }
    MergeSort(list.begin(), list.end(), n);
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << ' ';
    }
    return 0;
}