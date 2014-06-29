#if !defined(_ANALYSINGWIDGET_H)
#define _ANALYSINGWIDGET_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Player.h"
#include "ThumbnailListWidget.h"
#include "VideoAnalysingWidget.h"
#include "MainControlWidget.h"
#include <QList>

namespace view {
/**
 *	The AnalysingWidget basically unites the abilities to  display videos and their metadata, to control the player
 *	and to set the active videos.
 */
class AnalysingWidget : public QWidget {
private:
	Player player; /**< The player which plays all activated videos */
	QList<VideoAnalysingWidget> analysingWidgets; /**< The AnalysingWidgets which actually display videos and their metadata */
	ThumbnailListWidget thumbnailWidget; /**< The ThumbnalListWidget to choose the active videos and to add new videos */
	MainControlWidget mainControlWidget;/**< The MainControlWidget which provides the player functionalities */
};

}  // namespace view

#endif  //_ANALYSINGWIDGET_H
