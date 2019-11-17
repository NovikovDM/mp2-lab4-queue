#ifndef __TClasster_H__
#define __TClasster_H__

#include <string>
#include "TQueue.h"

using namespace std;

struct Task
{
	int CntProc = 0;
	int CntTacts = 0;
};
class TClasster
{
private:
	int Proc;                  //количество процессоров
	int *masProc;              //массив процессоров
	int CountFreeProc;           //количество свободных процессоров
	int CountGenerationTasks;    //количество сгенерированных задач
	int CountFulfilledTask;      //количество выполненных задач
	int CountUnfulfilledTask;    //количество невыполненых задач 
	int CountTaskError;          //количество ошибочных задач (переполнение очереди)
	int LoadProc;              //количество занятых процессоров при каждом такте 
	int Tact;                  //время выполнения задач процессором
	double ProcIntensity;      //интенсивность процессора 
public:
	TClasster();
	void StartNewJob(int _size, int _proc, int _tact, double _ProcIntensity);
	void ProcessJob(TQueue<Task> &queue);
	Task TaskGeneration();
	int GetGenerationTasks();
	int GetCountCompleteTask();
	int GetCountNotCompleteTask();
	int GetCountTaskError();
	int GetAverageLoadProc();
};
#endif