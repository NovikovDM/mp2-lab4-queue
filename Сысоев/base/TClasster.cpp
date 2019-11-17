#include "TClasster.h"
#include <iostream>
#include <ctime>
TClasster::TClasster()
{
	CountGenerationTasks = 0;
	CountFulfilledTask = 0;
	CountUnfulfilledTask = 0;
	CountTaskError = 0;
	LoadProc = 0;
}
void TClasster::StartNewJob(int _size, int _Proc, int _tact, double _ProcIntensity)
{
	Proc = CountFreeProc = _Proc;
	Tact = _tact;
	ProcIntensity = _ProcIntensity;
	masProc = new int[Proc];
	for (int i = 0; i < Proc; i++)
	{
		masProc[i] = 0;
	}
	TQueue<Task> queue(_size);
	ProcessJob(queue);
}

void TClasster::ProcessJob(TQueue<Task> &queue)
{
	for (int i = 0; i < Tact; i++)
	{
		Task Task;
		Task = TaskGeneration();
		if (Task.CntTacts != 0)
		{
			if (!queue.IsFull())
			{
				queue.Push(Task);
			}
			if (queue.IsFull())
			{
				CountTaskError++;
			}
		}
		if (!queue.IsEmpty())
		{
			int CountProc = queue.GetTop().CntProc;
			int CountTact = queue.GetTop().CntTacts;
			int ChangeCountProc = CountProc;
			if ((CountFreeProc >= CountProc))
			{
				for (int i = 0; i < Proc; i++)
				{
					if ((masProc[i] == 0) && (ChangeCountProc > 0))
					{
						masProc[i] = CountTact + 1;
						ChangeCountProc--;
					}
				}
				CountFreeProc -= CountProc;
				queue.Pop();
			}
		}
		for (int i = 0; i < Proc; i++)
		{
			if (masProc[i] > 0)
			{
				masProc[i]--;
				if (masProc[i] == 0)
				{
					CountFreeProc++;
				}
			}
		}
		LoadProc += (Proc - CountFreeProc);
	}
	CountUnfulfilledTask = queue.GetLenght();
}

Task TClasster::TaskGeneration()
{
	Task cl;
	srand((unsigned int)time(NULL));
	double pr = (rand() % 9 + 1) / 10.0;
	if (pr < ProcIntensity)
	{
		srand((unsigned int)time(NULL));
		cl.CntProc = rand() % (Proc)+1;
		cl.CntTacts = rand() % 9 + 1;
		CountGenerationTasks++;
	}
	else
		cl.CntProc = cl.CntTacts = 0;
	return cl;
}

int TClasster::GetGenerationTasks()
{
	return CountGenerationTasks;
}

int TClasster::GetCountCompleteTask()
{
	CountFulfilledTask = CountGenerationTasks - (CountUnfulfilledTask + CountTaskError);
	return CountFulfilledTask;
}

int TClasster::GetCountNotCompleteTask()
{
	return CountUnfulfilledTask;
}

int TClasster::GetCountTaskError()
{
	return CountTaskError;
}

int TClasster::GetAverageLoadProc()
{
	return LoadProc / Tact + 1;
}