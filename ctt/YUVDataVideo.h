#if !defined(_YUVDATAVIDEO_H)
#define _YUVDATAVIDEO_H

#include "DataVideo.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace video {

class YUVDataVideo : public DataVideo {
public:
	VideoMetadata getMetadata();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

}  // namespace video
}  // namespace model

#endif  //_YUVDATAVIDEO_H
