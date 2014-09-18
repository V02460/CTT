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

	QObject::connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(filterSelectionChanged()));
	setSelectionMode(QAbstractItemView::NoSelection);
}

FilterListView::~FilterListView() {
	if (!video.isNull()) {
		video->unsubscribe(this);
	}
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

	items.clear();
	clear();
}

void FilterListView::update() {
	QList<AbstractListViewItem*> newItems;
	for each (Filter::sptr filter in video->getFilterList()) {
		newItems.append(new FilterListViewItem(filter, filterController, this));
	}
	setupUi(newItems);
}

void FilterListView::filterSelectionChanged() {
	//TODO bessere alternative überlegen
	/*QList<QTreeWidgetItem*> selected = selectedItems();

	int selectedFilterIndex = indexOfTopLevelItem(selected.at(0));

	if (selectedFilterIndex != -1 && static_cast<int>(video->getFilterCount()) > selectedFilterIndex) {
		emit selectedFilterChanged(video->getFilterList().value(selectedFilterIndex));
	}*/
}

}  // namespace view