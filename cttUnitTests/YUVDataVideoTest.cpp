#include "YUVDataVideoTest.h"

#include "CustomTestingMacros.h"
#include "VideoMetadata.h"
#include "IllegalArgumentException.h"
#include "..\CTT\YUVDataVideo.h"

using namespace model::video;
using namespace exception;


void YUVDataVideoTest::dummyTest()
{
	QVERIFY2(YUVDataVideo::getDummy()->isDummy(), "Dummy YUVDataVideo claimed not to be a dummy!");	
}
