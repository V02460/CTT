#include "TestResult.h"

#include "VideoMetadataTest.h"
#include "YUVDataVideoTest.h"
#include "FilteredVideoTest.h"
#include "VideoTest.h"
#include "FileVideoTest.h"

namespace model {
namespace video {

static TestResult test(int argc, char *argv[]) {
    TestResult r("video");

    VideoMetadataTest videoMetadataTest;
	YUVDataVideoTest yuvDataVideotest;
	FilteredVideoTest filteredVideoTest;
	FileVideoTest fileVideoTest;
	VideoTest videoTest;
	r << TestResult("VideoMetadataTest", QTest::qExec(&videoMetadataTest, argc, argv))
		<< TestResult("YUVDataVideoTest", QTest::qExec(&yuvDataVideotest, argc, argv))
		<< TestResult("FilteredVideoTest", QTest::qExec(&filteredVideoTest, argc, argv))
		<< TestResult("VideoTest", QTest::qExec(&videoTest, argc, argv))
		<< TestResult("FileVideoTest", QTest::qExec(&fileVideoTest, argc, argv));

    return r;
}

}
}


