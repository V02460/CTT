#include <CppUnitTest.h>
#include <functional>

#include <QObject>

#include "VideoMetadata.h"
#include "IllegalArgumentException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace model::video;
using namespace exception;

namespace ctt_unit_tests {
	TEST_CLASS(VideoMetadataTest) {
public:
	TEST_METHOD(noAdditionalMetadata) {
		QSize testSize(42, 100);

		VideoMetadata testMetadata(testSize, 23.9, 1337);

		testMetadata.getSize().height();
		testMetadata.getSize().width();
		testMetadata.getFPS();
		testMetadata.getLength();

		testMetadata.hasData("");
		testMetadata.hasData("test");

		Assert::ExpectException<IllegalArgumentException>([&]() {testMetadata.getData("test"); });
	}

	TEST_METHOD(noAdditionalMetadataInvalid) {
		QSize testSize(0, 100);
		Assert::ExpectException<IllegalArgumentException>([&]() {VideoMetadata testMetadata(testSize, 23.9, 1337); });

		QSize testSize2(100, 0);
		Assert::ExpectException<IllegalArgumentException>([&]() {VideoMetadata testMetadata(testSize2, 23.9, 1337); });

		QSize testSize3(100, 100);
		Assert::ExpectException<IllegalArgumentException>([&]() {VideoMetadata testMetadata(testSize3, 0, 1337); });

		Assert::ExpectException<IllegalArgumentException>([&]() {VideoMetadata testMetadata(testSize3, 23.9, 0); });
	}

	TEST_METHOD(withAdditionalMetadata) {
		QSize testSize(42, 100);
		QMap<QString, QString> testMap;

		testMap.insert("key1", "value1");
		testMap.insert("key2", "value2");

		VideoMetadata testMetadata(testSize, 23.9, 1337, testMap);

		testMetadata.getSize().height(), testSize.height();
		testMetadata.getSize().width(), testSize.width();
		testMetadata.getFPS();
		testMetadata.getLength();

		testMetadata.hasData("");
		testMetadata.hasData("test");

		testMetadata.hasData("key1");
		testMetadata.hasData("key2");

		Assert::ExpectException<IllegalArgumentException>([&]() {testMetadata.getData("test"); });

		QString value1("value1");
		QString value2("value2");

		testMetadata.getData("key1");
		testMetadata.getData("key2");
	}

	TEST_METHOD(withAdditionalMetadataInvalid) {
		QMap<QString, QString> testMap;

		QSize testSize(0, 100);
		Assert::ExpectException<IllegalArgumentException>([&]() {VideoMetadata testMetadata(testSize, 23.9, 1337, testMap); });

		QSize testSize2(100, 0);
		Assert::ExpectException<IllegalArgumentException>([&]() {VideoMetadata testMetadata(testSize2, 23.9, 1337, testMap); });

		QSize testSize3(100, 100);
		Assert::ExpectException<IllegalArgumentException>([&]() {VideoMetadata testMetadata(testSize3, 0, 1337, testMap); });

		Assert::ExpectException<IllegalArgumentException>([&]() {VideoMetadata testMetadata(testSize3, 23.9, 0, testMap); });
	}
	};
}