#include "FrameMetadataWidget.h"

#include "NotImplementedException.h"

using ::exception::NotImplementedException;

namespace view { // TODO translations

using ::model::player::VideoScrubber;
using ::model::video::VideoMetadata;
using ::model::frame::FrameMetadata;

FrameMetadataWidget::FrameMetadataWidget(VideoScrubber::sptr scrubber, QWidget *parent) : scrubber(scrubber),
																						  QWidget(parent) {
	scrubber->subscribe(this);
	update();
}

FrameMetadataWidget::~FrameMetadataWidget() {
	scrubber->unsubscribe(this);
}

void FrameMetadataWidget::update() {
	// TODO may cause problems
	if (layout() != nullptr) {
		delete layout();
	}
	VideoMetadata video = scrubber->getVideoMetadata();
	FrameMetadata frame = scrubber->getCurrentFrame()->getMetadata();
	QBoxLayout *layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
	layout->addWidget(new QLabel("Frames per second: " + QString::number(video.getFPS()), this));
	layout->addWidget(new QLabel("Number of frames: " + QString::number(video.getLength()), this));
	for each (QString key in video.getAdditionalMetadata().keys()) {
		layout->addWidget(new QLabel(key + ": " + video.getData(key), this));
	}
	layout->addWidget(new QLabel("Video size: " + QString::number(frame.getSize().width()) + "x"
		                         + frame.getSize().height(), this));
	layout->addWidget(new QLabel(QString("Video does ") + (frame.hasMbType() ? "" : "not ")
		                         + "contain metablock types.", this));
	layout->addWidget(new QLabel(QString("Video does ") + (frame.hasMbMotionvectors() ? "" : "not ")
		                         + "contain metablock motion vectors.", this));
	setLayout(layout);
}

}  // namespace view