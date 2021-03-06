#include "FrameMetadataWidget.h"

namespace view { // TODO translations

using ::model::player::VideoScrubber;
using ::model::video::VideoMetadata;
using ::model::frame::FrameMetadata;

FrameMetadataWidget::FrameMetadataWidget(VideoScrubber::sptr scrubber, QWidget *parent) : QScrollArea(parent),
                                                                                          scrubber(scrubber),
																						  contentsWidget(new QWidget(this)),
																						  identifierWidget(new QLabel(contentsWidget)),
																						  fpsWidget(new QLabel(contentsWidget)),
																						  framecountWidget(new QLabel(contentsWidget)),
																						  sizeWidget(new QLabel(contentsWidget)),
																						  blockWidget(new QLabel(contentsWidget)),
																						  vectorWidget(new QLabel(contentsWidget)),
																						  moreMetadata() {
	scrubber->subscribe(this);
	setupUi();
	update();
}

FrameMetadataWidget::~FrameMetadataWidget() {
	scrubber->unsubscribe(this);
}

void FrameMetadataWidget::setupUi() {
	QBoxLayout *layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
	identifierWidget->setText(tr("FILE_NAME") + scrubber->getVideo()->getIdentifier());
	layout->addWidget(identifierWidget);
	layout->addWidget(fpsWidget);
	layout->addWidget(framecountWidget);
	layout->addWidget(sizeWidget);
	layout->addWidget(blockWidget);
	layout->addWidget(vectorWidget);
	layout->setContentsMargins(2, 2, 2, 2);
	contentsWidget->setLayout(layout);
	setWidget(contentsWidget);
}

void FrameMetadataWidget::update() {
	VideoMetadata video = scrubber->getVideoMetadata();
	FrameMetadata frame = scrubber->getCurrentFrame()->getMetadata();
	fpsWidget->setText(tr("FPS") + QString::number(video.getFPS()));
	framecountWidget->setText(tr("FRAMECOUNT") + QString::number(video.getLength()));
	sizeWidget->setText(tr("VIDEO_SIZE") + QString::number(frame.getSize().width()) + "x" + QString::number(frame.getSize().height()));
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