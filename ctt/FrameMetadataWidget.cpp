#include "FrameMetadataWidget.h"

#include "NotImplementedException.h"

using ::exception::NotImplementedException;

namespace view { // TODO translations

using ::model::player::VideoScrubber;
using ::model::video::VideoMetadata;
using ::model::frame::FrameMetadata;

FrameMetadataWidget::FrameMetadataWidget(VideoScrubber::sptr scrubber, QWidget *parent) : QWidget(parent),
                                                                                          scrubber(scrubber),
																						  fpsWidget(new QLabel(this)),
																						  framecountWidget(new QLabel(this)),
																						  sizeWidget(new QLabel(this)),
																						  blockWidget(new QLabel(this)),
																						  vectorWidget(new QLabel(this)),
																						  moreMetadata() {
	scrubber->subscribe(this);
	QBoxLayout *layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
	layout->addWidget(fpsWidget);
	layout->addWidget(framecountWidget);
	layout->addWidget(sizeWidget);
	layout->addWidget(blockWidget);
	layout->addWidget(vectorWidget);
	setLayout(layout);
}

FrameMetadataWidget::~FrameMetadataWidget() {
	scrubber->unsubscribe(this);
}

void FrameMetadataWidget::update() {
	VideoMetadata video = scrubber->getVideoMetadata();
	FrameMetadata frame = scrubber->getCurrentFrame()->getMetadata();
	fpsWidget->setText(tr("FPS") + QString::number(video.getFPS()));
	framecountWidget->setText(tr("FRAMECOUNT") + QString::number(video.getLength()));
	sizeWidget->setText(tr("VIDEO_SIZE") + QString::number(frame.getSize().width()) + "x" + frame.getSize().height());
	blockWidget->setText(tr("HAS_BLOCK") + (frame.hasMbType() ? tr("YES") : tr("NO")));
	vectorWidget->setText(tr("HAS_VECTRO") + (frame.hasMbMotionvectors() ? tr("YES") : tr("NO")));
	for (int i = 0; i < moreMetadata.length(); i++) {
		layout()->removeWidget(moreMetadata[i].data());
	}
	moreMetadata.clear();
	for each (QString key in video.getAdditionalMetadata().keys()) {
		QLabel *metadata = new QLabel(key + ": " + video.getAdditionalMetadata().value(key));
		moreMetadata.append(QSharedPointer<QLabel>(metadata));
		layout()->addWidget(metadata);
	}
}

}  // namespace view