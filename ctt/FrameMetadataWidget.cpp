#include "FrameMetadataWidget.h"

#include "NotImplementedException.h"

using ::exception::NotImplementedException;

namespace view {

using ::model::player::VideoScrubber;
using ::model::video::VideoMetadata;
using ::model::frame::FrameMetadata;

FrameMetadataWidget::FrameMetadataWidget(VideoScrubber::sptr scrubber,
	                                     QWidget *parent) : scrubber(scrubber),
	                                                        QWidget(parent),
															layout(QBoxLayout::Direction::TopToBottom, this),
															fps(this),
															length(this),
															additionalVideoMetadata(),
															size(this),
															hasTypes(this),
															hasVectors(this) {
	scrubber->subscribe(this);
	VideoMetadata video = scrubber->getVideoMetadata();
	fps.setText("Frames per second: " + QString::number(video.getFPS()));
	layout.addWidget(&fps);
	length.setText("Number of frames: " + QString::number(video.getLength()));
	layout.addWidget(&length);
	for each (QString key in video.getAdditionalMetadata().keys()) {
		// TODO funktioniert?
		QLabel metadata(key + ":" + video.getData(key), this);
		additionalVideoMetadata.append(metadata);
		layout.addWidget(&metadata);
	}
	update();
	layout.addWidget(&size);
	layout.addWidget(&hasTypes);
	layout.addWidget(&hasVectors);
	setLayout(&layout);
}

FrameMetadataWidget::~FrameMetadataWidget() {
	scrubber->unsubscribe(this);
}

void FrameMetadataWidget::update() {
	FrameMetadata frame = scrubber->getCurrentFrame()->getMetadata();
	size.setText("Video size: " + QString::number(frame.getSize().width()) + "x" + frame.getSize().height());
	hasTypes.setText(QString("Video does ") + (frame.hasMbType() ? "" : "not ") + "contain metablock types.");
	hasVectors.setText(QString("Video does ") + (frame.hasMbMotionvectors() ? "" : "not ")
		               + "contain metablock motion vectors.");
}

}  // namespace view