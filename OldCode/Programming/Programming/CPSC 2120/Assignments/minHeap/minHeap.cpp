#include "minHeap.h"

using namespace std;


void minHeap::siftUp(int pos){

    int parent = (pos - 1) / 2; 

    int child = pos; 

    while(child != 0 && heap[parent] > heap[child]){

        int temp = heap[parent];
        heap[parent] = heap[child];
        heap[child] = temp;
        child = parent;
        parent = (parent - 1) / 2;
    }
}


void minHeap::siftDown(int pos){
    int parent = pos;
    int child1 = 2 * parent + 1;
    int child2 = 2 * parent + 2;
    int child_to_swap = -1;

    if(child1 < (int)heap.size() && heap[child1] < heap[parent]){
        child_to_swap = child1;
    }
    if(child2 < (int)heap.size() && heap[child2] < heap[parent]){
        if (child_to_swap == -1){ 
            child_to_swap = child2;
        }
        else{
            if (heap[child2] < heap[child1]) child_to_swap=child2; 
        }
    }
    if(child_to_swap == -1){
        return;
    }
    int temp = heap[parent];
    heap[parent] = heap[child_to_swap];
    heap[child_to_swap] = temp;
    siftDown(child_to_swap);
}

minHeap::minHeap(vector<int> data){
    heap.resize(0);
    for(int i=0;i<(int)data.size();i++){
        heap.push_back(data[i]);
    } 

    for(int i=heap.size()-1;i>=0;i--){
        siftDown(i);
    }
}

void minHeap::insert(int value){
    heap.push_back(value);
    int position = heap.size()-1;

    siftUp(position);
}

int minHeap::removeMin(){
    if(heap.size()== 0){
        return -1;
    }
    int temp = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap[heap.size() - 1] = temp;
    heap.pop_back();
    siftDown(0);
    return temp;
}