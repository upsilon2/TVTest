#ifndef TVTEST_COLOR_SCHEME_OPTIONS_H
#define TVTEST_COLOR_SCHEME_OPTIONS_H


#include "ColorScheme.h"
#include "Options.h"
#include "ColorPalette.h"
#include <memory>


namespace TVTest
{

	class CColorSchemeOptions
		: public COptions
	{
	public:
		class ABSTRACT_CLASS(CEventHandler)
		{
		public:
			virtual bool ApplyColorScheme(const CColorScheme * pColorScheme) = 0;
		};

		CColorSchemeOptions();
		~CColorSchemeOptions();

	// COptions
		bool LoadSettings(CSettings &Settings) override;
		bool SaveSettings(CSettings &Settings) override;

	// CBasicDialog
		bool Create(HWND hwndOwner) override;

	// CColorSchemeOptions
		bool SetEventHandler(CEventHandler *pEventHandler);
		bool ApplyColorScheme() const;
		const CColorScheme *GetColorScheme() const { return m_ColorScheme.get(); }
		COLORREF GetColor(int Type) const;
		COLORREF GetColor(LPCTSTR pszText) const;
		static bool GetThemesDirectory(LPTSTR pszDirectory, int MaxLength, bool fCreate = false);

	private:
		std::unique_ptr<CColorScheme> m_ColorScheme;
		CColorSchemeList m_PresetList;
		CColorScheme::GradientStyle m_GradientList[CColorScheme::NUM_GRADIENTS];
		Theme::BorderType m_BorderList[CColorScheme::NUM_BORDERS];
		std::unique_ptr<CColorScheme> m_PreviewColorScheme;
		bool m_fPreview;
		CEventHandler *m_pEventHandler;
		CColorPalette m_ColorPalette;
		int m_ColorListMargin;

		static const LPCTSTR m_pszExtension;

	// CBasicDialog
		INT_PTR DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) override;

	// CUIBase
		void ApplyStyle() override;
		void RealizeStyle() override;

		bool Apply(const CColorScheme *pColorScheme) const;
		void GetCurrentSettings(CColorScheme *pColorScheme);
		void SetListItemSize();

		static INT_PTR CALLBACK SaveDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};

}	// namespace TVTest


#endif
