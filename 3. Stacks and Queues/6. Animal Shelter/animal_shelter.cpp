#include <iostream>
using namespace std;

/**
 * based on the textbook a better solution would be to have a timestamp and only two different lists
 * that way you can compare to see which is the oldest then dequeue from either list
 * this would make dequeue have less time compleximity compared to this implementation
 * i had a good try though!
 */
class Animal {
    public:
    string name; // name of animal
    bool dog; // using boolean since it can only be a dog or cat
    Animal* next; // plan for there to be one list put a node can have two different nexts, 
                    // one for the all the animals, and another for the specific kind of animal
    Animal* nextDog;
    Animal* nextCat;

    Animal() {
        name = "";
        dog = true; // defaults to dog
        next = NULL;
        nextDog = NULL;
        nextCat = NULL;
    }

    Animal(string n, bool d) {
        name = n;
        dog = d;
        next = NULL;
        nextDog = NULL;
        nextCat = NULL;
    }
};

class AnimalList {
    public:
    Animal* head;
    Animal* headDog;
    Animal* headCat;
    Animal* tail;
    Animal* tailDog;
    Animal* tailCat;

    AnimalList() {
        head = NULL;
        headDog = NULL;
        headCat = NULL;
        tail = NULL;
        tailDog = NULL;
        tailCat = NULL;
    }

    void enqueue(string n, bool d) {
        Animal* a = new Animal(n, d);
        if (head == NULL) {
            head = a;
            headDog = d ? a : NULL; // if dog start dog list
            headCat = !d ? a : NULL; // if cat start cat list
            tail = a;
            tailDog = d ? a : NULL;
            tailCat = !d ? a : NULL;
            return;
        }

        tail->next = a;
        tail = a;

        // update tailDog or tailCat based on new animal
        if (headDog == NULL && d) { 
            headDog = a;
            tailDog = a;
        } else if (headDog != NULL && d) {
            tailDog->nextDog = a;
            tailDog = a;
        }

        if (headCat == NULL && !d) {
            headCat = a;
            tailCat = a;
        } else if (headCat != NULL && !d) {
            tailCat->nextCat = a;
            tailCat = a;
        }
    }

    Animal* dequeueAny() {
        if (head == NULL) {
            return nullptr;
        }

        Animal* a = head;
        head = head->next;

        if (a->dog) {
            headDog = headDog->nextDog;
        } else {
            headCat = headCat->nextCat;
        }

        if (head == NULL) {
            tail = NULL;
            tailDog = NULL;
            tailCat = NULL;
        }

        return a;
    }

    Animal* dequeueDog() {
        if (headDog == NULL) {
            return nullptr;
        }

        Animal* d = headDog;
        headDog = headDog->nextDog;

        if (d == head) {
            head = head->next;
            if (head == NULL) {
                tail = NULL;
                tailDog = NULL;
                tailCat = NULL;
            }
        } else {
            // have to search back through list if head of dog or cat list isn't the head of the entire list of animals
            Animal* tmp = head;
            while (tmp->next != NULL && tmp->next != d) {
                tmp = tmp->next;
            }
            tmp->next = tmp->next->next;
        }



        return d;
    }

    Animal* dequeueCat() {
        if (headCat == NULL) {
            return nullptr;
        }

        Animal* c = headCat;
        headCat = headCat->nextCat;

        if (c == head) {
            head = head->next;
            if (head == NULL) {
                tail = NULL;
                tailDog = NULL;
                tailCat = NULL;
            }
        } else {
            Animal* tmp = head;
            while (tmp->next != NULL && tmp->next != c) {
                tmp = tmp->next;
            }
            tmp->next = tmp->next->next;
        }
        return c;
    }

    void print() {
        Animal* tmp = head;
        while (tmp != NULL) {
            cout << tmp->name << " (" << (tmp->dog ? "Dog), " : "Cat), ");
            tmp = tmp->next;
        }
        cout << endl;

        tmp = headDog;
        while (tmp != NULL) {
            cout << tmp->name << " (" << (tmp->dog ? "Dog), " : "Cat), ");
            tmp = tmp->nextDog;
        }
        cout << endl;

        tmp = headCat;
        while (tmp != NULL) {
            cout << tmp->name << " (" << (tmp->dog ? "Dog), " : "Cat), ");
            tmp = tmp->nextCat;
        }
        cout << endl;
    }
};

int main() {
    AnimalList l;
    l.enqueue("Rover", true);
    l.enqueue("Trouble", false);
    l.enqueue("Toast", false);
    l.enqueue("Peanut", true);
    l.print(); /**
                Rover (Dog), Trouble (Cat), Toast (Cat), Peanut (Dog)
                Rover (Dog), Peanut (Dog)
                Trouble (Cat), Toast(Cat)
                */

    cout << endl << l.dequeueAny()->name << endl; // Rover
    cout << l.dequeueCat()->name << endl; // Trouble
    cout << l.dequeueDog()->name << endl << endl; // Peanut
    l.print(); /**
                Toast (Cat),
                
                Toast(Cat),
                */
    cout << l.dequeueAny()->name << endl; // Toast
    return 0;
}