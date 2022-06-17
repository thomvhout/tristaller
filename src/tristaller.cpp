#include "tristaller.h"

#include "../lib/imgui/imgui.h"

#include <iostream>
#include <string>
#include <vector>

#include "io.h"

using namespace std;

vector<string> mod_selection= {};

namespace tristaller {
    bool show_demo_window = false;

    const char* mouse_cursors_names[] = { "Arrow", "TextInput", "ResizeAll", "ResizeNS", "ResizeEW", "ResizeNESW", "ResizeNWSE", "Hand", "NotAllowed" };


    void renderUI() {
        /* const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        */

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        ImGui::Begin("Main Window");

        if (ImGui::IsItemHovered()) {
            ImGui::SetMouseCursor(2);
        }
        if (ImGui::Button("Show Demo")) {
            show_demo_window = !show_demo_window;
        }
        if (show_demo_window) {
            ImGui::ShowDemoWindow(&show_demo_window);
        }
        static bool check = false;
        //ImGui::Checkbox("Checkbox", &check);

        const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };
        static int item_current_idx = 0; // Here we store our selection data as an index.
        if (ImGui::BeginListBox("listbox 1", ImVec2(1920, 1080)))
        {
            ImGui::Checkbox("Checkbox", &check);
            if (ImGui::BeginListBox("listbox 2"))
            {
                ImGui::Checkbox("Child Checkbox", &check);

                if (ImGui::BeginListBox("listbox 3"))
                {
                    ImGui::Checkbox("Child Checkbox", &check);
                    ImGui::EndListBox();
                }

                ImGui::EndListBox();
            }

            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                const bool is_selected = (item_current_idx == n);
                if (ImGui::Selectable(items[n], is_selected))
                    item_current_idx = n;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }

        if (ImGui::Button("List Installed Mods")) {
            string mc_dir = "~/.minecraft/";
            string installation_dir = mc_dir + "installations/fabric-1.18.1/";
            string mod_dir = installation_dir + "mods/";
//            grep_dir(mod_dir, "*.jar");
        }
        if (ImGui::BeginListBox("listbox 1", ImVec2(1920, 1080))) {
            ImGui::EndListBox();
        }

        ImGui::End();
    }

    void getPlatform(){
        #ifdef __linux__
            std::printf("Linux");
        #elif _WIN32
            std::printf("Windows");
        #elif __APPLE__
            std::printf("Mac OS X");
        #else
        #endif

    }
}
