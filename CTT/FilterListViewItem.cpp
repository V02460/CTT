#include "FilterListViewItem.h"

#include "NotImplementedException.h"
#include <QHeaderView>

using ::model::filter::Filter;
using ::model::filter::FilterParam;
using ::controller::FilterController;
using ::exception::NotImplementedException;

namespace view {

FilterListViewItem::FilterListViewItem(Filter::sptr filter,
	                                   FilterController::sptr filterController,
									   QWidget *parent) : AbstractListViewItem(parent),
									                      filter(filter),
									                      filterParams() {
	identifierLabel = new QLabel(filter->getName());
	setColumnCount(2);
	horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
	setRowCount(filter->getParams().size());
	filter->subscribe(this);
	update();
	QObject::connect(this, SIGNAL(filterParamChanged(const ::model::filter::Filter::sptr,
		                                             ::model::filter::FilterParam::sptr)),
		             filterController.data(), SLOT(changeFilterParam(const ::model::filter::Filter::sptr,
					                               ::model::filter::FilterParam::sptr)));
	setSelectionMode(QAbstractItemView::NoSelection);
}

QLabel* FilterListViewItem::getIdentifier() const {
	return identifierLabel;
}

void FilterListViewItem::changeFilterParam(FilterParam::sptr newParam) {
	emit filterParamChanged(filter, newParam);
}

void FilterListViewItem::setupUi() {
	for (int i = 0; i < filterParams.size(); i++) {
		setCellWidget(i, 0, filterParams[i]->getNameLabel());
		setCellWidget(i, 1, filterParams[i]->getInteractibleComponent());

		setHeight(getHeight() + filterParams[i]->getInteractibleComponent()->height() + 3);
	}
}

void FilterListViewItem::update() {
	setHeight(0);

	for each (FilterParam::sptr param in filter->getParams()) {
		FilterParamItem *paramRepresentation = new FilterParamItem(param);
		filterParams.append(FilterParamItem::sptr(paramRepresentation));
		QObject::connect(paramRepresentation, SIGNAL(filterParamChanged(::model::filter::FilterParam::sptr)),
			this, SLOT(changeFilterParam(::model::filter::FilterParam::sptr)));
	}

	setupUi();
}

}  // namespace view