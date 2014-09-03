#include "HistogramWidget.h"

#include <QVBoxLayout>
#include <QPushButton>

#include "NotImplementedException.h"
#include "Histogram.h"

namespace view {

using ::exception::NotImplementedException;
using ::model::frame::histogram::Histogram;
using ::model::frame::Frame;

HistogramWidget::HistogramWidget(::model::player::VideoScrubber::sptr scrubber, QWidget *parent) : QWidget(parent), scrubber(scrubber) {
	scrubber->subscribe(this);
	currentHistogramType = Histogram::HISTOGRAM_TYPE_STRINGS.at(0);

	histogramPlot = new QCustomPlot();
	histogramPlot->plotLayout()->insertRow(0);
	histogramPlot->axisRect()->setAutoMargins(QCP::msNone);
	histogramPlot->axisRect()->setMargins(QMargins(0, 0, 0, 0));
	histogramPlot->xAxis->setRange(0, 255);
	histogramPlot->yAxis->setRange(0, 0.015);
	histogramPlot->xAxis->setVisible(false);
	histogramPlot->yAxis->setVisible(false);

	histogramBars = new QCPBars(histogramPlot->xAxis, histogramPlot->yAxis);
	histogramBars->setPen(QPen(Qt::black));
	histogramPlot->addPlottable(histogramBars);

	setupUi();

	update();
}

HistogramWidget::~HistogramWidget() {
	scrubber->unsubscribe(this);
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

	update();
}

void HistogramWidget::update() {
	Histogram::HistogramType type = Histogram::stringToType(currentHistogramType);
    Histogram::sptr histogram = Frame::getHistogram(scrubber->getCurrentFrame(), type);

	QVector<double> keys = QVector<double>();
	QVector<double> values = QVector<double>();

	for (unsigned int i = 0; i < Histogram::kSize; i++) {
		keys.append(i);
		values.append(histogram->getValue(i));
	}

	histogramBars->clearData();
	histogramBars->setData(keys, values);

	histogramBars->setName(currentHistogramType);
	QCPLayoutElement *oldTitle = histogramPlot->plotLayout()->element(0, 0);
	histogramPlot->plotLayout()->remove(oldTitle);
	histogramPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(histogramPlot, currentHistogramType));

	histogramPlot->replot();
}

}  // namespace view