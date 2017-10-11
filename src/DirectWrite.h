#ifndef TVTEST_DIRECTWRITE_H
#define TVTEST_DIRECTWRITE_H


#include <d2d1.h>
#include <dwrite.h>


namespace TVTest
{

	class CDirectWriteSystem
	{
	public:
		CDirectWriteSystem();
		~CDirectWriteSystem();

		bool Initialize();
		void Finalize();
		bool IsInitialized() const;
		ID2D1Factory *GetD2DFactory();
		IDWriteFactory *GetDWriteFactory();

	private:
		HMODULE m_hD2DLib;
		HMODULE m_hDWriteLib;
		ID2D1Factory *m_pD2DFactory;
		IDWriteFactory *m_pDWriteFactory;
	};

	class CDirectWriteRenderer;

	class CDirectWriteResource
	{
	public:
		virtual ~CDirectWriteResource() = default;

		virtual void Destroy() = 0;
		virtual bool IsCreated() const = 0;
	};

	class CDirectWriteFont
		: public CDirectWriteResource
	{
	public:
		CDirectWriteFont();
		~CDirectWriteFont();

		bool Create(CDirectWriteRenderer &Renderer, const LOGFONT &lf);
		void Destroy() override;
		bool IsCreated() const override;
		IDWriteTextFormat *GetTextFormat();
		bool GetLogFont(LOGFONT *pLogFont) const;

	private:
		IDWriteTextFormat *m_pTextFormat;
		LOGFONT m_LogFont;
	};

	class CDirectWriteBrush
		: public CDirectWriteResource
	{
	public:
		CDirectWriteBrush();
		~CDirectWriteBrush();

		bool Create(CDirectWriteRenderer &Renderer, BYTE Red, BYTE Green, BYTE Blue, BYTE Alpha = 255);
		void Destroy() override;
		bool IsCreated() const override;
		bool SetColor(BYTE Red, BYTE Green, BYTE Blue, BYTE Alpha = 255);
		ID2D1Brush *GetBrush();

	private:
		ID2D1SolidColorBrush *m_pBrush;
	};

	class CDirectWriteRenderer
	{
	public:
		struct RenderingParams
		{
			enum class ParamFlag : unsigned int {
				None             = 0x0000U,
				Gamma            = 0x0001U,
				EnhancedContrast = 0x0002U,
				ClearTypeLevel   = 0x0004U,
				PixelGeometry    = 0x0008U,
				RenderingMode    = 0x0010U,
			};

			ParamFlag Mask;
			float Gamma;
			float EnhancedContrast;
			float ClearTypeLevel;
			DWRITE_PIXEL_GEOMETRY PixelGeometry;
			DWRITE_RENDERING_MODE RenderingMode;

			RenderingParams() : Mask(ParamFlag::None) {}
		};

		struct FontMetrics
		{
			float Ascent;
			float Descent;
			float LineGap;
		};

		struct TextMetrics
		{
			float Width;
			float WidthIncludingTrailingWhitespace;
			float Height;
		};

		enum class DrawTextFlag : unsigned int {
			None             = 0x0000U,
			Align_HorzCenter = 0x0001U,
			Align_Right      = 0x0002U,
			Align_Justified  = 0x0004U,
			Align_VertCenter = 0x0008U,
			Align_Bottom     = 0x0010U,
		};

		CDirectWriteRenderer(CDirectWriteSystem &System);
		~CDirectWriteRenderer();

		bool Initialize(HWND hwnd);
		void Finalize();
		bool IsInitialized() const;
		CDirectWriteSystem &GetSystem() { return m_System; }
		ID2D1RenderTarget *GetRenderTarget();
		bool BeginDraw(HDC hdc, const RECT &Rect);
		bool EndDraw();
		bool BindDC(HDC hdc, const RECT &Rect);
		HDC GetDC() const { return m_hdc; }
		bool Clear(BYTE Red, BYTE Green, BYTE Blue, BYTE Alpha = 255);
		bool SetClippingRect(const RECT &Rect);
		bool ResetClipping();
		bool SetRenderingParams(const RenderingParams &Params);
		bool OnWindowPosChanged();
		bool DrawText(
			LPCWSTR pText, int Length, const RECT &Rect,
			CDirectWriteFont &Font, CDirectWriteBrush &Brush, DrawTextFlag Flags = DrawTextFlag::None);
		int GetFitCharCount(LPCWSTR pText, int Length, int Width, CDirectWriteFont &Font);
		bool IsNeedRecreate() const { return m_fNeedRecreate; }
		bool GetFontMetrics(CDirectWriteFont &Font, FontMetrics *pMetrics);
		bool GetTextMetrics(LPCWSTR pText, int Length, CDirectWriteFont &Font, TextMetrics *pMetrics);

	private:
		bool UpdateRenderingParams();

		CDirectWriteSystem &m_System;
		ID2D1DCRenderTarget *m_pRenderTarget;
		HWND m_hwnd;
		HDC m_hdc;
		HMONITOR m_hMonitor;
		RenderingParams m_RenderingParams;
		bool m_fNeedRecreate;
	};

	TVTEST_ENUM_FLAGS(CDirectWriteRenderer::DrawTextFlag)
	TVTEST_ENUM_FLAGS(CDirectWriteRenderer::RenderingParams::ParamFlag)

}	// namespace TVTest


#endif
