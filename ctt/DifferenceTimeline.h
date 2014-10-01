#ifndef _DIFFERENCETIMELINE_H
#define _DIFFERENCETIMELINE_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QShowEvent>

#include "AbstractTimeline.h"
#include "SaveableList.h"
#include "FrameDiff.h"
#include "Player.h"
#include "qcustomplot.h"

namespace view {

/**
 * The DifferenceTimeline is the visual representation of a set of differences.
 * The active differences are simply plotted as overlapping different-colored graphs.
 */
class DifferenceTimeline : public AbstractTimeline {
public:
    typedef QScopedPointer<DifferenceTimeline> uptr;
    typedef QSharedPointer<DifferenceTimeline> sptr;
    typedef QWeakPointer<DifferenceTimeline> wptr;

	DifferenceTimeline(::model::saveable::SaveableList<::model::difference::FrameDiff>::sptr differences, ::model::player::Player::sptr player, QWidget *parent = 0);

	~DifferenceTimeline();

	virtual void update() Q_DECL_OVERRIDE;

protected:
	virtual void showEvent(QShowEvent *ev) Q_DECL_OVERRIDE;
private:
	void updateDifferences();
	void setupUi();

	static const int frameskip = 1;

	::model::saveable::SaveableList<::model::difference::FrameDiff>::sptr differences;
	::model::player::Player::sptr player;
	int frameCount;
	int currentFrameNumber;
	bool wasPlaying;
	bool needsRecalculation;
	QCustomPlot *graphPlot;
};

}  // namespace view

#endif  //_DIFFERENCETIMELINE_H
