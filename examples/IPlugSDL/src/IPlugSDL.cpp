#include "IPlugSDL.h"
#include "IPlug_include_in_plug_src.h"
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
  
  SDL_Surface* screenSurface = NULL;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    return 1;
  }
  printf("done: sdl init\n");
  // So.. in VST3 the SDL_CreateWindowFrom is ok.. I just(??) need to make the run/draw loop not blocking
  // in APP, SDL_CreateWindowFrom fails with
  // X Error of failed request:  BadWindow (invalid Window parameter)

  p_window = SDL_CreateWindowFrom(pParent);
  // window = SDL_CreateWindow(
  // 			    "hello_sdl2",
  // 			    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
  // 			    SCREEN_WIDTH, SCREEN_HEIGHT,
  // 			    SDL_WINDOW_SHOWN
  // 			    );
  printf("after SDL_CreateWindow...\n");
  if (p_window == NULL) {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return 1;
  }

  screenSurface = SDL_GetWindowSurface(p_window);
  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xBA, 0xDA, 0x55));
  SDL_UpdateWindowSurface(p_window);
  //  SDL_Delay(2000);
  //  SDL_DestroyWindow(window);
  //  SDL_Quit();
  
  return (void *) p_window;
}

void IPlugSDL::CloseWindow(){
  printf("closing window\n");
  SDL_Surface* screenSurface = SDL_GetWindowSurface(p_window);
  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xBA, 0xDA, 0x55));
  SDL_UpdateWindowSurface(p_window);
   SDL_Delay(2000);
  SDL_DestroyWindow(p_window);
  printf("closed window\n");
  OnUIClose();
}
#endif
