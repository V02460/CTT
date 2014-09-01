#ifndef _FILTEREDVIDEOTEST_H
#define _FILTEREDVIDEOTEST_H

#include <QtTest/QtTest>

class FilteredVideoTest : public QObject
{
	Q_OBJECT

private slots:
	void initTestCase();
	void dummyTest();
	void filterOperations();
	void saveRestore();

private:
	QSharedPointer<QOpenGLContext> testContext;
};

#endif  //_FILTEREDVIDEOTEST_H