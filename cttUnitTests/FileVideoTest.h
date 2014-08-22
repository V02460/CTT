#include <QtTest/QtTest>
#include <qoffscreensurface.h>

class FileVideoTest : public QObject
{
	Q_OBJECT

		private slots:
	void initTestCase();
	void test();

private:
	QOffscreenSurface surface;
	QSharedPointer<QOpenGLContext> testContext;
};