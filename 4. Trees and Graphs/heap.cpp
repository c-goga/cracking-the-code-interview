#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// my bad attempt to implement it using nodes lol

// class MinHeap {
//     private:
//     int min;
//     class TreeNode {
//         public:
//         int d;
//         TreeNode* left;
//         TreeNode* right;
//         TreeNode* parent;

//         TreeNode(int d) {
//             this->d = d;
//             left = nullptr;
//             right = nullptr;
//         }

//         void add(int d) {
//             TreeNode* t = new TreeNode(d);
//             queue<TreeNode *> q;
//             q.push(left);
//             q.push(right);

//             while (!q.size() != 0) {
//                 if (q.front() == nullptr) {
//                     q.front() = t;
//                     return;
//                 } else {
//                     if (q.front()->left != nullptr) {
//                         q.push(q.front()->left);
//                     }

//                     if (q.front()->right != nullptr) {
//                         q.push(q.front()->right);
//                     }

//                     q.pop();
//                 }
//             }
//         }
//     };

//     TreeNode* root;
//     public:
//     MinHeap(int d) {
//         root = new TreeNode(d);
//         min = d;
//     }

//     void insert(int d) {
//         TreeNode* t = new TreeNode(d);
//     }
// };

// geeksforgeeks copied by hand along with some notes
// did this to better learn the inner workings

template <typename T> // used so that any data type can be used within the heap
class MinHeap {
    private:
    vector<T> array;
    int size;
    int capacity;

    public:
    MinHeap(int capacity) {
        this->size = 0;
        this->capacity = capacity;
        this->array.resize(capacity); // good to know that vector has its own resize method
    }

    // restores the heap order at index i
    void heapify(int i) {
        int smallest = i; // initializes smallest as root
        int left = 2 * i + 1; // left child index
        int right = 2 * i + 2; // right child index
        // children of tree node are always two times the index away from the parent if 
        // it is represented by an array, good to know

        // if left child smaller than root
        if (left < size && array[left] < array[smallest]) {
            smallest = left; 
        }

        // if right child smaller than the smallest so far (root or left)
        if (right < size && array[right] < array[right]) {
            smallest = right;
        }

        // smallest is not root (left or right)
        if (smallest != i) {
            swap(array[i], array[smallest]); // swap root with left or right
            heapify(smallest); // do it all over again with child that was swapped until bottom is reached
        }
    }

    // create min heap from given array
    void buildHeap(const vector<T>& arr) {
        capacity = arr.size();
        size = capacity;
        array = arr;

        // heapify the (n-1)/2 nodes
        for (int i = (size - 1) / 2; i >= 0; i--) {
            heapify(i);
        }
    }

    // insert new node into min heap
    void insertNode(T value) {
        if (size == capacity) {
            capacity *= 2;
            array.resize(capacity);
        }

        size++;
        int i = size - 1;
        array[i] = value;

        // keep swaping with parent until parent is smaller than new node
        while (i != 0 && array[(i - 1) / 2] > array[i]) {
            swap(array[i], array[((i - 1) / 2)]);
            i = (i - 1) / 2;
        }
    }

    // get topmost value from min heap
    T peek() {
        if (size <= 0) return -1; // indicates heap empty

        return array[0];
    }

    // remove and return minimum value from heap
    T extractMin() {
        if (size <= 0) return -1; // heap empty
        if (size == 1) {
            size--;
            return array[0];
        }

        // store min value and remove it
        T root = array[0];
        array[0] = array[size - 1];
        size--;
        // heapify the root node after deletion
        heapfiy(0);
        return root;
    }

    // delete a specific node from heap
    void DeleteNode(T key) {
        // find index of key
        int index = -1;
        for (int i = 0; i < size; i++) {
            if (array[i] == key) {
                index = i;
                break;
            }
        }

        // if key not found, return
        if (index == -1) {
            cout << "Key not found" << endl;
            return;
        }

        if (index == size - 1) {
            size--;
            return;
        }

        // move last element to the index of the key to be deleted
        array[index] = array[size - 1];
        size--;

        // heapify down to heapify the rest of the min heap
        heapify(index);
    }

    // print values of min heap
    void printHeap() const {
        for (int i = 0; i < size; i++)
            cout << array[i] << " ";
        cout << endl;
    }
};