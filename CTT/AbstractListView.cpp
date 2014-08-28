#include "AbstractListView.h"

#include <QTreeWidgetItem>
#include <QBoxLayout>
#include <QLabel>

#include "ListedPushButton.h"

namespace view {

AbstractListView::AbstractListView(QWidget *parent) : items(), QTreeWidget(parent) {
	setIndentation(0);
	//setItemsExpandable(true);
	setRootIsDecorated(true);
}

void AbstractListView::removeAllItems() {
	items.clear();
	clear();
}

void AbstractListView::setupUi() {
	for (int i = 0; i < items.size(); i++) {
		QLabel *identifierLabel = new QLabel(items[i]->getIdentifier(), this);

		ListedPushButton *removeButton = new ListedPushButton(i, this);
		removeButton->setText(tr("REMOVE"));
		QObject::connect(removeButton, SIGNAL(clicked(bool, int)), this, SLOT(buttonRemoveClicked(bool, int)));

		QHBoxLayout *itemWidgetLayout = new QHBoxLayout(this);
		itemWidgetLayout->addStretch();
		itemWidgetLayout->addWidget(identifierLabel);
		itemWidgetLayout->addWidget(removeButton);

		QWidget *itemWidget = new QWidget(this);
		itemWidget->setLayout(itemWidgetLayout);

		QTreeWidgetItem *childItem = new QTreeWidgetItem(this);
		childItem->setDisabled(true);
		setItemWidget(childItem, 0, items[i]);

		QTreeWidgetItem *item = new QTreeWidgetItem(this);
		setItemWidget(item, 0, itemWidget);
		item->addChild(childItem);
		addTopLevelItem(item);
	}
}

void AbstractListView::buttonRemoveClicked(bool checked, int id) {
	emit elementRemoved(id);
}

}  // namespace view