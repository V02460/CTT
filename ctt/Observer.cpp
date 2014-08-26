#include "Observer.h"

#include"NotImplementedException.h"

namespace model {

	using ::exception::NotImplementedException;

Observer::~Observer() {

}

// TODO remove! + = 0 in .h
void Observer::update() {
	throw new NotImplementedException();
}

}  // namespace model