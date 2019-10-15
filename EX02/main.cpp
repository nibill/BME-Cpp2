/* Exercise 02 - ""
 *
 * @author Thomas Buchegger
 * @email thomas.buchegger@students.unibe.ch
 * @created  08.10.2019 09:08
 *
 * University of Bern / Bern University of Applied Sciences
 * Course 394661-FS2019-0: C++ Programming II
 */

#include <iostream>
#include "ex2.h"
#include "billionaire.h"

using namespace std;

int main()
{
    ex2 ex2{};
    Billionaire bil{};
    cout << "ex 2a:" << endl;
    cout << "--------------------------------------" << endl;
    ex2.ex2a();
    cout << endl;

    cout << "ex 2b:" << endl;
    cout << "--------------------------------------" << endl;
    ex2.ex2b();
    cout << endl;

    cout << "ex 3:" << endl;
    cout << "--------------------------------------" << endl;
    bil.ex3();
    cout << endl;
    return 0;
}
