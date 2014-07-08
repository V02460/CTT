#ifndef _ILLEGALARGUMENTEXCEPTION_H
#define _ILLEGALARGUMENTEXCEPTION_H

#include <QException>

namespace exception {

    /**
     * Thrown to indicate that a method has been passed an illegal or inappropriate argument.
     */
    class IllegalArgumentException : public QException
    {
    public:
        /**
        * Creates a new IllegalStateException.
        */
        IllegalArgumentException();

        /**
        * Destroys the IllegalStateException.
        */
        ~IllegalArgumentException();
    };

}  // namespace exception

#endif