


#if !defined(_VIDEOREADER_H)
#define _VIDEOREADER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Frame.h"

class VideoReader {
public:
	typedef QScopedPointer<VideoReader> uptr;
	typedef QSharedPointer<VideoReader> sptr;
	typedef QWeakPointer<VideoReader> wptr;

	Frame getFrame(int frameNumber);
};

#endif  //_VIDEOREADER_H
