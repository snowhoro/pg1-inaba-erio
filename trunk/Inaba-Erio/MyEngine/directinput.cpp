
//---------------------------------------------------------------------------
#include "directinput.h"
//---------------------------------------------------------------------------
#include <d3d9.h>
//---------------------------------------------------------------------------
using namespace Inaba;
//---------------------------------------------------------------------------
DirectInput::DirectInput ()
:
m_lpObjectOne(NULL),
m_lpObjectTwo(NULL),
m_lpKeyboard(NULL),
m_lpMouse(NULL)
{
	/***/
}
//---------------------------------------------------------------------------
DirectInput::~DirectInput ()
{
	/***/
}
//---------------------------------------------------------------------------
bool DirectInput::init (HINSTANCE hInstance, HWND hWnd)
{
	POINT kCursorPos;
	GetCursorPos(&kCursorPos);

	m_lMouseScreenAbsPosition[0] = kCursorPos.x;
	m_lMouseScreenAbsPosition[1] = kCursorPos.y;
	m_lMouseScreenAbsPosition[2] = 0;

	// init DirectInput keyboard
	HRESULT hr = DirectInput8Create(
								hInstance, 
								DIRECTINPUT_VERSION, 
								IID_IDirectInput8,
								(void**)&m_lpObjectOne, 
								NULL 
	);

	if(hr != D3D_OK)
	{
		return false;
	}

	// create keyboard device
	hr = m_lpObjectOne->CreateDevice( GUID_SysKeyboard, &m_lpKeyboard, NULL );

	if(hr != D3D_OK)
	{
		return false;
	}

	hr = m_lpKeyboard->SetDataFormat(&c_dfDIKeyboard);

	if(hr != D3D_OK)
	{
		return false;
	}

	hr = m_lpKeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	if(hr != D3D_OK)
	{
		return false;
	}

	m_lpKeyboard->Acquire();		

	// init DirectInput mouse
	hr = DirectInput8Create( 
							hInstance, 
							DIRECTINPUT_VERSION, 
							IID_IDirectInput8,
							(void**)&m_lpObjectTwo,	
							NULL 
							);

	if(hr != D3D_OK)
	{
		return false;
	}

	// create mouse device
	hr = m_lpObjectTwo->CreateDevice(GUID_SysMouse, &m_lpMouse, NULL);

	if(hr != D3D_OK)
	{
		return false;
	}

	hr = m_lpMouse->SetDataFormat(&c_dfDIMouse);

	if(hr != D3D_OK)
	{
		return false;
	}

	hr = m_lpMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	if(hr != D3D_OK)
	{
		return false;
	}

	m_lpMouse->Acquire();

	if(hr != D3D_OK)
	{
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
void DirectInput::deinit ()
{
	  m_lpKeyboard->Unacquire();  // then unacquire it
    m_lpKeyboard->Release();    // and release it
    m_lpKeyboard = NULL;		// and NULL the pointer
	m_lpObjectOne->Release();		// release the DirectInput Object One
    m_lpObjectOne = NULL;			// and NULL the pointer
    
	m_lpMouse->Unacquire();		// then unacquire it
    m_lpMouse->Release();		// and release it
    m_lpMouse = NULL;			// and NULL the pointer
    m_lpObjectTwo->Release();		// release de DirectInput Object Two
    m_lpObjectTwo = NULL;			// and NULL the pointer
}
//---------------------------------------------------------------------------
void DirectInput::reacquire ()
{
	//Para usarlo devuelta
	m_lpMouse->Acquire();
	m_lpKeyboard->Acquire();

	acquire();
}
//---------------------------------------------------------------------------
void DirectInput::unacquire ()
{
	//Releases access to the device.
	ZeroMemory(&m_ucKeyBuffer, sizeof(m_ucKeyBuffer));
	ZeroMemory(&m_kMouseTaken, sizeof(m_kMouseTaken));
	
	m_lpMouse->Unacquire();
	m_lpKeyboard->Unacquire();
}
//---------------------------------------------------------------------------
void DirectInput::acquire ()
{
	//Obtains access to the input device.
	//Me da el estado del teclado
	ZeroMemory( &m_ucKeyBuffer, sizeof(m_ucKeyBuffer) );
	m_lpKeyboard->GetDeviceState( sizeof(m_ucKeyBuffer), &m_ucKeyBuffer );

	// Me da el estado del mouse 
	ZeroMemory( &m_kMouseTaken, sizeof(m_kMouseTaken) );
	m_lpMouse->GetDeviceState( sizeof(m_kMouseTaken), &m_kMouseTaken );

	// updatea la posicion mouse abs 
	m_lMouseScreenAbsPosition[POS_X] += m_kMouseTaken.lX;
	m_lMouseScreenAbsPosition[POS_Y] -= m_kMouseTaken.lY;
	m_lMouseScreenAbsPosition[POS_Z] += m_kMouseTaken.lZ;

	// set mouse rel position
	m_lMouseRelPosition[POS_X] = m_kMouseTaken.lX;
	m_lMouseRelPosition[POS_Y] = m_kMouseTaken.lY;
	m_lMouseRelPosition[POS_Z] = m_kMouseTaken.lZ;

	// update mouse buttons
	m_ucMouseButton[MB_1] = m_kMouseTaken.rgbButtons[MB_1] & 0x80;
	m_ucMouseButton[MB_2] = m_kMouseTaken.rgbButtons[MB_2] & 0x80;
	m_ucMouseButton[MB_3] = m_kMouseTaken.rgbButtons[MB_3] & 0x80;
}
//---------------------------------------------------------------------------
void DirectInput::reset ()
{
	//Resetea todos los estados del buffer de los device
	
	Input::reset();
	
	ZeroMemory( &m_kMouseTaken, sizeof(m_kMouseTaken) );
}
//---------------------------------------------------------------------------
