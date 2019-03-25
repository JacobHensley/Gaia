#pragma once

class GAIA_API TimeStep {
private:
	float m_LastUpdate, m_UpdateTime;
public:
	TimeStep()
		: m_LastUpdate(0.0f), m_UpdateTime(0.0f)
	{
	}

	inline void Update(float time)
	{
		m_LastUpdate = time - m_UpdateTime;
		m_UpdateTime = time;
	}

	inline float GetMills() const { return m_LastUpdate * 1000; }
	inline float GetSeconds() const { return m_LastUpdate; }
};