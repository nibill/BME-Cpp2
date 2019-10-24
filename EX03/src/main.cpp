/* Exercise 03 - ""
 *
 * @author Thomas Buchegger
 * @email thomas.buchegger@students.unibe.ch
 * @created  15.10.2019 11:51
 *
 * University of Bern / Bern University of Applied Sciences
 * Course 394661-FS2019-0: C++ Programming I
 */

#include <QApplication>
#include "widget.h"

int main ( int argc , char * argv [])
{
    QApplication a(argc , argv );
    Widget w;
    w.show();
    return a.exec ();

}
