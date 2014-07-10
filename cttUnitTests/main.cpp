#include "VideoMetadataTest.h"
#include "FrameTest.h"

int main(int argc, char *argv[])
{
	VideoMetadataTest videoMetadataTest;
	QTest::qExec(&videoMetadataTest, argc, argv);

	FrameTest frameTest;
	QTest::qExec(&frameTest, argc, argv);

	return 0;
}
