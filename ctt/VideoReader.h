


#if !defined(_VIDEOREADER_H)
#define _VIDEOREADER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Frame.h"

class VideoReader {
public:
	Frame getFrame(int frameNumber);
};

#endif  //_VIDEOREADER_H
