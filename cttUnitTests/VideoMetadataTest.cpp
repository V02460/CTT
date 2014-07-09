#include "VideoMetadataTest.h"
#include "../ctt/VideoMetadata.h"
#include "../ctt/IllegalArgumentException.h"
#include "CustomTestingMacros.h"

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
