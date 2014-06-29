#if !defined(_FFMPEGDATAVIDEO_H)
#define _FFMPEGDATAVIDEO_H

#include "DataVideo.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace video {

class FFmpegDataVideo : public DataVideo {
public:
	VideoMetadata getMetadata();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

}  // namespace video
}  // namespace model

#endif  //_FFMPEGDATAVIDEO_H
