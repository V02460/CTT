#include "FilterListViewElement.h"

namespace view{
	FilterListViewElement::FilterListViewElement(model::filter::Filter::sptr filter,
		controller::FilterController::sptr controller, QWidget *parent) : QTableWidget(parent) {
		this->filter = filter;
		filter->subscribe(FilterListViewElement::sptr(this));

		QObject::connect(this, SIGNAL(changeFilterParam(const ::model::filter::Filter &filter,
			::model::filter::FilterParam param)), controller.data(), SLOT(changeFilterParam
			(const ::model::filter::Filter &filter, ::model::filter::FilterParam param)));
		
		setupUi();
	}

	void FilterListViewElement::setupUi() {
		QList<model::filter::FilterParam> params = filter->getParams();

		setColumnCount(2);
		setRowCount(params.size());

		for each (::model::filter::FilterParam param in params) {

		}
	}
}