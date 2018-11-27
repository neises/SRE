#pragma once
//Note: this code is mainly from Frank Lunka D3D11 Book
namespace SRE
{
	class Timer
	{
	public:
		Timer();
		~Timer();

		void Reset();
		void Start();
		void Stop();
		void Tick();


		float GetTotalTime() const;
		float GetDeltaTime() const;

	private:
		double	m_dSecondsperCount;
		double	m_dDeltaTime;

		__int64 m_BaseTime;
		__int64 m_PausedTime;
		__int64 m_StopTime;
		__int64 m_PreviousTime;
		__int64 m_CurrentTime;

		bool	m_bStopped;

	};
}

