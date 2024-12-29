
# GIF Resizer  
## Demonstrated video.
[![Watch the video](https://img.youtube.com/vi/UIbTYUVFbZ4/0.jpg)](https://youtu.be/UIbTYUVFbZ4)

This repository contains a tool for resizing GIFs, built using **giflib** and the **Qt Framework**.  

## Features  
- Resize animated GIFs while maintaining smooth animations.  
- Built with `giflib` for efficient GIF processing.  
- Uses the `Qt Framework` for a modern and intuitive GUI.  

## Prerequisites  

Before building or running the project, ensure you have the following installed:  
- **Qt Framework** (version 5.15 or later)  
- **giflib** (version 5.2.1 or later)  
- A C++ compiler (e.g., GCC, Clang, or MSVC)  
- **CMake** (for build configuration)  

## Installation  

Follow these steps to clone and build the repository:  

### 1. Clone the Repository  
```bash  
git clone https://github.com/<your-username>/<repository-name>.git  
cd <repository-name>
```

### 2. **Install Dependencies**
Download the latest version of Giflib source from: https://sourceforge.net/projects/giflib/files/
Put it on top of the source folder. Like this:
```
GIFResizer/
├── giflib-5.2.2/            # Giflib library source code
├── main.cpp                 # Main application entry point
├── CMakeLists.txt           # CMake build configuration
└── resources/ 
```
