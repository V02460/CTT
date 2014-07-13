#include "VideoMetadataTest.h"

#include "CustomTestingMacros.h"
#include "VideoMetadata.h"
#include "IllegalArgumentException.h"

using namespace model::video;
using namespace exception;

void VideoMetadataTest::noAdditionalMetadata()
{
	QSize testSize(42, 100);

	VideoMetadata testMetadata(testSize, 23.9, 1337);

	QCOMPARE(testMetadata.getSize().height(), testSize.height());
	QCOMPARE(testMetadata.getSize().width(), testSize.width());
	QCOMPARE(23.9, testMetadata.getFPS());
	QCOMPARE((unsigned int)1337, testMetadata.getLength());

	QVERIFY2(!testMetadata.hasData(""), "The tested object has metadata it isn't supposed to have!");
	QVERIFY2(!testMetadata.hasData("test"), "The tested object has metadata it isn't supposed to have!");

	QEXPECT_EXCEPTION(testMetadata.getData("test"), IllegalArgumentException);
}

void VideoMetadataTest::noAdditionalMetadataInvalid()
{
	QSize testSize(0, 100);
	QEXPECT_EXCEPTION(VideoMetadata testMetadata(testSize, 23.9, 1337), IllegalArgumentException);

	QSize testSize2(100, 0);
	QEXPECT_EXCEPTION(VideoMetadata testMetadata(testSize2, 23.9, 1337), IllegalArgumentException);

	QSize testSize3(100, 100);
	QEXPECT_EXCEPTION(VideoMetadata testMetadata(testSize3, 0, 1337), IllegalArgumentException);

	QEXPECT_EXCEPTION(VideoMetadata testMetadata(testSize3, 23.9, 0), IllegalArgumentException);

}

void VideoMetadataTest::withAdditionalMetadata()
{
	QSize testSize(42, 100);
	QMap<QString, QString> testMap;

	testMap.insert("key1", "value1");
	testMap.insert("key2", "value2");

	VideoMetadata testMetadata(testSize, 23.9, 1337, testMap);

	QCOMPARE(testMetadata.getSize().height(), testSize.height());
	QCOMPARE(testMetadata.getSize().width(), testSize.width());
	QCOMPARE(23.9, testMetadata.getFPS());
	QCOMPARE((unsigned int)1337, testMetadata.getLength());

	QVERIFY2(!testMetadata.hasData(""), "The tested object has metadata it isn't supposed to have!");
	QVERIFY2(!testMetadata.hasData("test"), "The tested object has metadata it isn't supposed to have!");

	QVERIFY2(testMetadata.hasData("key1"), "The tested object doesn't have metadata it is supposed to have!");
	QVERIFY2(testMetadata.hasData("key2"), "The tested object doesn't have metadata it is supposed to have!");

	QEXPECT_EXCEPTION(testMetadata.getData("test"), IllegalArgumentException);

	QString value1("value1");
	QString value2("value2");

	QCOMPARE(testMetadata.getData("key1"), value1);
	QCOMPARE(testMetadata.getData("key2"), value2);
}

void VideoMetadataTest::withAdditionalMetadataInvalid()
{
	QMap<QString, QString> testMap;

	
	QSize testSize(0, 100);

	QEXPECT_EXCEPTION(VideoMetadata testMetadata(testSize, 23.9, 1337, testMap), IllegalArgumentException);

	QSize testSize2(100, 0);
	QEXPECT_EXCEPTION(VideoMetadata testMetadata(testSize2, 23.9, 1337, testMap), IllegalArgumentException);

	QSize testSize3(100, 100);
	QEXPECT_EXCEPTION(VideoMetadata testMetadata(testSize3, 0, 1337, testMap), IllegalArgumentException);

	QEXPECT_EXCEPTION(VideoMetadata testMetadata(testSize3, 23.9, 0, testMap), IllegalArgumentException);


}
