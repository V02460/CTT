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

void AbstractListView::setupUi(QList<AbstractListViewItem*> newItems) {
	for (int i = 0; i < std::min(items.length(), newItems.length());) {
		if (!items[i]->equals(newItems[i])) {
			QTreeWidgetItem *item = takeTopLevelItem(i);
			QList<QTreeWidgetItem*> children = item->takeChildren();
			delete items.takeAt(i);
			while (!children.isEmpty()) {
				delete itemWidget(children.first(), 0);
				delete children.takeFirst();
			}
			delete itemWidget(item, 0);
			delete item;
			removeButtonList.removeAt(i);
		} else {
			removeButtonList[i]->setIndex(i++);
		}
	}
	while (items.length() > newItems.length()) {
		QTreeWidgetItem *item = takeTopLevelItem(newItems.length());
		delete itemWidget(item, 0);
		QList<QTreeWidgetItem*> children = item->takeChildren();
		while (!children.isEmpty()) {
			delete itemWidget(children.first(), 0);
			delete children.takeFirst();
		}
		items.removeAt(newItems.length());
		removeButtonList.removeAt(newItems.length());
	}
	while (items.length() < newItems.length()) {
		int index = items.length();
		items.insert(index, newItems[index]);

		QTreeWidgetItem *item = new QTreeWidgetItem(this);
		item->setExpanded(true);
		insertTopLevelItem(index, item);

		QWidget *itemWidget = new QWidget(this);
		QHBoxLayout *itemWidgetLayout = new QHBoxLayout(this);

		QLabel *identifierLabel = items[index]->getIdentifier();
		identifierLabel->setParent(itemWidget);
		itemWidgetLayout->addWidget(identifierLabel);
		itemWidgetLayout->addStretch();

		// TODO Add icon
		ListedPushButton::sptr removeButton(new ListedPushButton(index));
		removeButton->setText(tr("REMOVE"));
		itemWidgetLayout->addWidget(removeButton.data());
		QObject::connect(removeButton.data(), SIGNAL(clicked(bool, int)), this, SLOT(buttonRemoveClicked(bool, int)));
		removeButtonList.insert(index, removeButton);

		itemWidget->setLayout(itemWidgetLayout);
		setItemWidget(item, 0, itemWidget);

		// Create and set child
		QTreeWidgetItem *childItem = new QTreeWidgetItem(item);
		item->addChild(childItem);
		//childItem->setDisabled(true);
		//childItem->setExpanded(true);
		items[index]->setMaximumHeight(items[index]->getHeight());
		setItemWidget(childItem, 0, items[index]);
	}

	for (int i = 0; i < newItems.length(); i++) {
		if (items[i] != newItems[i]) {
			delete newItems[i];
		}
	}

	newItems.clear();
}

/*
void AbstractListView::setupUi() {
	for (int i = 0; i < items.size(); i++) {
		// Create and set header
		QTreeWidgetItem *item = new QTreeWidgetItem(this);
		item->setExpanded(true);
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
		//childItem->setExpanded(true);
		items[i]->setMaximumHeight(items[i]->getHeight());
		setItemWidget(childItem, 0, items[i]);
	}

	/*if (topLevelItemCount() > 0) {
		topLevelItem(0)->setExpanded(true);
	}* /
}
*/

void AbstractListView::buttonRemoveClicked(bool checked, int id) {
	emit elementRemoved(id);
}

void AbstractListView::setVideo(FilteredVideo::sptr) {}

void AbstractListView::removeVideo() {}

}  // namespace view