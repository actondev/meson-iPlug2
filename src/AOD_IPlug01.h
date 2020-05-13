#pragma once

#include "IPlug_include_in_plug_hdr.h"

const int kNumPrograms = 1;

enum EParams
{
	kGain = 0,
	kNumParams
};

using namespace iplug;
//using namespace igraphics;

class AOD_IPlug01 final : public Plugin
{
public:
	AOD_IPlug01(const InstanceInfo& info);

#if IPLUG_DSP // http://bit.ly/2S64BDd
	void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
#endif

#if IPLUG_EDITOR // http://bit.ly/2S64BDd
	void* OpenWindow(void* pParent);
#endif

	void schemeInit(void* hwnd);
};
