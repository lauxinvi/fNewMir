#include "..\MirEjTimer.h"

// 类静态变量定义
_int64 MirEjTimer::m_n64Freq = 0;

//-----------------------------------------------------------------------------
// 函数名: MirEjTimer::MirEjTimer()
// 功  能: 构造函数
// 参  数: [void] - 无
// 返回值: [void] - 无
//         失败则抛出EJMSimpleException异常
//-----------------------------------------------------------------------------
MirEjTimer::MirEjTimer(int nPrecision, bool bPlay)
	: m_n64TimeBegin(0)
	, m_n64TimeEnd(0)
	, m_TimerStatus(tsStop)
{
	if (m_n64Freq == 0)
	{
		LARGE_INTEGER tmp;
		QueryPerformanceFrequency(&tmp);
		m_n64Freq = tmp.QuadPart;
	}

	m_nPrecision = nPrecision;

	if (bPlay)
	{
		Play();
	}
}

//-----------------------------------------------------------------------------
// 函数名: MirEjTimer::~MirEjTimer()
// 功  能: 析构函数
// 参  数: [void] - 无
// 返回值: [void] - 无
//-----------------------------------------------------------------------------
MirEjTimer::~MirEjTimer()
{
}

//-----------------------------------------------------------------------------
// 函数名: MirEjTimer::GetTime()
// 功  能: 取当前计时器读数, 该值除以精度则为秒数
// 参  数: [void] - 无
// 返回值: [DWORD] - 若计时器处于运行状态, 则返回开始到当前时刻的计数值
//                   若计时器已停止, 则返回从开始到停止时刻的计数值
//-----------------------------------------------------------------------------
DWORD MirEjTimer::GetTime()
{
	if (m_TimerStatus != tsRun)
	{
		return DWORD((m_n64TimeEnd - m_n64TimeBegin) * m_nPrecision / m_n64Freq);
	}
	else
	{
		return DWORD((GetCurrentCount() - m_n64TimeBegin) * m_nPrecision / m_n64Freq);
	}
}

//-----------------------------------------------------------------------------
// 函数名: MirEjTimer::Play()
// 功  能: 开始计时
// 参  数: [void] - 无
// 返回值: [void] - 无
//-----------------------------------------------------------------------------
void MirEjTimer::Play()
{
	if (m_TimerStatus == tsStop)
	{
		m_n64TimeBegin = GetCurrentCount();
	}
	m_TimerStatus = tsRun;
}

//-----------------------------------------------------------------------------
// 函数名: MirEjTimer::Stop()
// 功  能: 停止计时
// 参  数: [void] - 无
// 返回值: [void] - 无
//-----------------------------------------------------------------------------
void MirEjTimer::Stop()
{
	m_n64TimeEnd = GetCurrentCount();
	m_TimerStatus = tsStop;
}

//-----------------------------------------------------------------------------
// 函数名: MirEjTimer::Pause()
// 功  能: 暂停计时
// 参  数: [void] - 无
// 返回值: [void] - 无
//-----------------------------------------------------------------------------
void MirEjTimer::Pause()
{
	m_n64TimeEnd = GetCurrentCount();
	m_TimerStatus = tsPause;
}

//-----------------------------------------------------------------------------
// 函数名: MirEjTimer::GetCurrentCount()
// 功  能: 取系统计时器的计数值
// 参  数: [void] - 无
// 返回值: [__int64] - 系统计时器的计数值
//-----------------------------------------------------------------------------
__int64 MirEjTimer::GetCurrentCount()
{
	LARGE_INTEGER tmp;
	QueryPerformanceCounter(&tmp);
	return tmp.QuadPart;
}