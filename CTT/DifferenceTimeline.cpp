#include "DifferenceTimeline.h"

#include <QHBoxLayout>

#include "ViewState.h"

using ::model::saveable::SaveableList;
using ::model::difference::FrameDiff;
using ::model::player::Player;

namespace view {
	DifferenceTimeline::DifferenceTimeline(SaveableList<FrameDiff>::sptr differences, Player::sptr player, QWidget *parent) : AbstractTimeline(parent), differences(differences), player(player) {
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
	}

	void DifferenceTimeline::update() {
		if (currentFrameNumber != player->getCurrentFrameNumber()) {
			//TODO range anpassen
		} else if (frameCount != player->getVideoLength()) {
			if (player->getVideoLength() != 0) {
				graphPlot->xAxis->setRange(0, player->getVideoLength());
			} else {
				graphPlot->xAxis->setRange(0, 1);
			}

			graphPlot->replot();
		} else {
			updateDifferences();
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

		for (int i = 0; i < differences->getSize(); i++) {
			QVector<double> x = QVector<double>();
			QVector<double> y = QVector<double>();
			for (int j = 0; j < static_cast<int>(differences->get(i)->getFrameCount()); j++) {
				x[j] = j;
				y[j] = qBound(0.0, differences->get(i)->getDiff(j), 1.0);
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
		graphPlot->yAxis->setRange(0, 1);

		graphPlot->replot();
	}
}  // namespace view