#ifndef _FFMPEGDATAVIDEO_H
#define _FFMPEGDATAVIDEO_H

extern "C"
{
#include "dev\include\libavcodec\avcodec.h"
#include "dev\include\libavformat\avformat.h"
#include "dev\include\libswscale\swscale.h"
#include "dev\include\libavutil\frame.h"
}

#pragma comment(lib, "dev\\lib\\avformat.lib")
#pragma comment(lib, "dev\\lib\\avcodec.lib")
#pragma comment(lib, "dev\\lib\\swscale.lib")
#pragma comment(lib, "dev\\lib\\avutil.lib")

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QDir>

#include "Video.h"
#include "Frame.h"
#include "Memento.h"
#include "FileVideo.h"

namespace model {
namespace video {

/**
 * A Video read from a mpeg-2, mpeg-4 part 2 or mpeg-4 part 10 video file.
 */
class FFmpegDataVideo : public FileVideo {
public:
    typedef QScopedPointer<FFmpegDataVideo> uptr;
    typedef QSharedPointer<FFmpegDataVideo> sptr;
    typedef QWeakPointer<FFmpegDataVideo> wptr;

    /**
     * Creates a new FFmpegDataVideo representing the mpeg-2, mpeg-4 part 2 or mpeg-4 part 10 video at the submitted
     * location in the file system.
     *
     * @param path the path to the video file which will be loaded
     * @param context the context in which the video creates its frames
     * @throws IOException if the file at the submitted location can't be accessed.
     * @throws FFmpegException if ffmpeg isn't able to use the file as a video file it can open and decode
     */
	FFmpegDataVideo(QString path, QSharedPointer<QOpenGLContext> context);

	~FFmpegDataVideo();

    VideoMetadata getMetadata() const;

    virtual model::frame::Frame::sptr getFrame(unsigned int frameNumber) const;

	virtual ::model::saveable::Saveable::SaveableType getType() const;

private:
	//Information about the videoFile
	AVFormatContext *videoFormatContext;
	//Context of the codec used by the first video stream (the one that will be used)
	AVCodecContext *codecContext;
	//number of the first video stream (the one that will be used)
	int videoStreamNr;
	//the codec used to decode the video
	AVCodec *vCodec;

};

}  // namespace video
}  // namespace model

#endif  //_FFMPEGDATAVIDEO_H
