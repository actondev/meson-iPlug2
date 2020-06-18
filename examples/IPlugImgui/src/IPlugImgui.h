#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "SDL.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#include "SDL_opengl.h"

const int kNumPrograms = 1;

enum EParams
{
  kGain = 0,
  kNumParams
};

using namespace iplug;

class IPlugImgui : public Plugin
{
private:

public:
  IPlugImgui(const InstanceInfo& info);

#if IPLUG_DSP // All DSP methods and member variables should be within an IPLUG_DSP guard, should you want distributed UI
  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
#endif

#if IPLUG_EDITOR // http://bit.ly/2S64BDd
  SDL_Window* p_window;
  bool m_guiOpen;
  void *pParent;
  static int guiLoop(void* data);
	void* OpenWindow(void* pParent);
        void CloseWindow();
#endif
};
