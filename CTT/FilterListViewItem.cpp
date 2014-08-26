#include "FilterListViewItem.h"

using ::model::filter::Filter;
using ::model::filter::FilterParam;
using ::controller::FilterController;

namespace view {
	FilterListViewItem::FilterListViewItem(Filter::sptr filter, FilterController::sptr filterController) {
		this->filter = filter;
		filterParams = QList<FilterParamItem::sptr>();

		setColumnCount(2);
		setRowCount(filter->getParams().size());

		for each (FilterParam param in filter->getParams()) {
			FilterParamItem *paramRepresentation = new FilterParamItem(FilterParam::sptr(&param));
			filterParams.append(FilterParamItem::sptr(paramRepresentation));
			QObject::connect(paramRepresentation, SIGNAL(filterParamChanged(FilterParam::sptr)),
				this, SLOT(changeFilterParam(FilterParam::sptr)));
		}

		QObject::connect(this, SIGNAL(filterParamChanged(const Filter::sptr, FilterParam::sptr)),
			filterController.data(), SLOT(changeFilterParam(const Filter::sptr, FilterParam::sptr)));

		setupUi();
	}

	QString FilterListViewItem::getIdentifier() {
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
}