
//---------------------------------------------------------------------------
#include "vertexbuffer3D.h"
//---------------------------------------------------------------------------
#include "../Renderer/Renderer.h"
//---------------------------------------------------------------------------
using namespace Inaba;
//---------------------------------------------------------------------------
VertexBuffer3D::VertexBuffer3D (Renderer& rkRenderer, IDirect3DDevice9* pkDevice, size_t uiVertexSize, unsigned int uiFVF)
:
m_uiFVF(uiFVF),
m_uiVertexSize(uiVertexSize),
m_uiVertexCount(0),
m_pkVertexBuffer(NULL),
m_pkDevice(pkDevice),
m_rkRenderer(rkRenderer)
{
	// nothing to do
}
//---------------------------------------------------------------------------
VertexBuffer3D::~VertexBuffer3D ()
{
	if(m_pkVertexBuffer)
	{
		m_pkVertexBuffer->Release();
		m_pkVertexBuffer = NULL;
	}
}
//---------------------------------------------------------------------------
void VertexBuffer3D::setVertexData (const void* pakVertices, size_t uiVertexCount)
{
	// release if previously created
	if(m_pkVertexBuffer)
	{
		m_pkVertexBuffer->Release();
		m_pkVertexBuffer = NULL;
	}

	// create vertex buffer
	HRESULT hr = m_pkDevice->CreateVertexBuffer(
												uiVertexCount * m_uiVertexSize,
												D3DUSAGE_WRITEONLY,
												m_uiFVF,
												D3DPOOL_DEFAULT,
												&m_pkVertexBuffer,
												NULL
	);

	assert(hr == D3D_OK);

	void* pVertices = NULL;

	hr = m_pkVertexBuffer->Lock(0, 0, (void**)(&pVertices), 0);

	memcpy(pVertices, 
		   pakVertices, 
		   uiVertexCount * m_uiVertexSize
	);

	hr = m_pkVertexBuffer->Unlock();

	// update internal state
	m_uiVertexCount = uiVertexCount;

	
}
//---------------------------------------------------------------------------
void VertexBuffer3D::bind ()
{
	// bind the buffer
	HRESULT hr;
	
	hr = m_pkDevice->SetVertexShader(NULL);
	assert(hr == D3D_OK);

	hr = m_pkDevice->SetFVF(m_uiFVF);
	assert(hr == D3D_OK);

	hr = m_pkDevice->SetStreamSource(0, m_pkVertexBuffer, 0, m_uiVertexSize);
	assert(hr == D3D_OK);

	m_rkRenderer.setCurrentVertexBuffer(this);
}
//---------------------------------------------------------------------------
