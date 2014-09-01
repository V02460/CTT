#include "AbstractListView.h"

#include <QTreeWidgetItem>
#include <QBoxLayout>
#include <QLabel>

#include "ListedPushButton.h"

using ::model::filter::FilteredVideo;

namespace view {

	AbstractListView::AbstractListView(QWidget *parent) : QTreeWidget(parent), items() {
	setIndentation(0);
	// TODO setItemsExpandable(true);
	setRootIsDecorated(true);
}

void AbstractListView::removeAllItems() {
	items.clear();
	clear();
}

void AbstractListView::setupUi() {
	for (int i = 0; i < items.size(); i++) {
		// Create and set header
		QTreeWidgetItem *item = new QTreeWidgetItem(this);
		addTopLevelItem(item);

		QWidget *itemWidget = new QWidget(this);
		QHBoxLayout *itemWidgetLayout = new QHBoxLayout(this);

		QLabel *identifierLabel = new QLabel(items[i]->getIdentifier(), this);
		itemWidgetLayout->addWidget(identifierLabel);
		itemWidgetLayout->addStretch();

		// TODO Add icon
		ListedPushButton *removeButton = new ListedPushButton(i, this);
		removeButton->setText(tr("REMOVE"));
		itemWidgetLayout->addWidget(removeButton);
		QObject::connect(removeButton, SIGNAL(clicked(bool, int)), this, SLOT(buttonRemoveClicked(bool, int)));

		itemWidget->setLayout(itemWidgetLayout);
		setItemWidget(item, 0, itemWidget);

		// Create and set child
		QTreeWidgetItem *childItem = new QTreeWidgetItem(this);
		childItem->setDisabled(true);
		item->addChild(childItem);
		setItemWidget(childItem, 0, items[i]);
	}
}

void AbstractListView::buttonRemoveClicked(bool checked, int id) {
	emit elementRemoved(id);
}

void AbstractListView::setVideo(FilteredVideo::sptr) {}

void AbstractListView::removeVideo() {}

}  // namespace view