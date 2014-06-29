#if !defined(_MIXFILTER_H)
#define _MIXFILTER_H

#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {

class MixFilter : public Filter {
public:
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

}  // namespace filter
}  // namespace model

#endif  //_MIXFILTER_H
