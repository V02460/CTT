#include "FilterListView.h"

#include "FilterListViewItem.h"

using ::controller::FilterController;
using ::model::filter::FilteredVideo;
using ::model::filter::Filter;

namespace view {

FilterListView::FilterListView(FilterController::sptr filterController,
	                           QWidget *parent) : AbstractListView(parent),
							                      video(),
                                                  filterController(filterController) {
	QObject::connect(this, SIGNAL(filterMoved(int, int)), filterController.data(), SLOT(moveFilter(int, int)));
	QObject::connect(this, SIGNAL(elementRemoved(int)), filterController.data(), SLOT(removeFilter(int)));
	QObject::connect(this, SIGNAL(videoChanged(::model::filter::FilteredVideo::sptr)),
		             filterController.data(), SLOT(setVideo(::model::filter::FilteredVideo::sptr)));
}

void FilterListView::setVideo(FilteredVideo::sptr newVideo) {
	removeVideo();
	video = newVideo;
	video->subscribe(this);
	update();
	emit videoChanged(newVideo);
}

void FilterListView::removeVideo() {
	if (!video.isNull()) {
		video->unsubscribe(this);
	}

	removeAllItems();
	setupUi();
}

void FilterListView::update() {
	removeAllItems();
	for each (Filter::sptr filter in video->getFilterList()) {
		items.append(new FilterListViewItem(filter, filterController, this));
	}
	setupUi();
}

}  // namespace view