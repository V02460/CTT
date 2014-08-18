#ifndef _FILTERTEST_H
#define _FILTERTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include <QOffscreenSurface>
#include <QImage>
#include <QSharedPointer>
#include <QOpenGLContext>

namespace model {
namespace filter {

class FilterTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void dummyCase();

private:
    QSharedPointer<QOpenGLContext> testContext;
    QOffscreenSurface surface;
    QImage testImage;
};

}  // namespace filter
}  // namespace model

#endif  //_FILTERTEST_H