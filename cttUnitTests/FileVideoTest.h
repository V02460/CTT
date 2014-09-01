#include <QtTest/QtTest>

class FileVideoTest : public QObject
{
	Q_OBJECT

private slots:
	void initTestCase();
	void test();

private:
	QSharedPointer<QOpenGLContext> testContext;
};