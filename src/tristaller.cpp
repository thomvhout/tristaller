#include "tristaller.h"

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#include <zip.h>

#include "../lib/imgui/imgui.h"

#include "io.h"
#include "zip_utils.h"

using std::string, std::cout, std::endl;

vector<string> mods = {};

namespace tristaller {
    bool show_demo_window = false;

    const char* mouse_cursors_names[] = { "Arrow", "TextInput", "ResizeAll", "ResizeNS", "ResizeEW", "ResizeNESW", "ResizeNWSE", "Hand", "NotAllowed" };

    static const string mc_dir = (string)getenv("HOME") + "/.minecraft/";
    static const string installation_dir = mc_dir + "installations/";
    static const string mod_dir = installation_dir + "/fabric-1.18.1/" + "mods/";

    void initialize() {
        // Populate installed mods list
        for (auto m : grep_dir(mod_dir, "(.*.jar)", false)) {
            mods.push_back(m);
        }
        if (readFile()) {
            cout << "[ERROR]: \tAn error occured while handeling zip file" << endl;
            throw;
        }

        return;
    }

    void renderUI() {
        static int item_current_idx = 0; // Here we store our selection data as an index.

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        ImGui::Begin("Mods");

        if (ImGui::IsItemHovered()) {
            ImGui::SetMouseCursor(2);
        }
        if (ImGui::Button("Show Demo")) {
            show_demo_window = !show_demo_window;
        }
        if (show_demo_window) {
            ImGui::ShowDemoWindow(&show_demo_window);
        }
        /*static bool check = false;
        ImGui::Checkbox("Checkbox", &check);
        */

        //const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };

        //if (ImGui::BeginListBox("listbox 1", ImVec2(1920, 1080)))
        //{
            /*
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
            */

        bool lbSuccess = ImGui::ListBoxHeader("lbMods", ImVec2(viewport->WorkSize.x, viewport->WorkSize.y - 70));
        if (lbSuccess) {
        for (int n = 0; n < mods.size(); n++) {
            string& item = mods[n]; 
            const bool is_selected = (item_current_idx == n);
            if (ImGui::Selectable(item.c_str(), is_selected)) {
                // Handle Selection
                item_current_idx = n;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();
            }
            ImGui::ListBoxFooter();
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
