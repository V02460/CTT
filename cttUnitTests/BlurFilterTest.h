#ifndef _BLURFILTERTEST_H
#define _BLURFILTERTEST_H

#include <QtTest/QtTest>
#include <QObject>

class BlurFilterTest : public QObject {
    Q_OBJECT

public:
    BlurFilterTest();
    ~BlurFilterTest();

private slots:
    void init();
    void testRun();

private:
    QSharedPointer<QOpenGLContext> testContext;
};

#endif