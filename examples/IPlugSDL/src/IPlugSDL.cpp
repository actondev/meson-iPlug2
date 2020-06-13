#include "IPlugSDL.h"
#include "IPlug_include_in_plug_src.h"
#include <SDL2/SDL.h>
#include "swell-internal.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

IPlugSDL::IPlugSDL(const InstanceInfo& info)
  : Plugin(info, MakeConfig(kNumParams, kNumPrograms))
{
  GetParam(kGain)->InitDouble("Gain", 0., 0., 100.0, 0.01, "%");
}

#if IPLUG_DSP
void IPlugSDL::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
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

void* IPlugSDL::OpenWindow(void* pParent)
{
  // shit.. pParent is null ??
  printf("IPlugSDL::OpenWindow window %p\n", pParent);
  
  SDL_Window* window = NULL;
  SDL_Surface* screenSurface = NULL;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    return 1;
  }
  printf("done: sdl init\n");
  // So.. in VST3 the SDL_CreateWindowFrom is ok.. I just(??) need to make the run/draw loop not blocking
  // in APP, SDL_CreateWindowFrom fails with
  // X Error of failed request:  BadWindow (invalid Window parameter)

  HWND hwnd = (HWND) pParent;
  HWND hpar = (HWND) pParent;
  void* ospar;
  while (hpar)
  {
    ospar = hpar->m_oswindow;
    printf("ospar %p\n", ospar);
    printf("hpar %p\n", hpar);
    if (ospar) break;
    hpar = hpar->m_parent;
    printf("hpar 2 %p\n", hpar);
  }

  printf("m_oswindow is %p\n", hwnd->m_oswindow);
  window = SDL_CreateWindowFrom(hwnd);
  // window = SDL_CreateWindow(
  // 			    "hello_sdl2",
  // 			    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
  // 			    SCREEN_WIDTH, SCREEN_HEIGHT,
  // 			    SDL_WINDOW_SHOWN
  // 			    );
  printf("after SDL_CreateWindow...\n");
  if (window == NULL) {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return 1;
  }

  screenSurface = SDL_GetWindowSurface(window);
  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xBA, 0xDA, 0x55));
  SDL_UpdateWindowSurface(window);
  SDL_Delay(2000);
  SDL_DestroyWindow(window);
  SDL_Quit();
  
  return (void *) window;
}
#endif
