#ifndef _FFMPEGDATAVIDEO_H
#define _FFMPEGDATAVIDEO_H

extern "C"
{
#include "libavcodec\avcodec.h"
#include "libavformat\avformat.h"
#include "libswscale\swscale.h"
#include "libavutil\frame.h"
}

#define FFmpeg_PixelFormat PixelFormat
#undef PixelFormat

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "FileVideo.h"
#include "Frame.h"

namespace model {
namespace video {

class FFmpegDataVideo : public FileVideo {
public:
    typedef QScopedPointer<FFmpegDataVideo> uptr;
    typedef QSharedPointer<FFmpegDataVideo> sptr;
    typedef QWeakPointer<FFmpegDataVideo> wptr;

    FFmpegDataVideo(QString path, QSharedPointer<QOpenGLContext> context);

    ~FFmpegDataVideo();

    VideoMetadata getMetadata() const;

    virtual model::frame::Frame::sptr getFrame(unsigned int frameNumber) const Q_DECL_OVERRIDE;

    virtual unsigned int getFrameCount() const Q_DECL_OVERRIDE;
    virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
    virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
    virtual SaveableType saveableType() const Q_DECL_OVERRIDE{return getSaveableType(); }
    static ::model::saveable::Saveable::SaveableType getSaveableType() { return ::model::saveable::Saveable::fFmpegDataVideo; }
    static ::model::saveable::Saveable::sptr getDummy();

private:
    Q_DISABLE_COPY(FFmpegDataVideo);

    /**
     * Creates a dummy FFmpegDataVideo.
     */
    FFmpegDataVideo();

    void init();
    void loadVideo();
    ::model::frame::Frame::sptr getNextFrame() const;

    static const QString kPathAttrStr;

    QString path;

    AVFormatContext *avFormatContext = NULL;
    AVCodecContext *avCodecContext = NULL;
    QByteArray ffmpegErrorStr;

    int bestStreamNr;

    mutable ::model::frame::Frame::sptr lastFrame;
    mutable unsigned int lastFrameNr = -1;

    //int iFrameDistance = -1;
    //QList<int> iFramePositions;
    mutable unsigned int frameCount = -1;
    double fps;
};

}  // namespace video
}  // namespace model

#define PixelFormat FFmpeg_PixelFormat
#undef FFmpeg_PixelFormat

#endif  //_FFMPEGDATAVIDEO_H