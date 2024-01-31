#include <iostream>

#include "List.h"

using std::cout;
using std::endl;


namespace ds {
    Node::Node(int v) {
        val = v;
    }

    DoublyLinkedList::DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    DoublyLinkedList::DoublyLinkedList(int arr[], int size) {
        if (size == 0) {
            head = nullptr;
            tail = nullptr;
            length = 0;
        }
        else if (size == 1) {
            Node* node1 = new Node(arr[0]);
            head = node1;
            tail = node1;
            length = 1;
        }
        else {
            Node* node1 = new Node(arr[0]);
            head = node1;
            tail = node1;

            for (int i = 1; i < size; i++) {
                Node *node2 = new Node(arr[i]);
                node1->next = node2;
                tail = node2;
                node2->prev = node1;
                node1 = node1->next;
                length = i + 1;
            }
        }
    }

    void DoublyLinkedList::Insert(int idx, int v) {
        if (idx < 0 || idx > length) {
            return;
        }
        else {
            Node* insertNode = new Node(v);

            if (length == 0) {
                head = insertNode;
                tail = insertNode;
                length = 1;
            }
            else if (idx == 0) {
                head->prev = insertNode;
                insertNode->next = head;
                head = insertNode;
                length++;
            }
            else if (idx == length) {
            tail->next = insertNode;
            insertNode->prev = tail;
            tail = insertNode;
            length++;
            }
            else {
            Node* findIdxNode = new Node(0);
            Node* tempNode = new Node(0);
            findIdxNode = head;
            int i = 0;

            while (i != idx - 1) {
                findIdxNode = findIdxNode->next;
                i++;
            }
            tempNode = findIdxNode;
            findIdxNode = findIdxNode->next;
            insertNode->next = findIdxNode;
            insertNode->prev = tempNode;
            tempNode->next = insertNode;
            findIdxNode->prev = insertNode;
            length++;

            }

        }
    }

    void DoublyLinkedList::Remove(int idx) {
        if (idx < 0 || idx > length - 1) {
            return;
        }
        else {
            Node* removeNode = new Node(0);
            removeNode = head;
            int i = 0;

            while (i != idx) {
                removeNode = removeNode->next;
                i++;
            }
            if (length == 1) {
                head = nullptr;
                tail = nullptr;
                length = 0;
            }
            else if (removeNode == head) {
                head = removeNode->next;
                removeNode->next->prev = nullptr;
                length--;
            }
            else if (removeNode == tail) {
                tail = removeNode->prev;
                removeNode->prev->next = nullptr;
                length--;
            }
            else {
                removeNode->prev->next = removeNode->next;
                removeNode->next->prev = removeNode->prev;
                length--;
            }
        }

    }

    int DoublyLinkedList::Get(int idx) {
        if (idx < 0 || idx > length - 1) {
            return -1;
        }
        else {
            Node* getNode = new Node(0);
            getNode = head;
            for (int i = 0; i < idx; i++) {
                getNode = getNode->next;
            }
            return getNode->val;
        }
    }

    int DoublyLinkedList::Search(int v) {
        Node* searchNode = new Node(0);
        searchNode = head;

        for (int i = 0; i < length; i++) {
            if (v == searchNode->val) {
                return i;
            }
            else {
                searchNode = searchNode->next;
            }
        }
        return -1;
    }

    void DoublyLinkedList::ReverseList() {
        int num = 0;
        for (int i = 0; i < length; i++) {
            num = Get(length - 1);
            Remove(length - 1);
            Insert(i, num);
        }
    }

    void DoublyLinkedList::PrintList() {
        for (int i = 0; i < length; i++) {
            cout << Get(i) << " ";
        }
        cout << '\n';
    }

    void DoublyLinkedList::MergeList(DoublyLinkedList* list) {
        if (list->head != nullptr) {
            list->head->prev = tail;
            tail->next = list->head;
            tail = list->tail;

            length = length + list->length;
        }
        else {
            return;
        }
    }
}