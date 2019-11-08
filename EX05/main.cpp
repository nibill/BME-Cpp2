/* Exercise 05 - ""
 *
 * @author Thomas Buchegger
 * @email thomas.buchegger@students.unibe.ch
 * @created  04.11.2019 17:24
 *
 * University of Bern / Bern University of Applied Sciences
 * Course 414078-HS2019-0: C++ Programming II
 */

#include <iostream>
#include <thread>
#include <sstream>
#include "dataqueue.h" // Your implementation!

using namespace std;
using namespace std::chrono_literals;

static DataQueue<size_t> q{5};
static mutex mu;
static bool finished{false};

void pcout(stringstream& msg)
{
    lock_guard<mutex> coutLock{mu};
    cout << msg.str() << endl;
}

void produce(size_t nbrItems)
{
    for(size_t count{0}; count < nbrItems; ++count)
    {
        std::this_thread::sleep_for(60ms); // Producing time
        q.add(count);
        stringstream ss;
        ss << "Producing --> item " <<   count;
        pcout(ss);
    }

    finished = true;
    stringstream ss; ss << " --- Producer done ----";
    pcout(ss);
}

void consume()
{
    while (!q.isEmpty() || !finished)
    {
        std::this_thread::sleep_for(90ms); // Consuming time
        stringstream ss;
        ss << "item " << q.get() << " --> comsumed";
        pcout(ss);
    }
}

int main()
{
    // Producer
    thread pThread{produce, 25};

    // Consumer
    thread cThread{consume};

    pThread.join();
    finished = true;
    cThread.join();

    cout << "Finished!"<< endl;
    return 0;
}
