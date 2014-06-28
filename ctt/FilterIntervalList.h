#pragma once
class FilterIntervalList
{
public:
	FilterIntervalList();
	~FilterIntervalList();
private:
	List<IntegerInterval> intervals;
public:
	bool isActive(unsigned int frameNumber);
	void activate(IntegerInterval interval);
	void deactivate(IntegerInterval interval);
	List<IntegerInterval> getIntervalList();
};

