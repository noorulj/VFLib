// Copyright (C) 2008 by Vinnie Falco, this file is part of VFLib.
//
// This file incorporates work covered by the following copyright
// and permission notice:
//
//   Luabridge is copyrighted (C) 2007 by Nathan Reed.
//   All rights reserved.
//
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions are met:
//
//       * Redistributions of source code must retain the above copyright notice,
//         this list of conditions and the following disclaimer.
//       * Redistributions in binary form must reproduce the above copyright
//         notice, this list of conditions and the following disclaimer in the
//         documentation and/or other materials provided with the distribution.
//       * Neither the name of Nathan Reed nor the names of any contributors to
//         this project may be used to endorse or promote products derived from
//         this software without specific prior written permission.
//
//   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
//   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//   POSSIBILITY OF SUCH DAMAGE.
//

#ifndef VF_LUABRIDGE_VFHEADER
#define VF_LUABRIDGE_VFHEADER

#include "AppConfig.h"

#if VF_USE_LUABRIDGE

#if VF_USE_LUA
#include "../vf_lua/vf_lua.h"
#else
#error "vf_luabridge requires vf_lua"
#endif

#include "luabridge/luabridge.hpp"

#endif

#endif
