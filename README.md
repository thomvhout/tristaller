# Tristaller
Tristaller is a Minecraft mod manager for clients and servers running on Linux and Windows. The goal is to easily install modded profiles and keep these updated by simply dropping a "modpack_update.zip" on the portable executable.

What sets Tristaller apart from other projects is that no 3rd party game launchers are required. No installation into the system is required (only a single executable). Lastly the regular buildsystem for IMGUI with Vulkan backend utilizes CMake, this has been stripped out and replaced by a good ol' Makefile.

# Building from Source
---
Note: At the moment this project can only be built on Linux.
---
`$ git clone https://github.com/thomvhout/tristaller --recurse-submodules`   Clone the Tristaller repository

Install the [Vulkan SDK](https://www.vulkan.org/tools#download-these-essential-development-tools)

Edit the Vulkan SDK path in the Makefile to your install location.

# TODO
## Build
- [ ] Makefile: Dynamic `VULKAN_SDK_PATH` in Windows
- [ ] Port Build for Windows: Potentially use `imgui/examples/example_glfw_opengl3/build_win32.bat`
- [ ] Clear object files from src/
## UI
- [X] Use ImGui `modals` as popup window for install process
## Misc
- [ ] Portability: Write used paths into executable itself
- [ ] Zip support: https://bitbucket.org/wbenny/ziplib/wiki/Home (built around streams)
- [ ] CLI support
- [ ] Implement path handling for each platform
