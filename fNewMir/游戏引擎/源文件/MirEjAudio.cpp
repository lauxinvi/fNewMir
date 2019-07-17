#include "..\MirEjAudio.h"

MirEjAudio::MirEjAudio()
	:_masterbuffer({ 0 })
	, _masterread(false)
	, _effectread(false)
	, _pmastersource(0)
	, _peffectsource(0)
	, _masterenabled(true)
	, _effectenabled(true)
{
}

MirEjAudio::~MirEjAudio()
{
}

void MirEjAudio::Init()
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);	// COM初始化
	XAudio2Create(&_AudioEJ);//创建声音引擎
	_AudioEJ->CreateMasteringVoice(&_pmastervoice);//创建通道
	_AudioRead = true;
}

void MirEjAudio::SubmitMaster()
{
	CWaveFile _wave;
	_wave.Open(_mastermusic, NULL, WAVEFILE_READ);//读取文件
	_masterpwfx = _wave.GetFormat();//获取文件格式
	DWORD size = _wave.GetSize();//获取文件的大小
	BYTE* _buff = new BYTE[size];//申请内存空间，用于保存数据
	_wave.Read(_buff, size, &size);//读取音频文件
	_AudioEJ->CreateSourceVoice(&_pmastersource, _masterpwfx);//创建背景音声音源
	_masterbuffer.AudioBytes = size;//创建缓存
	_masterbuffer.pAudioData = _buff;
	_masterbuffer.Flags = XAUDIO2_END_OF_STREAM;
	if (_masterloop)
	{
		_masterbuffer.LoopBegin = 0;
		_masterbuffer.LoopCount = XAUDIO2_LOOP_INFINITE;
		_masterbuffer.LoopLength = (UINT32)size / _masterpwfx->nBlockAlign;
		_masterbuffer.PlayBegin = 0;
		_masterbuffer.PlayLength = (UINT32)size / _masterpwfx->nBlockAlign;
	}
	_pmastersource->SubmitSourceBuffer(&_masterbuffer);
}

void MirEjAudio::SubmitEffect()
{
	CWaveFile _wave;
	_wave.Open(_effectmusic, NULL, WAVEFILE_READ);//读取文件
	_effectpwfx = _wave.GetFormat();//获取文件格式
	DWORD size = _wave.GetSize();//获取文件的大小
	BYTE* _buff = new BYTE[size];//申请内存空间，用于保存数据
	_wave.Read(_buff, size, &size);//读取音频文件
	_AudioEJ->CreateSourceVoice(&_peffectsource, _effectpwfx);//创建效果音声音源
	_effectbuffer.AudioBytes = size;//创建缓存
	_effectbuffer.pAudioData = _buff;
	_effectbuffer.Flags = XAUDIO2_END_OF_STREAM;
	if (_effectloop)
	{
		_effectbuffer.LoopBegin = 0;
		_effectbuffer.LoopCount = XAUDIO2_LOOP_INFINITE;
		_effectbuffer.LoopLength = (UINT32)size / _effectpwfx->nBlockAlign;
		_effectbuffer.PlayBegin = 0;
		_effectbuffer.PlayLength = (UINT32)size / _effectpwfx->nBlockAlign;
	}
	_peffectsource->SubmitSourceBuffer(&_effectbuffer);
}

void MirEjAudio::SendWav(LPWSTR s, bool t, bool b)
{
	if (t)
	{
		if (_pmastersource != NULL)
		{
			_pmastersource->GetState(&_masterstate);
			if (_masterstate.BuffersQueued > 0)
			{
				_pmastersource->Stop(0);
				_pmastersource->FlushSourceBuffers();
			}
		}
		_mastermusic = s;
		_masterloop = b;
		SubmitMaster();
		_masterread = true;
	}
	else
	{
		if (_peffectsource != NULL)
		{
			_peffectsource->GetState(&_effectstate);
			if (_effectstate.BuffersQueued > 0)
			{
				_peffectsource->Stop(0);
				_peffectsource->FlushSourceBuffers();
			}
		}
		_effectmusic = s;
		_effectloop = b;
		SubmitEffect();
		_effectread = true;
	}
}

void MirEjAudio::Update()
{
	if (_AudioRead)
	{
		if (_masterread)
		{
			_masterread = false;
			_pmastersource->Start(0);
		}
		if (_effectread)
		{
			_effectread = false;
			_peffectsource->Start(0);
		}
	}
}

void MirEjAudio::SubmitVolume()
{
	if (_pmastersource != NULL)
	{
		if (_masterenabled)
		{
			_pmastersource->SetVolume(1);
		}
		else
		{
			_pmastersource->SetVolume(0);
		}
	}
	if (_peffectsource != NULL)
	{
		if (_effectenabled)
		{
			_peffectsource->SetVolume(1);
		}
		else
		{
			_peffectsource->SetVolume(0);
		}
	}
	_AudioEJ->CommitChanges(XAUDIO2_COMMIT_ALL);
}

void MirEjAudio::Release()
{

}