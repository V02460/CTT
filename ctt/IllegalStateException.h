#ifndef _ILLEGALSTATEEXCEPTION_H
#define _ILLEGALSTATEEXCEPTION_H

#include <QException>

namespace exception {

/**
 * Signals that a method has been invoked at an illegal or inappropriate time.
 */
class IllegalStateException : public QException
{
public:
    /**
     * Creates a new IllegalStateException.
     */
    IllegalStateException();

    /**
     * Destroys the IllegalStateException.
     */
    ~IllegalStateException();
};

}  // namespace exception

#endif