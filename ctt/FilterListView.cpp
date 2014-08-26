#include "FilterListView.h"

#include "FilterListViewItem.h"

using ::controller::FilterController;
using ::model::filter::FilteredVideo;
using ::model::filter::Filter;

namespace view {
	FilterListView::FilterListView(FilterController::sptr filterController, QWidget *parent) : AbstractListView(parent) {
		this->filterController = filterController;

		QObject::connect(this, SIGNAL(filterMoved(int, int)), filterController.data(), SLOT(moveFilter(int, int)));
		QObject::connect(this, SIGNAL(elementRemoved(int)), filterController.data(), SLOT(removeFilter(int)));
		QObject::connect(this, SIGNAL(videoChanged(::model::filter::FilteredVideo::sptr)),
			filterController.data(), SLOT(setVideo(::model::filter::FilteredVideo::sptr)));
	}

	void FilterListView::setVideo(FilteredVideo::sptr video) {
		video->unsubscribe(*this);
		this->video = video;
		video->subscribe(Observer::sptr(this));

		update();
	}

	void FilterListView::update() {
		removeAllItems();

		for each (Filter::sptr filter in video->getFilterList()) {
			items.append(FilterListViewItem::sptr(new FilterListViewItem(filter, filterController)));
		}

		setupUi();
	}
}  // namespace view