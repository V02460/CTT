#if !defined(_FFMPEGDATAVIDEO_H)
#define _FFMPEGDATAVIDEO_H

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
	/**
	 * Creates a new FFmpegDataVideo representing the mpeg-2, mpeg-4 part 2 or mpeg-4 part 10 video at the submitted location in the file system.
	 * @param path the path to the video file which will be loaded
	 * @param context the context in which the video creates its frames
	 * @throws IOException if the file at the submitted location can't be accessed.
	 * @throws InvalidArgumentException if the file at the submitted location isn't a valid mpeg-2, mpeg-4 part 2 or mpeg-4 part 10 video file
	 */
	FFmpegDataVideo(QDir path, QOpenGLContext context);

	VideoMetadata getMetadata();

	Frame getFrame(int frameNumber);

	Memento getMemento();

	void restore(Memento memento);

    static Saveable* getDummy();

private:
	/**
	 * Creates a dummy FFmpegDataVideo.
	 */
	FFmpegDataVideo(QDir path);
};

}  // namespace video
}  // namespace model

#endif  //_FFMPEGDATAVIDEO_H
