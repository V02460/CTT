#include "FrameMetadataWidget.h"

#include "NotImplementedException.h"

using ::exception::NotImplementedException;

namespace view {

using ::model::player::VideoScrubber;
using ::model::video::VideoMetadata;
using ::model::frame::FrameMetadata;

FrameMetadataWidget::FrameMetadataWidget(VideoScrubber::sptr scrubber, QWidget *parent) : scrubber(scrubber),
                                                                                          size(this),
																						  hasTypes(this),
																						  hasVectors(this),
																						  QWidget(parent) {
	scrubber->subscribe(this);
	VideoMetadata video = scrubber->getVideoMetadata();
	QBoxLayout *layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
	layout->addWidget(new QLabel("Frames per second: " + QString::number(video.getFPS()), this));
	layout->addWidget(new QLabel("Number of frames: " + QString::number(video.getLength()), this));
	for each (QString key in video.getAdditionalMetadata().keys()) {
		layout->addWidget(new QLabel(key + ": " + video.getData(key), this));
	}
	update();
	layout->addWidget(&size);
	layout->addWidget(&hasTypes);
	layout->addWidget(&hasVectors);
	setLayout(layout);
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