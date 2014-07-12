#include <QApplication>
#include <QtTest/QTest>

#include "TestResult.h"

#include "ModelTests.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

    TestResult r("");

    r << model::test(argc, argv);
      //<< view::test(argc, argv)
      //<< controller::test(argc, argv);

    r.print("");

	return 0;
}
