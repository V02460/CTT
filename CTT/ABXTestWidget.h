#ifndef _ABXTESTWIDGET_H
#define _ABXTESTWIDET_H
#include <qwidget>
#include "ABXController.h"
#include "PlayerFunctions.h"
#include "VideoWidget.h"
#include "Observer.h"
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include "Player.h"
#include "ABXTest.h"

namespace view {
	using ::controller::ABXController;
	class ABXTestWidget :
		public QWidget, public ::model::Observer

	{
	public:
		typedef QScopedPointer<ABXTestWidget> uptr;
		typedef QSharedPointer<ABXTestWidget> sptr;
		typedef QWeakPointer<ABXTestWidget> wptr;

		ABXTestWidget(ABXController::sptr controller, QWidget *parent = 0);
		~ABXTestWidget();
		virtual void update();

	private:
		void setUpUI();

		::model::player::Player::sptr player;
		::model::ABXTest::sptr test;

		ABXController::sptr controller;

		VideoWidget::sptr videoA;
		VideoWidget::sptr videoB;
		VideoWidget::sptr videoX;
		VideoWidget::sptr videoY;

		QSharedPointer<QWidget> videoAContainer;
		QSharedPointer<QWidget> videoBContainer;
		QSharedPointer<QWidget> videoXContainer;
		QSharedPointer<QWidget> videoYContainer;

		QPushButton *resetButton;
		QPushButton *xIsAButton;
		QPushButton *xIsBButton;

		QLabel *triesLabel;
		QLabel *guessingChanceLabel;

		PlayerFunctions *playerFunctions;

		QGridLayout *mainLayout;
		QVBoxLayout *statusLayout;
		QVBoxLayout *controlsLayout;
	};


}

#endif
