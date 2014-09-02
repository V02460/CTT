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
	layout->addWidget(new QLabel(tr("FPS") + QString::number(video.getFPS()), this));
	layout->addWidget(new QLabel(tr("FRAMECOUNT") + QString::number(video.getLength()), this));
	for each (QString key in video.getAdditionalMetadata().keys()) {
		layout->addWidget(new QLabel(key + ": " + video.getData(key), this));
	}
	layout->addWidget(new QLabel(tr("VIDEO_SIZE") + QString::number(frame.getSize().width()) + "x"
		                         + frame.getSize().height(), this));
	layout->addWidget(new QLabel(tr("METADATA_START") + (frame.hasMbType() ? "" : tr("NOT"))
		                         + tr("METABLOCK_END"), this));
	layout->addWidget(new QLabel(tr("METADATA_START") + (frame.hasMbMotionvectors() ? "" : tr("NOT"))
		                         + tr("MOTIONVECTOR_END"), this));
	setLayout(layout);
}

}  // namespace view