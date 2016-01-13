// UrlMonAppWindow.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "UrlMonAppWindow.h"
#pragma comment(lib, "urlmon")

#include <urlmon.h>

class UrlMonClient : public IBindStatusCallback
{
public:
	UrlMonClient() : m_cRef(0) 
	{
		m_bindf = BINDF_ASYNCHRONOUS | BINDF_PULLDATA | BINDF_ASYNCSTORAGE;
	}
	virtual ~UrlMonClient() {}

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObj)
	{
		if (!ppvObj)
			return E_INVALIDARG;
		*ppvObj = nullptr;
		if (riid == IID_IUnknown ||
			riid == IID_IBindStatusCallback)
		{
			*ppvObj = (void*)this;
			AddRef();
			return S_OK;
		}

		return E_NOINTERFACE;
	}

	ULONG STDMETHODCALLTYPE AddRef()
	{
		InterlockedIncrement(&m_cRef);
		return m_cRef;
	}

	ULONG STDMETHODCALLTYPE Release()
	{
		ULONG ulRefCount = InterlockedDecrement(&m_cRef);
		if (0 == m_cRef)
		{
			delete this;
		}
		return ulRefCount;
	}


	HRESULT STDMETHODCALLTYPE GetBindInfo(DWORD* orgBINDF, BINDINFO* pbindinfo)
	{
		HRESULT hr = S_OK;
		orgBINDF = (DWORD*)&m_bindf;

		DWORD cbSize = pbindinfo->cbSize;
		memset(pbindinfo, 0, cbSize);
		
		pbindinfo->cbSize = cbSize;
		pbindinfo->szExtraInfo = L"";
		pbindinfo->dwCodePage = CP_UTF8;


		return hr;
	}

	HRESULT STDMETHODCALLTYPE GetPriority(long* pnPriority)
	{
		HRESULT hr = S_OK;
		return hr;
	}

	HRESULT STDMETHODCALLTYPE OnLowResource(DWORD reserved)
	{
		HRESULT hr = S_OK;
		return hr;
	}

	HRESULT STDMETHODCALLTYPE OnObjectAvailable(REFIID riid, IUnknown* punk)
	{
		HRESULT hr = S_OK;
		return hr;
	}


	HRESULT STDMETHODCALLTYPE OnStartBinding(DWORD dwReserved, IBinding* pib)
	{
		HRESULT hr = S_OK;
		return hr;
	}

	HRESULT STDMETHODCALLTYPE OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC* pformatetc, STGMEDIUM* pstgmed)
	{
		HRESULT hr = S_OK;
		return hr;
	}

	HRESULT STDMETHODCALLTYPE OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText)
	{
		HRESULT hr = S_OK;
		return hr;
	}

	HRESULT STDMETHODCALLTYPE OnStopBinding(HRESULT hresult, LPCWSTR szError)
	{
		HRESULT hr = S_OK;
		return hr;
	}


	void StartDownload()
	{
		HRESULT hr = S_OK;
		hr = CreateURLMoniker(NULL, L"http://download.thinkbroadband.com/5MB.zip", &m_urlMoniker);
		if (SUCCEEDED(hr))
		{
			hr = CreateAsyncBindCtx(0, (IBindStatusCallback*)this, NULL, &m_bindCtx);
			if (SUCCEEDED(hr))
			{
				hr = RegisterBindStatusCallback(m_bindCtx, (IBindStatusCallback*)this, 0, 0);
				if (SUCCEEDED(hr))
				{
					IUnknown* pUnknown = 0;
					hr = m_urlMoniker->BindToObject(m_bindCtx, NULL, IID_IUnknown, (void**)&pUnknown);
					if (SUCCEEDED(hr))
					{

					}
				}
			}
		}
	}
private:
	ULONG m_cRef;
	DWORD m_bindf;
	IMoniker* m_urlMoniker;
	IBindCtx* m_bindCtx;
};

static UrlMonClient* g_urlMonClient = 0;

void StartDownloadingFile();


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	CoInitialize(NULL);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_URLMONAPPWINDOW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_URLMONAPPWINDOW));

    MSG msg;

	g_urlMonClient = new UrlMonClient();
	g_urlMonClient->AddRef();

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

	g_urlMonClient->Release();

	CoUninitialize();

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_URLMONAPPWINDOW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_URLMONAPPWINDOW);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
				StartDownloadingFile();
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void StartDownloadingFile()
{
	g_urlMonClient->StartDownload();
}