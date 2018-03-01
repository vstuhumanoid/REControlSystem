#pragma once

/*
* Коэффициенты ПИД регулятора
*/
class PIDGates
{
public:
	int PGate; // пропорциональный
	int IGate; // интергральный
	int KGate; // дифференциальный

	PIDGates();
	~PIDGates();
};

