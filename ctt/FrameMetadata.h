


#if !defined(_FRAMEMETADATA_H)
#define _FRAMEMETADATA_H


class FrameMetadata {
public:
	QSize getSize();
	int[] getMbType();
	int[] getMbPartition();
	int[] getMbMotionvectors();
	bool hasMbType();
	bool hasMbPartions();
	bool hasMbType();
private:
	QSize size;
	int[] mbTypes;
	int[] mbPartions;
	int[] mbMotionvectors;
};

#endif  //_FRAMEMETADATA_H
