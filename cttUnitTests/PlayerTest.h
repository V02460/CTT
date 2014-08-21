#pragma once
#include "..\CTT\Player.h"
#include <QtTest/QtTest>
#include <QObject>
#include <QOffscreenSurface>
#include <Qtest>

using model::player::Player;

class PlayerTest :
	public QObject
{
	Q_OBJECT

	private slots:
	void initTestCase();
	void emptyPlayer();
	void playingAndLooping();
	void scrubberOperations();

private:
	QOffscreenSurface surface;
	QSharedPointer<QOpenGLContext> testContext;

};

