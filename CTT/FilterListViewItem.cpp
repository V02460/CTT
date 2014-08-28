#include "FilterListViewItem.h"

#include "NotImplementedException.h"

using ::model::filter::Filter;
using ::model::filter::FilterParam;
using ::controller::FilterController;
using ::exception::NotImplementedException;

namespace view {

FilterListViewItem::FilterListViewItem(Filter::sptr filter, FilterController::sptr filterController) {
	this->filter = filter;
	filterParams = QList<FilterParamItem::sptr>();

	setColumnCount(2);
	setRowCount(filter->getParams().size());

	for each (FilterParam param in filter->getParams()) {
		FilterParamItem *paramRepresentation = new FilterParamItem(FilterParam::sptr(&param));
		filterParams.append(FilterParamItem::sptr(paramRepresentation));
		QObject::connect(paramRepresentation, SIGNAL(filterParamChanged(::model::filter::FilterParam::sptr)),
			             this, SLOT(changeFilterParam(::model::filter::FilterParam::sptr)));
	}

	QObject::connect(this, SIGNAL(filterParamChanged(const ::model::filter::Filter::sptr, ::model::filter::FilterParam::sptr)),
		filterController.data(), SLOT(changeFilterParam(const ::model::filter::Filter::sptr, ::model::filter::FilterParam::sptr)));

	setupUi();
}

QString FilterListViewItem::getIdentifier() const {
	return filter->getName();
}

void FilterListViewItem::changeFilterParam(FilterParam::sptr newParam) {
	emit filterParamChanged(filter, newParam);
}

void FilterListViewItem::setupUi() {
	for (int i = 0; i < filterParams.size(); i++) {
		setCellWidget(i, 0, filterParams.at(i)->getNameLabel());
		setCellWidget(i, 1, filterParams.at(i)->getInteractibleComponent());
	}
}

void FilterListViewItem::update() {
	throw new NotImplementedException();
}

}  // namespace view