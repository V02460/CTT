#include "QObject"
#include <QtTest/QtTest>


class VideoMetadataTest :
	public QObject	
{
	Q_OBJECT

private slots:
	void noAdditionalMetadata();
	void noAdditionalMetadataInvalid();
	void withAdditionalMetadata();
	void withAdditionalMetadataInvalid();
};