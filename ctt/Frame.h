


#if !defined(_FRAME_H)
#define _FRAME_H

#include "Histogram.h"
#include "HistogramType.h"
#include "FrameMetadata.h"

class Frame {
public:
	FrameMetadata getMetadata();
	QOpenGLTexture getGLTexture();
	Histogram getHistogram(HistogramType type);
	void Frame(QOpenGLContext context, QImage image, FrameMetadata metadata);
private:
	QOpenGLContext glContext;
	QOpenGLTexture glTexture;
	FrameMetadata *metadata;
};

#endif  //_FRAME_H
