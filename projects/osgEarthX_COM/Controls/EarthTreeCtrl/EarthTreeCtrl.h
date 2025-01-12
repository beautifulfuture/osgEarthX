// EarthTreeCtrl.h : CEarthTreeCtrl 的声明
#pragma once
#include "resource.h"       // 主符号
#include <atlctl.h>
#include "osgEarthX_COM_i.h"
#include "_IEarthTreeCtrlEvents_CP.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

using namespace ATL;

#include <Controls/EarthTreeCtrl/EarthTreeView.h>

// CEarthTreeCtrl
class ATL_NO_VTABLE CEarthTreeCtrl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CEarthTreeCtrl, IEarthTreeCtrl>,
	public IPersistStreamInitImpl<CEarthTreeCtrl>,
	public IOleControlImpl<CEarthTreeCtrl>,
	public IOleObjectImpl<CEarthTreeCtrl>,
	public IOleInPlaceActiveObjectImpl<CEarthTreeCtrl>,
	public IViewObjectExImpl<CEarthTreeCtrl>,
	public IOleInPlaceObjectWindowlessImpl<CEarthTreeCtrl>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CEarthTreeCtrl>,
	public CProxy_IEarthTreeCtrlEvents<CEarthTreeCtrl>,
	public IPersistStorageImpl<CEarthTreeCtrl>,
	public ISpecifyPropertyPagesImpl<CEarthTreeCtrl>,
	public IQuickActivateImpl<CEarthTreeCtrl>,
#ifndef _WIN32_WCE
	public IDataObjectImpl<CEarthTreeCtrl>,
#endif
	public IProvideClassInfo2Impl<&CLSID_EarthTreeCtrl, &__uuidof(_IEarthTreeCtrlEvents), &LIBID_osgEarthX_COMLib>,
	public IPropertyNotifySinkCP<CEarthTreeCtrl>,
	public CComCoClass<CEarthTreeCtrl, &CLSID_EarthTreeCtrl>,
	public CComControl<CEarthTreeCtrl>
{
private:
	EarthTreeView m_EarthTreeView;

public:
	STDMETHOD(bindEarthCtrl)(IEarthCtrl* pIEarthCtrl);

public:
	CEarthTreeCtrl()
	{
		m_bWindowOnly = true;
	}

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_INSIDEOUT |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_EARTHTREECTRL)


BEGIN_COM_MAP(CEarthTreeCtrl)
	COM_INTERFACE_ENTRY(IEarthTreeCtrl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
#ifndef _WIN32_WCE
	COM_INTERFACE_ENTRY(IDataObject)
#endif
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROP_MAP(CEarthTreeCtrl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY_TYPE("Appearance", DISPID_APPEARANCE, CLSID_NULL, VT_I2)
	PROP_ENTRY_TYPE("AutoSize", DISPID_AUTOSIZE, CLSID_NULL, VT_BOOL)
#ifndef _WIN32_WCE
	PROP_ENTRY_TYPE("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage, VT_UI4)
#endif
	PROP_ENTRY_TYPE("BackStyle", DISPID_BACKSTYLE, CLSID_NULL, VT_I4)
#ifndef _WIN32_WCE
	PROP_ENTRY_TYPE("BorderColor", DISPID_BORDERCOLOR, CLSID_StockColorPage, VT_UI4)
#endif
	PROP_ENTRY_TYPE("BorderStyle", DISPID_BORDERSTYLE, CLSID_NULL, VT_I4)
	PROP_ENTRY_TYPE("BorderVisible", DISPID_BORDERVISIBLE, CLSID_NULL, VT_BOOL)
	PROP_ENTRY_TYPE("BorderWidth", DISPID_BORDERWIDTH, CLSID_NULL, VT_I4)
	PROP_ENTRY_TYPE("Caption", DISPID_CAPTION, CLSID_NULL, VT_BSTR)
	PROP_ENTRY_TYPE("DrawMode", DISPID_DRAWMODE, CLSID_NULL, VT_I4)
	PROP_ENTRY_TYPE("DrawStyle", DISPID_DRAWSTYLE, CLSID_NULL, VT_I4)
	PROP_ENTRY_TYPE("DrawWidth", DISPID_DRAWWIDTH, CLSID_NULL, VT_I4)
	PROP_ENTRY_TYPE("Enabled", DISPID_ENABLED, CLSID_NULL, VT_BOOL)
#ifndef _WIN32_WCE
	PROP_ENTRY_TYPE("FillColor", DISPID_FILLCOLOR, CLSID_StockColorPage, VT_UI4)
#endif
	PROP_ENTRY_TYPE("FillStyle", DISPID_FILLSTYLE, CLSID_NULL, VT_I4)
#ifndef _WIN32_WCE
	PROP_ENTRY_TYPE("Font", DISPID_FONT, CLSID_StockFontPage, VT_DISPATCH)
#endif
#ifndef _WIN32_WCE
	PROP_ENTRY_TYPE("ForeColor", DISPID_FORECOLOR, CLSID_StockColorPage, VT_UI4)
#endif
#ifndef _WIN32_WCE
	PROP_ENTRY_TYPE("MouseIcon", DISPID_MOUSEICON, CLSID_StockPicturePage, VT_DISPATCH)
#endif
	PROP_ENTRY_TYPE("MousePointer", DISPID_MOUSEPOINTER, CLSID_NULL, VT_I4)
#ifndef _WIN32_WCE
	PROP_ENTRY_TYPE("Picture", DISPID_PICTURE, CLSID_StockPicturePage, VT_DISPATCH)
#endif
	PROP_ENTRY_TYPE("ReadyState", DISPID_READYSTATE, CLSID_NULL, VT_I4)
	PROP_ENTRY_TYPE("TabStop", DISPID_TABSTOP, CLSID_NULL, VT_BOOL)
	PROP_ENTRY_TYPE("Text", DISPID_TEXT, CLSID_NULL, VT_BSTR)
	PROP_ENTRY_TYPE("Valid", DISPID_VALID, CLSID_NULL, VT_BOOL)
	// 示例项
	// PROP_ENTRY_TYPE("属性名", dispid, clsid, vtType)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CEarthTreeCtrl)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(__uuidof(_IEarthTreeCtrlEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CEarthTreeCtrl)
	CHAIN_MSG_MAP(CComControl<CEarthTreeCtrl>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()
// 处理程序原型:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* const arr[] =
		{
			&IID_IEarthTreeCtrl,
		};

		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(0)

// IEarthTreeCtrl
public:
	HRESULT OnDrawAdvanced(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		// 将剪辑区域设置为 di.prcBounds 指定的矩形
		HRGN hRgnOld = NULL;
		if (GetClipRgn(di.hdcDraw, hRgnOld) != 1)
			hRgnOld = NULL;
		bool bSelectOldRgn = false;

		HRGN hRgnNew = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);

		if (hRgnNew != NULL)
		{
			bSelectOldRgn = (SelectClipRgn(di.hdcDraw, hRgnNew) != ERROR);
		}

		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("EarthTreeCtrl");
#ifndef _WIN32_WCE
		TextOut(di.hdcDraw,
			(rc.left + rc.right) / 2,
			(rc.top + rc.bottom) / 2,
			pszText,
			lstrlen(pszText));
#else
		ExtTextOut(di.hdcDraw,
			(rc.left + rc.right) / 2,
			(rc.top + rc.bottom) / 2,
			ETO_OPAQUE,
			NULL,
			pszText,
			ATL::lstrlen(pszText),
			NULL);
#endif

		if (bSelectOldRgn)
			SelectClipRgn(di.hdcDraw, hRgnOld);

		return S_OK;
	}

	void OnAutoSizeChanged()
	{
		ATLTRACE(_T("OnAutoSizeChanged\n"));
	}
	SHORT m_nAppearance;
	void OnAppearanceChanged()
	{
		ATLTRACE(_T("OnAppearanceChanged\n"));
	}
	OLE_COLOR m_clrBackColor;
	void OnBackColorChanged()
	{
		ATLTRACE(_T("OnBackColorChanged\n"));
	}
	LONG m_nBackStyle;
	void OnBackStyleChanged()
	{
		ATLTRACE(_T("OnBackStyleChanged\n"));
	}
	OLE_COLOR m_clrBorderColor;
	void OnBorderColorChanged()
	{
		ATLTRACE(_T("OnBorderColorChanged\n"));
	}
	LONG m_nBorderStyle;
	void OnBorderStyleChanged()
	{
		ATLTRACE(_T("OnBorderStyleChanged\n"));
	}
	BOOL m_bBorderVisible;
	void OnBorderVisibleChanged()
	{
		ATLTRACE(_T("OnBorderVisibleChanged\n"));
	}
	LONG m_nBorderWidth;
	void OnBorderWidthChanged()
	{
		ATLTRACE(_T("OnBorderWidthChanged\n"));
	}
	CComBSTR m_bstrCaption;
	void OnCaptionChanged()
	{
		ATLTRACE(_T("OnCaptionChanged\n"));
	}
	LONG m_nDrawMode;
	void OnDrawModeChanged()
	{
		ATLTRACE(_T("OnDrawModeChanged\n"));
	}
	LONG m_nDrawStyle;
	void OnDrawStyleChanged()
	{
		ATLTRACE(_T("OnDrawStyleChanged\n"));
	}
	LONG m_nDrawWidth;
	void OnDrawWidthChanged()
	{
		ATLTRACE(_T("OnDrawWidthChanged\n"));
	}
	BOOL m_bEnabled;
	void OnEnabledChanged()
	{
		ATLTRACE(_T("OnEnabledChanged\n"));
	}
	OLE_COLOR m_clrFillColor;
	void OnFillColorChanged()
	{
		ATLTRACE(_T("OnFillColorChanged\n"));
	}
	LONG m_nFillStyle;
	void OnFillStyleChanged()
	{
		ATLTRACE(_T("OnFillStyleChanged\n"));
	}
	CComPtr<IFontDisp> m_pFont;
	void OnFontChanged()
	{
		ATLTRACE(_T("OnFontChanged\n"));
	}
	OLE_COLOR m_clrForeColor;
	void OnForeColorChanged()
	{
		ATLTRACE(_T("OnForeColorChanged\n"));
	}
	CComPtr<IPictureDisp> m_pMouseIcon;
	void OnMouseIconChanged()
	{
		ATLTRACE(_T("OnMouseIconChanged\n"));
	}
	LONG m_nMousePointer;
	void OnMousePointerChanged()
	{
		ATLTRACE(_T("OnMousePointerChanged\n"));
	}
	CComPtr<IPictureDisp> m_pPicture;
	void OnPictureChanged()
	{
		ATLTRACE(_T("OnPictureChanged\n"));
	}
	LONG m_nReadyState;
	void OnReadyStateChanged()
	{
		ATLTRACE(_T("OnReadyStateChanged\n"));
	}
	BOOL m_bTabStop;
	void OnTabStopChanged()
	{
		ATLTRACE(_T("OnTabStopChanged\n"));
	}
	CComBSTR m_bstrText;
	void OnTextChanged()
	{
		ATLTRACE(_T("OnTextChanged\n"));
	}
	BOOL m_bValid;
	void OnValidChanged()
	{
		ATLTRACE(_T("OnValidChanged\n"));
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};

OBJECT_ENTRY_AUTO(__uuidof(EarthTreeCtrl), CEarthTreeCtrl)
