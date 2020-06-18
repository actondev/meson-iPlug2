#include "IPlugImgui.h"
#include "IPlug_include_in_plug_src.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

IPlugImgui::IPlugImgui(const InstanceInfo &info) :
		Plugin(info, MakeConfig(kNumParams, kNumPrograms)) {
	GetParam(kGain)->InitDouble("Gain", 0., 0., 100.0, 0.01, "%");
	m_guiOpen = false;
}

#if IPLUG_DSP
void IPlugImgui::ProcessBlock(sample **inputs, sample **outputs, int nFrames) {
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
int IPlugImgui::guiLoop(void *pointer) {
	IPlugImgui *that = (IPlugImgui*) pointer;
	printf("gui loop\n");

	//Event handler
	SDL_Event e;

	printf("gui loop window %p\n", that->pParent);

	// the creation of window hangs after the first closing & reopening the vst editor
	that->p_window = SDL_CreateWindowFrom(that->pParent);
	printf("created sdl window\n");

	// that->p_window->flags |= SDL_WINDOW_OPENGL;
	SDL_Renderer *renderer = NULL;
//	renderer = SDL_GetRenderer(that->p_window);
//	printf("got window from renderer? %p", renderer);
	renderer = SDL_CreateRenderer(that->p_window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	printf("with renderer %p\n", renderer);

	//While application is running
	while (that->m_guiOpen) {
		printf("gui loop: drawing\n");
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0) {
			printf("got event\n");
			//User requests quit
			switch (e.type) {
			case SDL_QUIT:
				printf("SDL_QUIT ?? I don't think I'd ever get this");
				break;
			case SDL_MOUSEBUTTONDOWN:
				printf("mouse button down!\n");
				break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);

		SDL_RenderClear(renderer);

		SDL_Rect fillRect = { 20, 20, 100, 100 };
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(renderer, &fillRect);

		SDL_RenderPresent(renderer);

//		SDL_Surface *screenSurface = SDL_GetWindowSurface(that->p_window);
//		SDL_FillRect(screenSurface, NULL,
//				SDL_MapRGB(screenSurface->format, 0xBA, 0xDA, 0x55));
//		SDL_UpdateWindowSurface(that->p_window);
		SDL_Delay(100);

	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(that->p_window);
	printf("gui closed\n");
	return 0;

}
void* IPlugImgui::OpenWindow(void *pParent) {
	this->pParent = pParent;
	// shit.. pParent is null ??
	printf("IPlugImgui::OpenWindow window %p\n", pParent);
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
		return NULL;
	}
	printf("done: sdl init\n");

	m_guiOpen = true;
	SDL_CreateThread(guiLoop, "GuiThread", this);

	printf("after create thread...\n");

	// no need to return p_window, returning pParent works just fine
	return (void*) pParent;
}

void IPlugImgui::CloseWindow() {
	printf("closing window\n");
	m_guiOpen = false;
	printf("closed window\n");
	OnUIClose();
}
#endif
