


#if !defined(_DIFFERENCEFACTORY_H)
#define _DIFFERENCEFACTORY_H

#include "FrameDiff.h"
#include "Video.h"

class DifferenceFactory {
public:
	List<QString> getAllDiffIDs();
	FrameDiff createDiff(QString id, Video video1, Video video2);
};

#endif  //_DIFFERENCEFACTORY_H
