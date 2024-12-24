/*
* IGifDebugger.h
* Author: trung.la
* Date: 2024-12-24
* Description: This file contains the IGifDebugger interface.
*/

#ifndef IGIFDEBUGGER_H
#define IGIFDEBUGGER_H

#include <optional>

namespace gif_util {
    struct GifInfo;
};

class IGifDebugger
{
public:
    IGifDebugger();
    virtual ~IGifDebugger();
};

#endif // IGIFDEBUGGER_H
