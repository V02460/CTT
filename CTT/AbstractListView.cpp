#include "AbstractListView.h"

#include <QTreeWidgetItem>
#include <QBoxLayout>
#include <QLabel>

#include "ListedPushButton.h"

namespace view {
AbstractListView::AbstractListView(QWidget *parent) : QTreeWidget(parent) {
	items = QList<AbstractListViewItem::sptr>();
	setIndentation(0);
	//setItemsExpandable(true);
	setRootIsDecorated(true);
}

void AbstractListView::removeAllItems() {
	while (!items.isEmpty()) {
		QTreeWidgetItem *item = takeTopLevelItem(0);
		delete item;
		items.removeFirst();
	}
}

void AbstractListView::setupUi() {
	for (int i = 0; i < items.size(); i++) {
		//Create and set header
		QTreeWidgetItem *item = new QTreeWidgetItem();
		addTopLevelItem(item);

		QWidget *itemWidget = new QWidget();
		QHBoxLayout *itemWidgetLayout = new QHBoxLayout();

		QLabel *identifierLabel = new QLabel(items.at(i)->getIndentifier());
		itemWidgetLayout->addWidget(identifierLabel);
		itemWidgetLayout->addStretch();

		//TODO Add icon
		ListedPushButton *removeButton = new ListedPushButton(i);
		removeButton->setText(tr("REMOVE"));
		itemWidgetLayout->addWidget(removeButton);
		QObject::connect(removeButton, SIGNAL(clicked(bool, int)), this, SLOT(buttonRemoveClicked(bool, int)));

		itemWidget->setLayout(itemWidgetLayout);
		setItemWidget(item, 0, itemWidget);

		//Create and set child
		QTreeWidgetItem *childItem = new QTreeWidgetItem();
		childItem->setDisabled(true);
		item->addChild(childItem);
		setItemWidget(childItem, 0, items.at(i).data());
	}
}

void AbstractListView::buttonRemoveClicked(bool checked, int id) {
	emit elementRemoved(id);
}
}  // namespace view