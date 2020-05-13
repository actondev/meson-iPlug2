#include "AOD_IPlug01.h"
#include "IPlug_include_in_plug_src.h"
#include "IPlugPaths.h"

AOD_IPlug01::AOD_IPlug01(const InstanceInfo& info)
	: Plugin(info, MakeConfig(kNumParams, kNumPrograms))
{
	//GetParam(kGain)->InitDouble("Gain", 0., 0., 100.0, 0.01, "%");

	// setting cwd
	WDL_String path;
	PluginPath(path, gHINSTANCE);

	// something weird about LPCSTR and LPWSTR and char* conversions.. if I call the ..directory(..)
	SetCurrentDirectoryA(path.Get());
}

#if IPLUG_DSP
void AOD_IPlug01::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
	const double gain = GetParam(kGain)->Value() / 100.;
	const int nChans = NOutChansConnected();

	for (int s = 0; s < nFrames; s++) {
		for (int c = 0; c < nChans; c++) {
			outputs[c][s] = inputs[c][s] * gain;
		}
	}
}
#endif

#if IPLUG_EDITOR // http://bit.ly/2S64BDd

void* AOD_IPlug01::OpenWindow(void* pParent)
{
	SetEditorSize(600, 400);
	schemeInit(pParent);
	OnUIOpen();
	return pParent;
}
#endif

void AOD_IPlug01::schemeInit(void* hwnd)
{

}

