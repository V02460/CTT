#ifndef _TESTRESULT_T
#define _TESTRESULT_T

#include <QTextStream>
#include <QDebug>

class TestResult {
public:

    TestResult(QString name) : name(name), success(0), failure(0), isTest(false), children() {

    }

    TestResult(QString name, bool result)
            : name(name)
            , success(result ? 0 : 1)
            , failure(result ? 1 : 0)
            , isTest(true)
            , children() {

    }

    void add(TestResult result) {
        children.append(result);
        success += result.success;
        failure += result.failure;
    }

    void print(QString append) {
        //QTextStream out(stdout);
        
        if (isTest) {
            qDebug() << append + (failure ? "FAIL" : "OK") + " : " + name;
        } else {
            qDebug() << append + (failure ? "FAIL (" + QString::number(success) + "/"
                + QString::number(success + failure) + ")" : "OK") + " " + name;

            foreach(TestResult child, children) {
                child.print(append + "|   ");
            }
        }
    }

    inline TestResult &operator<<(TestResult &rhs) {
        add(rhs);
        return *this;
    }

private:
    QString name;

    unsigned int success;
    unsigned int failure;

    QList<TestResult> children;

    const bool isTest;
};

#endif