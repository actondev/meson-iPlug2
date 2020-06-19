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

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_Window* dummyWin = SDL_CreateWindow("", 0, 0, 1, 1, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);

	// the creation of window hangs after the first closing & reopening the vst editor

	char sBuf[32];
	sprintf_s<32>(sBuf, "%p", dummyWin);
	printf("Setting hint SDL_HINT_VIDEO_WINDOW_SHARE_PIXEL_FORMAT to %s\n", sBuf);
	SDL_SetHint(SDL_HINT_VIDEO_WINDOW_SHARE_PIXEL_FORMAT, sBuf);

	SDL_Window* window = SDL_CreateWindowFrom(that->pParent);
	SDL_SetHint(SDL_HINT_VIDEO_WINDOW_SHARE_PIXEL_FORMAT, nullptr);

	that->p_window = window;
	

	// SDL_WindowFlags();

	printf("created sdl window\n");

	SDL_GLContext gl_context = SDL_GL_CreateContext(window);
	printf("glcontext %d\n", gl_context);
	SDL_GL_MakeCurrent(window, gl_context);
	SDL_GL_SetSwapInterval(1); // Enable vsync

// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	bool sdlInit = ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
	printf("imgui sdl init 2? %d\n", sdlInit);
	ImGui_ImplOpenGL2_Init();
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	//While application is running
	while (that->m_guiOpen) {


		//Handle events on queue
		while (SDL_PollEvent(&e) != 0) {
			printf("got event!\n");
			ImGui_ImplSDL2_ProcessEvent(&e);
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
		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();
		
		bool show_demo_window = true;
		ImGui::ShowDemoWindow(&show_demo_window);
		ImGui::Render();

		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		//glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(window);

		// SDL_Delay(10);

	}

	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_DestroyWindow(dummyWin);
	SDL_Quit();

	printf("gui closed\n");
	return 0;

}
void IPlugImgui::guiInit()
{


}
void* IPlugImgui::OpenWindow(void *pParent) {
	this->pParent = pParent;
	// shit.. pParent is null ??
	printf("IPlugImgui::OpenWindow window %p\n", pParent);
	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

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
