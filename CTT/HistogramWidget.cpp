#include "HistogramWidget.h"

#include <QVBoxLayout>
#include <QPushButton>

#include "NotImplementedException.h"
#include "Histogram.h"

using ::exception::NotImplementedException;
using ::model::frame::histogram::Histogram;

namespace view {

HistogramWidget::HistogramWidget(::model::player::VideoScrubber::sptr scrubber, QWidget *parent) : QWidget(parent), scrubber(scrubber) {
	scrubber->subscribe(this);
	currentHistogramType = Histogram::HISTOGRAM_TYPE_STRINGS.at(0);
	histogramPlot = new QCustomPlot();
	histogramBars = new QCPBars(histogramPlot->xAxis, histogramPlot->yAxis);
	histogramPlot->addPlottable(histogramBars);

	setupUi();

	update();
}

void HistogramWidget::setupUi() {
	QVBoxLayout *layout = new QVBoxLayout();

	QPushButton *nextHistogram = new QPushButton(tr("NEXT_HISTOGRAM"));
	nextHistogram->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QObject::connect(nextHistogram, SIGNAL(clicked()), this, SLOT(next()));
	
	layout->addWidget(nextHistogram);
	layout->addWidget(histogramPlot);

	setLayout(layout);
}

void HistogramWidget::next() {
	int index = Histogram::HISTOGRAM_TYPE_STRINGS.indexOf(currentHistogramType);
	currentHistogramType = Histogram::HISTOGRAM_TYPE_STRINGS.at((index + 1) % Histogram::HISTOGRAM_TYPE_STRINGS.size());

	histogramBars->setName(currentHistogramType);

	update();
}

void HistogramWidget::update() {
	Histogram::HistogramType type = Histogram::stringToType(currentHistogramType);
	Histogram::sptr histogram = scrubber->getCurrentFrame()->getHistogram(type);

	QVector<double> keys = QVector<double>();
	QVector<double> values = QVector<double>();

	for (unsigned int i = 0; i < Histogram::kSize; i++) {
		keys.append(i);
		values.append(histogram->getValue(i));
	}

	histogramBars->clearData();
	histogramBars->setData(keys, values);

	histogramPlot->replot();
}

}  // namespace view