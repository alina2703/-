#include <iostream>


template <typename T>
class List {
private:
    struct Node {
            T val;
            Node* next;
            Node(): next(NULL) {}
            Node (const T& _val) : val(_val), next(nullptr) {}
    };
    Node* head;

public:
    List() : head(nullptr) {}
    List(Node* _head) : head(_head) {}
    ~List() {
        while (head != nullptr) {
            Node* nxt = head->next;
            delete(head);
            head = nxt;
        }
    }

    void pop_front() {
        Node* head1 = head->next;
        delete(head);
        head = head1;
    }

    void push_front(const T& el) {
        Node* new_node = new Node(el);
        new_node->next = head;
        head = new_node;
    }

    void reverse() {
        if (head == nullptr || head->next == nullptr)
            return;

        auto left = head, right = head->next->next;
        head = head->next;
        left->next = nullptr;
        head->next = left;

        while(right != nullptr) {
            left = head;
            head = right;
            right = right->next;
            head->next = left;
        }
    }

    T front() {
        return head->val;
    }

    bool empty() {
        return head == NULL;
    }

    Node* getHead() {
        return head;
    }

    void setHead(Node* h) {
        head = h;
    }

    Node* midPtr () {
        auto find_mid = head, find_end = head;
        while ((find_end = find_end->next) != nullptr &&
               (find_end = find_end->next) != nullptr)
            find_mid = find_mid->next;
        return find_mid;
    }
};

template<typename T>
void print(List<T>& list) {
    for (auto ptr = list.getHead(); ptr != nullptr; ptr = ptr->next)
        std::cout << ptr->val << ' ';
    std::cout << std::endl;
}

template <typename T>
void merge (List<T>& list1, List<T>& list2) {
    List<T> res;

    while (!list1.empty() || !list2.empty()) {
        if (list2.empty() || !list1.empty() && list1.front() < list2.front()) {
            res.push_front(list1.front());
            list1.pop_front();
        } else {
            res.push_front(list2.front());
            list2.pop_front();
        }
    }

    res.reverse();
    list1 = res;
    res.setHead(nullptr);
}

template<typename T>
void MergeSort(List<T>& l1) {
    auto ptr1 = l1.getHead(), ptr2 = l1.midPtr();

    if (ptr1->next == nullptr)
        return;

    auto ptr3 = ptr2->next;
    ptr2->next = nullptr;
    List<T> l2;
    l2.setHead(ptr3);

    MergeSort(l1);
    MergeSort(l2);
    merge(l1, l2);
}

int main() {
    size_t n;
    std::cin >> n;
    List <long long> list;
    for (size_t i = 0; i < n; ++i) {
        long long new_el;
        std::cin >> new_el;
        list.push_front(new_el);
    }

    MergeSort(list);
    print(list);
    return 0;
}
