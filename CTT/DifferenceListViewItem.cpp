#include "DifferenceListViewItem.h"

using ::model::difference::FrameDiff;

namespace view {
	DifferenceListViewItem::DifferenceListViewItem(FrameDiff::sptr diff, QWidget *parent) : AbstractListViewItem(parent) {
		//TODO erzeuge die tatsächliche anzeige
	}

	QString DifferenceListViewItem::getIdentifier() const {
		//TODO getName von FrameDiff
		return "";
	}
}