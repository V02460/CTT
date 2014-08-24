#include <QObject>
#include <QtTest/QtTest>
#include <qoffscreensurface.h>
#include <qopenglcontext.h>


class YUVDataVideoTest : public QObject {
	Q_OBJECT

	private slots:
	void init();
	void dummyTest();
 	void test444();
 	void test422();
 	void test420();
 	void invalidConstruction();
	void saveRestore();

	//TODO jezfua need test material
//	void macroBlockMetadata(); 

private:
	QOffscreenSurface surface;
	QSharedPointer<QOpenGLContext> testContext;
};
