#ifndef _CUSTOMTESTINGMACROS_H
#define _CUSTOMTESTINGMACROS_H

#define QEXPECT_EXCEPTION(expression, ExpectedExceptionType)\
try\
{\
	expression; \
	QFAIL("Expected " #ExpectedExceptionType " wasn't thrown!"); \
}\
catch (ExpectedExceptionType* e)\
{\
	qDebug(e->getMsg().toLatin1());\
}\

#endif