// UrlMonApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <urlmon.h>

class UrlMonClient : public IBindStatusCallback
{
public:
	UrlMonClient() : m_cRef(0){}
	virtual ~UrlMonClient(){}

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

	}
private:
	ULONG m_cRef;
};


int main()
{
	UrlMonClient* urlmonClient = new UrlMonClient();
	urlmonClient->StartDownload();

    return 0;
}

