#include "TestResult.h"

#include "VideoMetadataTest.h"

namespace model {
namespace video {

static TestResult test(int argc, char *argv[]) {
    TestResult r("video");

    VideoMetadataTest videoMetadataTest;
    r << TestResult("VideoMetadataTest", QTest::qExec(&videoMetadataTest, argc, argv));

    return r;
}

}
}


