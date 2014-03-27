#ifndef _PtEvent_H_
#define _PtEvent_H_
#include <pthread.h>
typedef struct
{
	pthread_cond_t mCond;
	pthread_mutex_t mMutex;
} CondStructure_t;
class PtEvent
{
	public:
		PtEvent(const int size=1);
		~PtEvent();
		void Set(const int index);
		void SetAll();
		void WaitOnce(const int index);
		void Wait(const int index);
		void WaitAll();
		int WaitAnyOnce();
		int WaitAny();
	private:
		int mSize;
		int mRecv;
		bool *mFlag;
		CondStructure_t mCondHandle;

		void Reset(const int index);
		void ResetAll();
};
#endif
