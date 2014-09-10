#include <CppUnitTest.h>
#include <functional>

#include <QApplication>
#include <QOpenGLContext>
#include <QDir>

#include "GreyscaleFilter.h"
#include "FilterParam.h"
#include "GlobalContext.h"
#include "YUVDataVideo.h"

#include "AccessToDummyException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ctt_unit_tests {

using ::model::filter::GreyscaleFilter;
using ::model::video::YUVDataVideo;
using ::model::filter::FilterParam;
using ::model::GlobalContext;
using ::model::video::YUVType;
using ::model::saveable::Memento;
using ::exception::AccessToDummyException;

TEST_CLASS(GreyscaleFilterTest) {
public:
    TEST_METHOD_INITIALIZE(initTestCase) {
        testContext = GlobalContext::get();

        QString string = QDir::currentPath();

        video.reset(new YUVDataVideo("Resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv",
            QSize(352, 288),
            24,
            YUVType::YUV420,
            testContext));
    }

    TEST_METHOD(testRun) {
        GreyscaleFilter greyscaleFilter(video);
        greyscaleFilter.getFrame(9);
    }

    TEST_METHOD(wrongParams) {
        GreyscaleFilter greyscaleFilter(video);

        Assert::ExpectException<IllegalArgumentException>([&]() {greyscaleFilter.setParam(FilterParam::sptr(new FilterParam("not right", "at all")));});
        Assert::ExpectException<IllegalArgumentException>([&]() {greyscaleFilter.setParam(FilterParam::sptr(new FilterParam("a bit off", 1.0)));});
        greyscaleFilter.getFrame(9);
    }

    TEST_METHOD(memento) {
        GreyscaleFilter testFilter(video);

        Memento memento = testFilter.getMemento();

        GreyscaleFilter::sptr dummyFilter = GreyscaleFilter::getDummy().dynamicCast<GreyscaleFilter>();
        Assert::ExpectException<AccessToDummyException>([&] {dummyFilter->getFrame(7);});
        Assert::ExpectException<AccessToDummyException>([&] {dummyFilter->getMemento(); });
        Assert::ExpectException<AccessToDummyException>([&] {dummyFilter->getUsesList(); });

        Assert::IsTrue(dummyFilter->isDummy());

        dummyFilter->restore(memento);
        dummyFilter->getFrame(6);
    }

private:
    QSharedPointer<QOpenGLContext> testContext;
    YUVDataVideo::sptr video;
};

}