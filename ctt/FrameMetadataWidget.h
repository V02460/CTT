#if !defined(_FRAMEMETADATAWIDGET_H)
#define _FRAMEMETADATAWIDGET_H

#include "Observer.h"
#include "VideoScrubber.h"
#include <QWidget>

namespace view {

/**
 *	The FrameMetadataWidget displays the metadata information provided by a frame.
 *	Therefore it registers itself at a VideoScrubber to recieve the metadata for the current frame.
 */
class FrameMetadataWidget : public Observer , public QWidget{
public:
	/**
	 *	Creates a new FrameMetadataWidget which holds a VideoScrubber from where it gets the metadata for the current frame.
	 *
	 *	@param scrubber The VideoScrubber to regiser at and which provides the metadata.
	 */
	FrameMetadataWidget(VideoScrubber scrubber);

	private:
	VideoScrubber scrubber /**< The scrubber at which the FrameMetadataWidget is registered */;
};

}  // namespace view

#endif  //_FRAMEMETADATAWIDGET_H
