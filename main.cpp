#include <QCoreApplication>
#include <iostream>
#include <iomanip>
#include <QTimer>
#include "SemiCL6Func.h"

//using std::cout, std::endl, std::setprecision;
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    if (!SemiCL6FuncInitialize()) // DLL Initialize
    {
        cout << "DLL initialization failed";
        return app.exec();
    }

    mwArray matrix_f1_x(1, 1120, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f1_ph1(1, 1120, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f1_ph2(1, 1120, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f1_ph3(1, 1120, mxDOUBLE_CLASS, mxREAL);
    int nargout=4;
    SemiCL6Func(nargout, matrix_f1_x, matrix_f1_ph1, matrix_f1_ph2, matrix_f1_ph3);
    //cout << "matrix_f1_x:" << endl;
    //cout <<setiosflags(ios::fixed) << std::setprecision(10) << matrix_f1_x << endl;
    //cout << "matrix_f1_ph1" << endl;
    //cout << setiosflags(ios::fixed) << setprecision(8) << matrix_f1_ph1 << endl;

    typedef QList<double> DataList;
    DataList f1_x_list;
    for(int i(1); i<=1120; i++){
        f1_x_list << matrix_f1_ph1.Get(1, i);
    }
    qDebug() <<  f1_x_list;



    cout << "done." << endl;
    //SemiCL6FuncTerminate();
    //Add this, otherwise the Qt console program will not end automatically
    QTimer t;
    t.connect(&t, SIGNAL(timeout()), &app, SLOT(quit()));
    t.start(5);  // 5millisecond
    return app.exec();
}
