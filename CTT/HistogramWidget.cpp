#include "HistogramWidget.h"

#include <QVBoxLayout>
#include <QPushButton>

#include "Histogram.h"

namespace view {

using ::model::frame::histogram::Histogram;
using ::model::frame::Frame;

HistogramWidget::HistogramWidget(::model::player::VideoScrubber::sptr scrubber, QWidget *parent) : QWidget(parent), scrubber(scrubber), histogramMaxY(0.025), autoRecalculation(false) {
	scrubber->subscribe(this);
	currentHistogramType = Histogram::HISTOGRAM_TYPE_STRINGS.at(0);

	histogramPlot = new QCustomPlot();
	histogramPlot->plotLayout()->insertRow(0);
	histogramPlot->axisRect()->setAutoMargins(QCP::msNone);
	histogramPlot->axisRect()->setMargins(QMargins(0, 0, 0, 0));
	histogramPlot->xAxis->setRange(0, 255);
	histogramPlot->yAxis->setRange(0, histogramMaxY);
	histogramPlot->xAxis->setVisible(false);
	histogramPlot->yAxis->setVisible(false);

	histogramBars = new QCPBars(histogramPlot->xAxis, histogramPlot->yAxis);
	histogramBars->setPen(QPen(Qt::black));
	histogramPlot->addPlottable(histogramBars);

	setupUi();

	recalculateHistogram();
}

HistogramWidget::~HistogramWidget() {
	scrubber->unsubscribe(this);
}

void HistogramWidget::setupUi() {
	QVBoxLayout *layout = new QVBoxLayout();

	QHBoxLayout *buttonLayout = new QHBoxLayout();

	QPushButton *nextHistogram = new QPushButton(tr("NEXT_HISTOGRAM"));
	nextHistogram->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QObject::connect(nextHistogram, SIGNAL(clicked()), this, SLOT(next()));
	buttonLayout->addWidget(nextHistogram);

	btnAutoRecalculation = new QPushButton(tr("START_AUTO_UPDATE"));
	btnAutoRecalculation->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QObject::connect(btnAutoRecalculation, SIGNAL(clicked()), this, SLOT(toggleAutoRecalculation()));
	buttonLayout->addWidget(btnAutoRecalculation);

	QPushButton *btnUpdate = new QPushButton(tr("UPDATE_HISTOGRAM"));
	btnUpdate->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QObject::connect(btnUpdate, SIGNAL(clicked()), this, SLOT(recalculateHistogram()));
	buttonLayout->addWidget(btnUpdate);

	layout->addLayout(buttonLayout);
	layout->addWidget(histogramPlot);

	setLayout(layout);
}

void HistogramWidget::next() {
	int index = Histogram::HISTOGRAM_TYPE_STRINGS.indexOf(currentHistogramType);
	currentHistogramType = Histogram::HISTOGRAM_TYPE_STRINGS.at((index + 1) % Histogram::HISTOGRAM_TYPE_STRINGS.size());

	recalculateHistogram();
}

void HistogramWidget::update() {
	if (autoRecalculation) {
		recalculateHistogram();
	}
}

::model::player::VideoScrubber::sptr HistogramWidget::getScrubber() {
	return scrubber;
}

void HistogramWidget::recalculateHistogram() {
	Histogram::HistogramType type = Histogram::stringToType(currentHistogramType);
	Histogram::sptr histogram = Frame::getHistogram(scrubber->getCurrentFrame(), type);

	QVector<double> keys = QVector<double>();
	QVector<double> values = QVector<double>();

	for (unsigned int i = 0; i < Histogram::kSize; i++) {
		keys.append(i);
		double value = histogram->getValue(i);
		values.append(value);

		if (value > histogramMaxY) {
			histogramMaxY = value;
			histogramPlot->yAxis->setRange(0, histogramMaxY);
		}
	}

	histogramBars->clearData();
	histogramBars->setData(keys, values);

	histogramBars->setName(currentHistogramType);
	QCPLayoutElement *oldTitle = histogramPlot->plotLayout()->element(0, 0);
	histogramPlot->plotLayout()->remove(oldTitle);
	histogramPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(histogramPlot, currentHistogramType));

	histogramPlot->replot();
}

void HistogramWidget::toggleAutoRecalculation() {
	autoRecalculation = !autoRecalculation;

	if (autoRecalculation) {
		btnAutoRecalculation->setText(tr("STOP_AUTO_UPDATE"));
	} else {
		btnAutoRecalculation->setText(tr("START_AUTO_UPDATE"));
	}
}

}  // namespace view