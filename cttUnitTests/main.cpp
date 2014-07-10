#include "VideoMetadataTest.h"

int main(int argc, char *argv[])
{
	VideoMetadataTest videoMetadataTest;
	QTest::qExec(&videoMetadataTest, argc, argv);

	return 0;
}