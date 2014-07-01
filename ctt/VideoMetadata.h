#if !defined(_VIDEOMETADATA_H)
#define _VIDEOMETADATA_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QString>

namespace model {
namespace video {

/**
 * Represents globally valid Metadata of a Video like length and resolution. Can also store custom metadata.
 *
 */
class VideoMetadata {
public:
    typedef QScopedPointer<VideoMetadata> uptr;
    typedef QSharedPointer<VideoMetadata> sptr;
    typedef QWeakPointer<VideoMetadata> wptr;

    /**
     * Creates a new VideoMetadata object, initialized with resolution, default playback speed, length and a map of
     * custom data.
     *
     * @param size the resolution of the Video described by this object
     * @param fps the default playback speed of the Video described by this object
     * @param length the length in frames of the Video described by this object
     * @param additionalData custom data describing the Video described by this object, entry labels are mapped to
     *     values
     */
    VideoMetadata(QSize size, double fps, unsigned int length, QMap<QString, QString> additionalData);

    /**
     * Creates a new VideoMetadata object, initialized with resolution, default playback speed and length.
     *
     * @param size the resolution of the Video described by this object
     * @param fps the default playback speed of the Video described by this object
     * @param length the length in frames of the Video described by this object
     */
    VideoMetadata(QSize size, double fps, unsigned int length);

    /**
     * Checks whether metadata with the submitted label is available.
     *
     * @param key it will be checked whether metadata with this label is available
     * @return bool true only if metadata with the submitted label is available
     */
    bool hasData(QString key);

    /**
     * Returns the metadata with the submitted label.
     *
     * @param key the metadata with this label will be returned.
     * @return QString the metadata with the submitted label.
     */
    QString getData(QString key);

    /**
     * Returns the size (i.e. resolution) of the Video described by this object.
     *
     * @return QSize the size (i.e. resolution) of the Video described by this object
     */
    QSize getSize();

    /**
     * Returns the default playback speed in frames per second of the Video described by this object.
     *
     * @return double the default playback speed in frames per second of the Video described by this object
     */
    double getFPS();

    /**
     * Returns the length in frames of the Video described by this object.
     *
     * @return unsigned int the length in frames of the Video described by this object
     */
    unsigned int getLength();

private:
    QSize size; /**< The resolution of the Video described by this object. */
    double fps; /**< The default playback speed of the Video described by this object. */
    unsigned int length; /**< The length in frames of the Video described by this object. */
};

}  // namespace video
}  // namespace model

#endif  //_VIDEOMETADATA_H
