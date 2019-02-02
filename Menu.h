#pragma once

#include <Windows.h>
#include "singleton.h"
#include "GUI.h"

class Menu : public Singleton<Menu>
{
	bool m_isVisible = false;
	bool m_ESPtabVisible = false;
	bool m_AIMtabVisible = false;
	bool m_MISCtabVisible = false;
	bool m_COLtabVisible = false;
	bool m_HVHtabVisible = false;
	CForm MenuForm;
	CForm AIMTabz;
	CForm ESPERTabz;
	CForm MISERCTabz;
	CForm HVHERTabz;
	CForm COLTabz;
	CForm MenuTabz;
public:
	void Init();
	void Kill();

	void PaintTraverse();
	void Click();
	void HandleInput(WPARAM vk);

	void Toggle();

	bool IsVisible() const { return m_isVisible; }
};
