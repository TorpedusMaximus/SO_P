#include <iostream>
#include <cstdlib>
#include <cassert>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <algorithm>

using namespace std;
// compilation command: g++ -g -Wall main.cpp -o exe -pthread
// execute: ./exe [number of desired threads]

int numThreads;

void bubbleSort(int threadNumber) {
    int size = 100;
    vector<int> table(size);

    for (int &i: table) {
        i = rand() % 500;
    }

    //print table
    cout<<"Thread: "<<threadNumber<<" "<<endl;
    for (auto i: table) {
        cout << i << " ";
    }
    cout<<"Thread: "<<threadNumber<< " Started sorting: " << endl;

    //bubble sort
    for (int i = 0; i < size; i++) {
        if (i % (10) == 0) {
            cout <<"Thread: "<<threadNumber<<" "<< i <<"% passed" << endl;
        }
        for (int j = 0; j < size - 1; j++) {
            if (table[j] > table[j + 1]) {
                int temp = table[j];
                table[j] = table[j + 1];
                table[j + 1] = temp;
            }
        }
    }

    cout <<"Thread: "<<threadNumber<< " Finished sorting: " << endl;
    //print table
    for (auto i: table) {
        cout << i << " ";
    }
}

void selectionSort(int threadNumber) {
    int size = 100;
    vector<int> table(size);

    for (int &i: table) {
        i = rand() % 500;
    }

    //print table
    cout<<"Thread: "<<threadNumber<<" "<<endl;
    for (auto i: table) {
        cout << i << " ";
    }
    cout<<"Thread: "<<threadNumber<< " Started sorting: " << endl;

    for (int i = 0; i < table.size(); i++) {

        if (i % (10) == 0) {
            cout <<"Thread: "<<threadNumber <<" "<< i << " % passed" << endl;
        }

        int min = i;
        for (int j = i + 1; j < table.size(); j++) {
            if (table[j] < table[min]) {
                min = j;
            }
        }
        swap(table[i], table[min]);
    }

    cout <<"Thread: "<<threadNumber<< " Finished sorting: " << endl;
    //print table
    for (auto i: table) {
        cout << i << " ";
    }
}


void countToMilion(int threadNumber) {
    cout <<"Thread: "<<threadNumber<< " Counting to milion" << endl;
    for (int i = 0; i <= 1000000; i++) {
        if (i % 100000 == 0) {
            cout <<"Thread: "<<threadNumber<< " "<<i<< " passed" << endl;
        }
    }
    cout <<"Thread: "<<threadNumber<< " Counting finished" << endl;
}

void drawSlope(int threadNumber) {
    for (int i = 0; i < 10; i++) {
        cout <<"Thread: "<<threadNumber<<" ";
        for (int j = 0; j < i; j++) {
            cout << "*";
        }
        cout << endl;
    }

    cout <<"Thread: "<<threadNumber<< " Drawing finished" << endl;
}

void *perform_work(void *arguments) {
    int action = rand() % 4;
    int thread = *(int *) arguments;
    switch (action) {
        case 0:
            bubbleSort(thread);
            break;
        case 1:
            selectionSort(thread);
            break;
        case 2:
            countToMilion(thread);
            break;
        case 3:
            drawSlope(thread);
            break;
    }
    return nullptr;
}

int main(int argc, char *argv[]) {
    int NUM_THREADS = atoi(argv[1]);
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int i;
    int result_code;

    //create all threads one by one
    for (i = 0; i < NUM_THREADS; i++) {
        cout<<"IN MAIN: Creating thread " << i << "." << endl;
        thread_args[i] = i;
        result_code = pthread_create(&threads[i], NULL, perform_work, &thread_args[i]);
        assert(!result_code);
    }

    cout<<"IN MAIN: All threads are created."<<endl;

    //wait for each thread to complete
    for (i = 0; i < NUM_THREADS; i++) {
        result_code = pthread_join(threads[i], NULL);
        assert(!result_code);
        cout<<"IN MAIN: Thread " << i << " has ended."<<endl;
    }

    cout<<"MAIN program has ended."<<endl;
    return 0;
}