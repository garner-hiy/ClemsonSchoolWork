#include "IntegerArrayQueue.h"

bool IntegerArrayQueue::enqueue(int value) {
    if((back + 2) % size == front){
        return false;
    }
    else{
        back = (back + 1) % size;
        array[back] = value;
        return true;
    }
}

int IntegerArrayQueue::dequeue() {
    int temp;
    if(front - 1 == back){
        return 0;
    }
    else{
        temp = front;
        front = (front + 1) % size;
        return array[temp];
    }
}