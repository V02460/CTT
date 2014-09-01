#include <QObject>
#include <QtTest/QtTest>
#include <QOpenGLContext>


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
	void testMacroblockMetadata();
	//TODO jezfua need test material
//	void macroBlockMetadata(); 

private:
	QSharedPointer<QOpenGLContext> testContext;
};
