#pragma once

class Vector;
class QAngle;
class C_BaseEntity;

#include <Windows.h>

#include "GUI.h"
#include "SDK.h"
#include "NccMath.h"
#include "CDrawManager.h"

#include "QAngle.h"


class CRadar
{
protected:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
public:
	float m_flx = 101;
	float m_fly = 101;
	float m_flw = 100;

	bool dragg;
	int m_dragoffsetx, m_dragoffsety;
	void DrawRadarPoint(Vector vOriginX, Vector vOriginY, QAngle qAngle, CBaseEntity * pBaseEntity, Color dwTeamColor);
	void DrawRadarBack();
};
extern CRadar gRadar;