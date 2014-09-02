#include "AbstractListView.h"

#include <QTreeWidgetItem>
#include <QBoxLayout>
#include <QLabel>
#include <QHeaderView>

#include "ListedPushButton.h"

using ::model::filter::FilteredVideo;

namespace view {

	AbstractListView::AbstractListView(QWidget *parent) : QTreeWidget(parent), items() {
	setIndentation(0);
	setItemsExpandable(true);
	//setRootIsDecorated(true);
	//invisibleRootItem()->setChildIndicatorPolicy(QTreeWidgetItem::DontShowIndicatorWhenChildless);
	header()->setVisible(false);
	header()->setSectionResizeMode(QHeaderView::Stretch);
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

		QLabel *identifierLabel = items[i]->getIdentifier();
		identifierLabel->setParent(itemWidget);
		itemWidgetLayout->addWidget(identifierLabel);
		itemWidgetLayout->addStretch();

		// TODO Add icon
		ListedPushButton *removeButton = new ListedPushButton(i, itemWidget);
		removeButton->setText(tr("REMOVE"));
		itemWidgetLayout->addWidget(removeButton);
		QObject::connect(removeButton, SIGNAL(clicked(bool, int)), this, SLOT(buttonRemoveClicked(bool, int)));

		itemWidget->setLayout(itemWidgetLayout);
		setItemWidget(item, 0, itemWidget);

		// Create and set child
		QTreeWidgetItem *childItem = new QTreeWidgetItem(item);
		item->addChild(childItem);
		//childItem->setDisabled(true);
		childItem->setExpanded(false);
		items[i]->setMaximumHeight(items[i]->getHeight());
		setItemWidget(childItem, 0, items[i]);
	}

	if (topLevelItemCount() > 0) {
		topLevelItem(0)->setExpanded(true);
	}
}

void AbstractListView::buttonRemoveClicked(bool checked, int id) {
	emit elementRemoved(id);
}

void AbstractListView::setVideo(FilteredVideo::sptr) {}

void AbstractListView::removeVideo() {}

}  // namespace view