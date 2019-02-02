#include "Radar.h"


void CRadar::DrawRadarPoint(Vector vOriginX, Vector vOriginY, QAngle qAngle, CBaseEntity *pBaseEntity, Color dwTeamColor)
{
	CBaseEntity* pLocalEntity = GetBaseEntity(me);

	if (pLocalEntity == NULL)
		return;

	float flDeltaX = vOriginX.x - vOriginY.x;
	float flDeltaY = vOriginX.y - vOriginY.y;

	float flAngle = qAngle.y;

	float flYaw = (flAngle)* (3.14159265358979323846 / 180.0);
	float flMainViewAngles_CosYaw = cos(flYaw);
	float flMainViewAngles_SinYaw = sin(flYaw);

	// rotate
	float x = flDeltaY * (-flMainViewAngles_CosYaw) + flDeltaX * flMainViewAngles_SinYaw;
	float y = flDeltaX * (-flMainViewAngles_CosYaw) - flDeltaY * flMainViewAngles_SinYaw;

	float flRange = 2000;

	if (fabs(x) > flRange || fabs(y) > flRange)
	{
		// clipping
		if (y > x)
		{
			if (y > -x)
			{
				x = flRange * x / y;
				y = flRange;
			}
			else
			{
				y = -flRange * y / x;
				x = -flRange;
			}
		}
		else
		{
			if (y > -x)
			{
				y = flRange * y / x;
				x = flRange;
			}
			else
			{
				x = -flRange * x / y;
				y = -flRange;
			}
		}
	}

	if (gCvars.radartype == 0)
	{

	}
	else if (gCvars.radartype == 1)
	{
		int	iScreenX = gCvars.radar_posx + int(x / flRange * gCvars.radar_width );
		int iScreenY = gCvars.radar_posy + int(y / flRange * gCvars.radar_width );

		gDraw.DrawRect(iScreenX - 3, iScreenY - 3, 7, 7, Color(0, 0, 0, 255));
		gDraw.DrawRect(iScreenX - 2, iScreenY - 2, 5, 5, dwTeamColor);
	}
	else if (gCvars.radartype == 2)
	{
		int	iScreenX = gCvars.radar_posx + int(x / flRange * gCvars.radar_width );
		int iScreenY = gCvars.radar_posy + int(y / flRange * gCvars.radar_width );

		gDraw.DrawRect(iScreenX - 3, iScreenY - 3, 7, 7, Color(0, 0, 0, 255));
		gDraw.DrawRect(iScreenX - 2, iScreenY - 2, 5, 5, dwTeamColor);
	}

	


}
//===================================================================================
void CRadar::DrawRadarBack()
{
	if (gCvars.radarenable && gCvars.esp_active)
	{

		if (dragg && !InputSys::Get().IsKeyDown(VK_LBUTTON))
			dragg = false;

		int cur_x, cur_y;
		gInts.Surface->GetCursorPosition(cur_x, cur_y);

		if (dragg && InputSys::Get().IsKeyDown(VK_LBUTTON) && InputSys::Get().GetKeyState(VK_LBUTTON) != KeyState::Pressed)
		{
			m_x = cur_x - gCvars.radar_posx;
			m_y = cur_y - gCvars.radar_posy;
		}

		int t_x = gCvars.radar_posx;
		int t_y = gCvars.radar_posy;
		Vector2 tl(t_x + m_x, t_y + m_y);
		Vector2 br(tl.x + m_width, tl.y + m_height);


		int lmao1;
		int lmao2;
		//int iCenterX = m_flx;
		//int iCenterY = m_fly;
		int iCenterX = gCvars.radar_posx;
		int iCenterY = gCvars.radar_posy;
		int iSize = gCvars.radar_width;


		int m_iScreenWidth = gScreenSize.iScreenWidth;
		int m_iScreenHeight = gScreenSize.iScreenHeight;

		int x = m_iScreenWidth / 2;
		int y = m_iScreenHeight / 2;

		if (gCvars.radartype == 0)
		{

		}
		else if (gCvars.radartype == 1)
		{
			gDraw.DrawRect(iCenterX - iSize, iCenterY - iSize, 2 * iSize + 2, 2 * iSize + 2, Color(30, 30, 30, 128));
			gDraw.DrawRect(iCenterX, iCenterY - iSize, 1, 2 * iSize, Color::Green());
			gDraw.DrawRect(iCenterX - iSize, iCenterY, 2 * iSize, 1, Color::Green());
			gDraw.DrawRectRadar(iCenterX - iSize, iCenterY - iSize, 2 * iSize + 2, 2 * iSize + 2, Color(0, 255, 0,255));
		}
		else if (gCvars.radartype == 2)
		{
			gDraw.DrawCircleForRadar(iCenterX, iCenterY, iSize + 40, 180, Color::Red());
			gDraw.DrawRect(iCenterX, iCenterY - 40 - iSize , 1, 2 * iSize + 80, Color::Red());
			gDraw.DrawRect(iCenterX - 40 - iSize, iCenterY , 2 * iSize + 80, 1 , Color::Red());
		}	
		
	}
}


CRadar gRadar;