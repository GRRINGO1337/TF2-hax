#pragma once

#include "SDK.h"

struct DrawModelState_t;
struct ModelRenderInfo_t;
typedef float matrix3x4[3][4];

typedef void(__thiscall *DrawModelExecuteFn)(CModelRender*, const DrawModelState_t&, const ModelRenderInfo_t&, matrix3x4*);

void __fastcall Hooked_FrameStageNotify(void* _this, void* _edx, ClientFrameStage_t stage);
bool __fastcall Hooked_CreateMove(PVOID ClientMode, int edx, float input_sample_frametime, CUserCmd* pCommand);
int __fastcall Hooked_KeyEvent(PVOID CHLClient, int edx, int eventcode, int keynum, const char *currentBinding);
