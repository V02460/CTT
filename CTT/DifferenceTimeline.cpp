#include "DifferenceTimeline.h"

#include <QHBoxLayout>

#include "ViewState.h"

using ::model::saveable::SaveableList;
using ::model::difference::FrameDiff;
using ::model::player::Player;

namespace view {
	DifferenceTimeline::DifferenceTimeline(SaveableList<FrameDiff>::sptr differences, Player::sptr player, QWidget *parent) : AbstractTimeline(parent), differences(differences), player(player), wasPlaying(false), needsRecalculation(false), currentFrameNumber(0), frameCount(0) {
		differences->subscribe(this);
		player->subscribe(this);

		frameCount = player->getVideoLength();
		currentFrameNumber = player->getCurrentFrameNumber();

		setupUi();
		update();
	}

	DifferenceTimeline::~DifferenceTimeline() {
		differences->unsubscribe(this);
		player->unsubscribe(this);

		for (int i = 0; i < differences->getSize(); i++) {
			differences->get(i)->unsubscribe(this);
		}
	}

	void DifferenceTimeline::update() {
		if (currentFrameNumber != player->getCurrentFrameNumber()) {
			//TODO range anpassen
			currentFrameNumber = player->getCurrentFrameNumber();
		} else if (frameCount != player->getVideoLength()) {
			if (player->getVideoLength() != 0) {
				graphPlot->xAxis->setRange(0, player->getVideoLength());
			} else {
				graphPlot->xAxis->setRange(0, 1);
			}

			graphPlot->replot();

			frameCount = player->getVideoLength();
		} else if (wasPlaying != player->isPlaying()) {
			wasPlaying = player->isPlaying();
		} else {
			if (isVisible()) {
				updateDifferences();
			}
			else {
				needsRecalculation = true;
			}
		}
	}

	void DifferenceTimeline::setupUi() {
		graphPlot = new QCustomPlot(this);

		QHBoxLayout *layout = new QHBoxLayout(this);
		layout->addWidget(graphPlot);

		setLayout(layout);
	}

	void DifferenceTimeline::updateDifferences() {
		graphPlot->clearGraphs();

		double maxY = 0;

		for (int i = 0; i < differences->getSize(); i++) {
			differences->get(i)->subscribe(this);

			int differenceLength = static_cast<int>(differences->get(i)->getFrameCount());
			QVector<double> x = QVector<double>(differenceLength);
			QVector<double> y = QVector<double>(differenceLength);
			for (int j = 0; j < differenceLength; j++) {
				x[j] = j;
				y[j] = qBound(0.0, differences->get(i)->getDiff(j), 1.0);
				if (y[j] > maxY) {
					maxY = y[j];
				}
			}
			graphPlot->addGraph(graphPlot->xAxis, graphPlot->yAxis);
			graphPlot->graph(i)->setPen(QPen(ViewState::getColorFromIndex(i)));
			graphPlot->graph(i)->setLineStyle(QCPGraph::lsLine);
			graphPlot->graph(i)->setData(x, y);
		}

		if (player->getVideoLength() != 0) {
			graphPlot->xAxis->setRange(0, player->getVideoLength() - 1);
		} else {
			graphPlot->xAxis->setRange(0, 1);
		}
		graphPlot->yAxis->setRange(0, maxY * 1.1);

		graphPlot->replot();
	}

	void DifferenceTimeline::showEvent(QShowEvent *ev) {
		AbstractTimeline::showEvent(ev);

		if (needsRecalculation) {
			updateDifferences();
		}
	}
}  // namespace view