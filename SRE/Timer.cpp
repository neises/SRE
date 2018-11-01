#include "Timer.h"
#include <windows.h>

namespace SRE
{
	
	Timer::Timer(): m_dSecondsperCount(0.0), m_dDeltaTime(-1.0), m_BaseTime(0),
		m_PausedTime(0), m_PreviousTime(0), m_CurrentTime(0), m_bStopped(false)
	{
		__int64 countsPerSec;
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
		m_dSecondsperCount = 1.0 / (double)countsPerSec;
	}

	Timer::~Timer()
	{

	}

	void Timer::Reset()
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		m_BaseTime = currTime;
		m_PreviousTime = currTime;
		m_StopTime = 0;
		m_bStopped = false;
	}

	void Timer::Start()
	{
		__int64 startTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&startTime);


		if (m_bStopped)
		{
			m_PausedTime += (startTime - m_StopTime);

			m_PreviousTime = startTime;
			m_StopTime = 0;
			m_bStopped = false;
		}
	}

	void Timer::Stop()
	{
		if (!m_bStopped)
		{
			__int64 currTime;
			QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

			m_StopTime = currTime;
			m_bStopped = true;
		}
	}

	void Timer::Tick()
	{
		if (m_bStopped)
		{
			m_dDeltaTime = 0.0;
			return;
		}

		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		m_CurrentTime = currTime;

		// Time difference between this frame and the previous.
		m_dDeltaTime = (m_CurrentTime - m_PreviousTime)*m_dSecondsperCount;

		// Prepare for next frame.
		m_PreviousTime = m_CurrentTime;

		// Force nonnegative.  The DXSDK's CDXUTTimer mentions that if the 
		// processor goes into a power save mode or we get shuffled to another
		// processor, then mDeltaTime can be negative.
		if (m_dDeltaTime < 0.0)
		{
			m_dDeltaTime = 0.0;
		}
	}

	float Timer::GetTotalTime() const
	{
		if (m_bStopped)
		{
			return (float)(((m_StopTime - m_PausedTime) - m_BaseTime)*m_dSecondsperCount);
		}
		else
		{
			return (float)(((m_CurrentTime - m_PausedTime) - m_BaseTime)*m_dSecondsperCount);
		}
	}

	float Timer::GetDeltaTime() const
	{
		return (float)m_dDeltaTime;
	}

}