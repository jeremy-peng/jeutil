#include <iostream>
#include <thread>

#include "src/threadpool.h"

using namespace std;

void add_test(int a, int b)
{
    this_thread::sleep_for(chrono::seconds(2));
    cout << "id" << this_thread::get_id() << " " << a << " " << b << endl;
}

int main(int argc, char **argv)
{
    tpool::ThreadPool tp(5);

    std::function<void(int, int)> func = add_test;

    for (int i = 0; i < 100; i++)
    {
        tp.addTask(std::function<void(int, int)>(add_test), i, i + 2);
    }

    std::this_thread::sleep_for(chrono::seconds(10));
    cout << "about to exit" << endl;
    tp.stop();

    return 0;
}