// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <string>

template<typename T>
class TPQueue {
    struct ITEM {
        T data;
        ITEM* next;
    };
    
 public:
     TPQueue(): head(nullptr), tail(nullptr) {}
    ~TPQueue() {
        while (head)
            pop();
    }
    void push(const T& data) {
        if (tail && head) {
            ITEM* temp = head;
            if (temp->data.prior < data.prior) {
                ITEM* curr = create(data);
                curr->next = temp;
                head = curr;
            } else {
                while (temp->next) {
                    if (temp->next->data.prior < data.prior) {
                        ITEM* next = temp->next;
                        temp->next = create(data);
                        temp->next->next = next;
                        break;
                    }
                    temp = temp->next;
                }
                if (temp == tail) {
                    tail->next = create(data);
                    tail = tail->next;
                }
            }
        } else {
            head = create(data);
            tail = head;
        }
    }
    T pop() {
        if (head) {
            ITEM* temp = head->next;
            T data = head->data;
            delete head;
            head = temp;
            return data;
        } else {
            T error;
            throw std::string(" Empty ! ");
            return error;
        }
    }
    
 private:
    ITEM* create(const T& data) {
        ITEM* item = new ITEM;
        item->data = data;
        item->next = nullptr;
        return item;
    }
    ITEM* head;
    ITEM* tail;
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
