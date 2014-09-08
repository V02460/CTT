#ifndef _PLAYERTEST_H
#define _PLAYERTEST_H

#include "Player.h"
#include <QtTest/QtTest>
#include <QObject>
#include <Qtest>

namespace model {
namespace player {

class PlayerTest : public QObject {
	Q_OBJECT

private slots:
	void initTestCase();
	void testDummy();
	void emptyPlayer();
	void playingAndLooping();
	void scrubberOperations();
	void saveRestore();

private:
	QSharedPointer<QOpenGLContext> testContext;

};

}  // namespace player
}  // namespace model

#endif