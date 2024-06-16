#include "PersonalData.h"


PersonalData::PersonalData(int age, const string& name) : age(age), name(name) {
	random_device rd;
	default_random_engine engine(rd());
	uniform_int_distribution<int> generalDistId(10000, 99999);
	this->generalId = generalDistId(rd);
};