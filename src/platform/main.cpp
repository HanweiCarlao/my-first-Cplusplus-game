#include <iostream>
#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>
#include <gameMain.h>

int main(void) {

#if PRODUCTION_BUILD == 1
	SetTraceLogLevel(LOG_NONE);//disable raylib logs in production build
#endif


	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 450, "window name");
	SetExitKey(KEY_NULL); //Disable Exc from closing window
	SetTargetFPS(240);

#pragma region ImGui setup
	rlImGuiSetup(true);

	ImGuiIO& io = ImGui::GetIO();
	io.FontGlobalScale = 2.5f;//you can make it bigger or smaller if you want
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;//enable docking
	ImGui::StyleColorsClassic();
#pragma endregion
	if (!initGame())
	{
		//std::cerr << "Failed to initialize game!" << std::endl;
		return 0;
	}
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		
#pragma region ImGui new frame
		rlImGuiBegin();


		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);

		if (!updateGame())
		{
			CloseWindow();
		}
#pragma endregion


		


		rlImGuiEnd();
		EndDrawing(); 

	}
	CloseWindow();
	closeGame();
	std::cout << "\n\nGame closed successfully!" << std::endl;
#pragma region ImGui shutdown
	rlImGuiShutdown();
#pragma endregion
	return 0;

}