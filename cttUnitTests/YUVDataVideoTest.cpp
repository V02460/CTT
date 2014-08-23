#include "YUVDataVideoTest.h"

#include "CustomTestingMacros.h"
#include "VideoMetadata.h"
#include "IllegalArgumentException.h"
#include "FileNotFoundException.h"
#include "YUVDataVideo.h"
#include "Frame.h"

using namespace model::video;
using namespace exception;
using model::frame::Frame;


void YUVDataVideoTest::dummyTest()
{
	QVERIFY2(YUVDataVideo::getDummy()->isDummy(), "Dummy YUVDataVideo claimed not to be a dummy!");	
}

void YUVDataVideoTest::test444()
{
	//TODO relative Path zefgtiq
	YUVDataVideo testVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, testContext);
	QCOMPARE(testVideo.getFrameCount(), (unsigned int) 15);

	VideoMetadata metadata = testVideo.getMetadata();
	QCOMPARE(metadata.getLength(), (unsigned int) 15);
	QCOMPARE(metadata.getFPS(), 24.0f);
	QCOMPARE(metadata.getSize().width(), 720);
	QCOMPARE(metadata.getSize().height(), 576);

	Frame::sptr testframe = testVideo.getFrame(10);
	QCOMPARE(testframe->getSize().width(), 720);
	QCOMPARE(testframe->getSize().height(), 576);

	QVERIFY(!testframe->getMetadata().hasMbMotionvectors());
	QVERIFY(!testframe->getMetadata().hasMbType());

	QCOMPARE(testframe->getMetadata().getSize().width(), 720);
	QCOMPARE(testframe->getMetadata().getSize().height(), 576);

	QEXPECT_EXCEPTION(testVideo.getFrame(testVideo.getFrameCount()), IllegalArgumentException);
}

void YUVDataVideoTest::init()
{
	surface.create();
	testContext.reset(new QOpenGLContext());
	testContext->create();
	testContext->makeCurrent(&surface);
}

void YUVDataVideoTest::test422()
{
	//TODO relative Path zefgtiq
	YUVDataVideo testVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV422, testContext);
	QCOMPARE(testVideo.getFrameCount(), (unsigned int)15);

	VideoMetadata metadata = testVideo.getMetadata();
	QCOMPARE(metadata.getLength(), (unsigned int)15);
	QCOMPARE(metadata.getFPS(), 24.0f);
	QCOMPARE(metadata.getSize().width(), 720);
	QCOMPARE(metadata.getSize().height(), 576);

	Frame::sptr testframe = testVideo.getFrame(10);
	QCOMPARE(testframe->getSize().width(), 720);
	QCOMPARE(testframe->getSize().height(), 576);

	QVERIFY(!testframe->getMetadata().hasMbMotionvectors());
	QVERIFY(!testframe->getMetadata().hasMbType());

	QCOMPARE(testframe->getMetadata().getSize().width(), 720);
	QCOMPARE(testframe->getMetadata().getSize().height(), 576);

	QEXPECT_EXCEPTION(testVideo.getFrame(testVideo.getFrameCount()), IllegalArgumentException);
}

void YUVDataVideoTest::test420()
{
	//TODO relative Path zefgtiq
	YUVDataVideo testVideo("resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv", QSize(352, 288), 24, model::video::YUVType::YUV420, testContext);
	QCOMPARE(testVideo.getFrameCount(), (unsigned int)260);

	VideoMetadata metadata = testVideo.getMetadata();
	QCOMPARE(metadata.getLength(), (unsigned int)260);
	QCOMPARE(metadata.getFPS(), 24.0f);
	QCOMPARE(metadata.getSize().width(), 352);
	QCOMPARE(metadata.getSize().height(), 288);

	Frame::sptr testframe = testVideo.getFrame(10);
	QCOMPARE(testframe->getSize().width(), 352);
	QCOMPARE(testframe->getSize().height(), 288);

	QVERIFY(!testframe->getMetadata().hasMbMotionvectors());
	QVERIFY(!testframe->getMetadata().hasMbType());

	QCOMPARE(testframe->getMetadata().getSize().width(), 352);
	QCOMPARE(testframe->getMetadata().getSize().height(), 288);

	QEXPECT_EXCEPTION(testVideo.getFrame(testVideo.getFrameCount()), IllegalArgumentException);
}

void YUVDataVideoTest::invalidConstruction()
{
	
	QEXPECT_EXCEPTION(YUVDataVideo atest("thisfiledoesntexist", QSize(352, 288), 24, model::video::YUVType::YUV420, testContext), FileNotFoundException);
	QEXPECT_EXCEPTION(YUVDataVideo testVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(719, 576), 24, model::video::YUVType::YUV422, testContext), IllegalArgumentException);
	QEXPECT_EXCEPTION(YUVDataVideo testVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(719, 576), 24, model::video::YUVType::YUV420, testContext), IllegalArgumentException);
	QEXPECT_EXCEPTION(YUVDataVideo testVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(720, 575), 24, model::video::YUVType::YUV420, testContext), IllegalArgumentException);
	QEXPECT_EXCEPTION(YUVDataVideo testVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(920, 886), 24, model::video::YUVType::YUV444, testContext), IllegalArgumentException);
	QEXPECT_EXCEPTION(YUVDataVideo testVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", "thismetadatafiledoesntexist",QSize(720, 576), 24, model::video::YUVType::YUV422, testContext), FileNotFoundException);

	//TODO kugtexxxiiia metadatafiles of wrong sizes, resolutions that cant be divided into 16*16 pixel blocks
}
