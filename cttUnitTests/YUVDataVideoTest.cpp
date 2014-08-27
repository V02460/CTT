#include "YUVDataVideoTest.h"

#include "CustomTestingMacros.h"
#include "VideoMetadata.h"
#include "IllegalArgumentException.h"
#include "FileNotFoundException.h"
#include "YUVDataVideo.h"
#include "Frame.h"
#include "..\CTT\GlobalContext.h"
#include "..\ctt\MacroblockType.h"
#include "..\CTT\OpenGLException.h"

using namespace model::video;
using namespace exception;
using model::frame::Frame;
using model::frame::MacroblockType;


void YUVDataVideoTest::dummyTest()
{
	QVERIFY2(YUVDataVideo::getDummy()->isDummy(), "Dummy YUVDataVideo claimed not to be a dummy!");	
}

void YUVDataVideoTest::test444()
{
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

	QVERIFY(!testframe->getMetadata().hasMbMotionvectors());
	QVERIFY(!testframe->getMetadata().hasMbType());

	QEXPECT_EXCEPTION(testVideo.getFrame(testVideo.getFrameCount()), IllegalArgumentException);
}

void YUVDataVideoTest::invalidConstruction()
{
	
	QEXPECT_EXCEPTION(YUVDataVideo atest("thisfiledoesntexist", QSize(352, 288), 24, model::video::YUVType::YUV420, testContext), FileNotFoundException);
	QEXPECT_EXCEPTION(YUVDataVideo btestVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(719, 576), 24, model::video::YUVType::YUV422, testContext), IllegalArgumentException);
	QEXPECT_EXCEPTION(YUVDataVideo ctestVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(719, 576), 24, model::video::YUVType::YUV420, testContext), IllegalArgumentException);
	QEXPECT_EXCEPTION(YUVDataVideo dtestVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(720, 575), 24, model::video::YUVType::YUV420, testContext), IllegalArgumentException);
	QEXPECT_EXCEPTION(YUVDataVideo etestVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(920, 886), 24, model::video::YUVType::YUV444, testContext), IllegalArgumentException);
	QEXPECT_EXCEPTION(YUVDataVideo ftestVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", "thismetadatafiledoesntexist",QSize(720, 576), 24, model::video::YUVType::YUV422, testContext), FileNotFoundException);

	QEXPECT_EXCEPTION(YUVDataVideo testVideo2("resources/Videos/YUV420/raftingNEW_352x288_113.yuv", "resources/Videos/YUV420/ModeGrid_RD1_Rafting.dat", QSize(352, 288), 24, model::video::YUVType::YUV420, testContext), IllegalArgumentException);
	//TODO kugtexxxiiia resolutions that cant be divided into 16*16 pixel blocks
}

void YUVDataVideoTest::saveRestore()
{
	YUVDataVideo testVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV422, testContext);
	Memento memento = testVideo.getMemento();
	
	YUVDataVideo::sptr dummy = YUVDataVideo::getDummy().dynamicCast<YUVDataVideo>();

	dummy->restore(memento);
	QCOMPARE(dummy->getFrameCount(), (unsigned int)15);

	VideoMetadata metadata = dummy->getMetadata();
	QCOMPARE(metadata.getLength(), (unsigned int)15);
	QCOMPARE(metadata.getFPS(), 24.0f);
	QCOMPARE(metadata.getSize().width(), 720);
	QCOMPARE(metadata.getSize().height(), 576);

	QVERIFY(dummy->getContext() == model::GlobalContext::get());

	dummy->getFrame(10);
	dummy->getFrame(14);
	dummy->getFrame(0);

	YUVDataVideo testVideo2("resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv", QSize(352, 288), 24, model::video::YUVType::YUV420, testContext);
	testVideo2.restore(memento);

	VideoMetadata metadata2 = testVideo2.getMetadata();
	QCOMPARE(metadata2.getLength(), (unsigned int)15);
	QCOMPARE(metadata2.getFPS(), 24.0f);
	QCOMPARE(metadata2.getSize().width(), 720);
	QCOMPARE(metadata2.getSize().height(), 576);

	QVERIFY(testVideo2.getContext() == model::GlobalContext::get());

	testVideo2.getFrame(10);
	testVideo2.getFrame(14);
	testVideo2.getFrame(0);

	YUVDataVideo testVideo3("resources/Videos/YUV420/raftingNEW_352x288_113.yuv", "resources/Videos/YUV420/ModeGrid_raf_512my.dat", QSize(352, 288), 24, model::video::YUVType::YUV420, testContext);

	memento = testVideo3.getMemento();

	testVideo.restore(memento);
	Frame::sptr testFrame = testVideo.getFrame(0);
	QVERIFY(testFrame->getMetadata().hasMbType());
	QVERIFY(testFrame->getMetadata().getMbType()[0][0] == MacroblockType::INTRA_4X4);
	QVERIFY(testFrame->getMetadata().getMbType()[0][9] == MacroblockType::INTRA_16X16);
	QVERIFY(testFrame->getMetadata().getMbType()[0][21] == MacroblockType::INTRA_4X4);
	QVERIFY(testFrame->getMetadata().getMbType()[1][0] == MacroblockType::INTRA_4X4);

	testFrame.reset();
	testFrame = testVideo.getFrame(testVideo.getFrameCount() - 1);
	QVERIFY(testFrame->getMetadata().getMbType()[17][21] == MacroblockType::INTER_SKIP);
}

void YUVDataVideoTest::testMacroblockMetadata()
{

	YUVDataVideo testVideo("resources/Videos/YUV420/raftingNEW_352x288_113.yuv", "resources/Videos/YUV420/ModeGrid_raf_512my.dat", QSize(352, 288), 24, model::video::YUVType::YUV420, testContext);

	Frame::sptr testFrame = testVideo.getFrame(0);
	QVERIFY(testFrame->getMetadata().hasMbType());
	QVERIFY(testFrame->getMetadata().getMbType()[0][0] == MacroblockType::INTRA_4X4);
	QVERIFY(testFrame->getMetadata().getMbType()[0][9] == MacroblockType::INTRA_16X16);
	QVERIFY(testFrame->getMetadata().getMbType()[0][21] == MacroblockType::INTRA_4X4);
	QVERIFY(testFrame->getMetadata().getMbType()[1][0] == MacroblockType::INTRA_4X4);

	testFrame.reset();
	testFrame = testVideo.getFrame(testVideo.getFrameCount() - 1);
	QVERIFY(testFrame->getMetadata().getMbType()[17][21] == MacroblockType::INTER_SKIP);	
}
