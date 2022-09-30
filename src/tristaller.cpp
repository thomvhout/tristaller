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
// TODO move to seperate utils file
struct bool_wrapper { bool value = false; };
vector<bool_wrapper> checkboxes = {};

static const string last_path_written_in_binary = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

namespace tristaller {
    static bool show_demo_window = false;

    const char* mouse_cursors_names[] = { "Arrow", "TextInput", "ResizeAll", "ResizeNS", "ResizeEW", "ResizeNESW", "ResizeNWSE", "Hand", "NotAllowed" };

    static const string mc_dir = (string)getenv("HOME") + "/.minecraft/";
    static const string installation_dir = mc_dir + "installations/";
    // TODO generate path dynamically
    static const string mod_dir = installation_dir + "/fabric_1.16.5/" + "mods/";

    void initialize() {
        // Populate installed mods list
            // TODO Handle dir not found (empty vector)
        for (auto m : grep_dir(mod_dir, "(.*.jar)", false)) {
            mods.push_back(m);
            bool_wrapper bw = {};
            checkboxes.push_back(bw);
        }

        //TODO read "*.jar/fabric.mod.json"
        if (!readFile("../Chunky-1.2.217.jar")) {
            cout << "[ERROR]: \tAn error occured while handeling zip file" << endl;
            throw;
        }

        return;
    }

    void renderUI() {
        static long unsigned int item_current_idx = 0; // Here we store our selection data as an index.

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);

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

        //                                     ## => Hide label/name
        bool lbSuccess = ImGui::ListBoxHeader("##lbMods", ImVec2(-FLT_MIN, mods.size() * ImGui::GetTextLineHeightWithSpacing()));
        if (lbSuccess) {
        for (long unsigned int n = 0; n < mods.size(); n++) {
            // TODO Cache checkbox name
            string cb_name = "##" + std::to_string(n);
            if (ImGui::Checkbox(cb_name.c_str(), &checkboxes[n].value)) {
                // Handle Selection
            }

            ImGui::SameLine();

            string& item = mods[n]; 
            const bool is_selected = (item_current_idx == n);

            if (ImGui::Selectable(item.c_str(), is_selected)) {
                // Handle Selection
                item_current_idx = n;
                // TODO Display `fabric.mod.properties`
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
