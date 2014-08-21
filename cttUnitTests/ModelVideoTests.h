#include "TestResult.h"

#include "VideoMetadataTest.h"
#include "YUVDataVideoTest.h"

namespace model {
namespace video {

static TestResult test(int argc, char *argv[]) {
    TestResult r("video");

    VideoMetadataTest videoMetadataTest;
	YUVDataVideoTest yuvDataVideotest;
    r	<< TestResult("VideoMetadataTest", QTest::qExec(&videoMetadataTest, argc, argv))
		<< TestResult("YUVDataVideoTest", QTest::qExec(&yuvDataVideotest, argc, argv));

    return r;
}

}
}


