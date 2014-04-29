#include "Renderer.h"

using namespace Inaba;
 
D3DPRIMITIVETYPE primitivesMapping[Inaba::PrimitiveCount] =
{
	D3DPT_TRIANGLELIST, 
	D3DPT_TRIANGLESTRIP,
	D3DPT_POINTLIST,
	D3DPT_LINELIST,     
	D3DPT_LINESTRIP,
	D3DPT_TRIANGLEFAN
};

D3DTRANSFORMSTATETYPE MatrixTypeMapping[MatrixTypeCount] =
{
	D3DTS_VIEW,
	D3DTS_PROJECTION,
	D3DTS_WORLD
};

Renderer::Renderer():
_d3d(NULL),
_d3ddev(NULL),
_vertexbuffer(NULL)
{
}
Renderer::~Renderer()
{
	_d3d->Release();
	_d3d = NULL;
	
	_d3ddev->Release();
	_d3ddev = NULL;
	
	delete _vertexbuffer;
	_vertexbuffer = NULL;
}
bool Renderer::Init(HWND hWnd)
{
	_d3d = Direct3DCreate9(D3D_SDK_VERSION);
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hWnd;

    if(_d3d->CreateDevice(	D3DADAPTER_DEFAULT,
							D3DDEVTYPE_HAL,
							hWnd,
							D3DCREATE_SOFTWARE_VERTEXPROCESSING,
							&d3dpp,
							&_d3ddev) 
	!= D3D_OK)
	{		
		return false;
	}

	_d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);
	_d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//_d3ddev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	D3DVIEWPORT9 viewport;
	_d3ddev->GetViewport(&viewport);

	float viewportWidth = static_cast<float>(viewport.Width);
	float viewportHeight = static_cast<float>(viewport.Height);

	D3DXMATRIX projectionMatrix;
	D3DXMatrixOrthoLH(&projectionMatrix,viewportWidth,viewportHeight, -1.0f, 1.0f);
	_d3ddev->SetTransform(D3DTS_PROJECTION, &projectionMatrix);

	_vertexbuffer = new Inaba::VertexBuffer(_d3ddev,sizeof(Inaba::ColorVertex),Inaba::ColorVertexType);
	
	return true;
}
void Renderer::BeginFrame()
{
	_d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
    _d3ddev->BeginScene();
}
void Renderer::EndFrame()
{
	_vertexbuffer->flush();
	_d3ddev->EndScene();
    _d3ddev->Present(NULL, NULL, NULL, NULL);
}
void Renderer::Draw(ColorVertex* vertex,Inaba::Primitive primitive,size_t vertexCount)
{
	_vertexbuffer->bind();
	_vertexbuffer->draw(vertex,primitivesMapping[primitive], vertexCount);
}
void Renderer::setMatrix(MatrixType matrixType, const Matrix& matrix)
{
	_d3ddev->SetTransform(MatrixTypeMapping[matrixType], matrix);
}