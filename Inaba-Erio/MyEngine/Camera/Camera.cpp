#include "Camera.h"
#include "../Input/directinput.h"
using namespace Inaba;

Camera::Camera():
_right(0,0,0),
_up(0,1,0),
_look(0,0,1000),
_position(0,0,-1000),
_lookAt(0,0,0),
_velocity(0,0,0)
{
	CreateProjectionMatrix(D3DXToRadian(45), 1.3f, 0.001f, 1000.0f);
	Update();
}

void Camera::CreateProjectionMatrix(float fov, float aspect, float nearPlane, float farPlane)
{
	_fov = fov;
	_aspect = aspect;
	_nearPlane = nearPlane;
	_farPlane = farPlane;
	D3DXMatrixPerspectiveFovLH(&_projection, _fov, _aspect, _nearPlane, _farPlane);
}

void Camera::MoveForward(float vel)
{
	_velocity += _look * vel;
}

void Camera::Strafe(float vel)
{
	_velocity += _right * vel;
}

void Camera::MoveUp(float vel)
{
	_velocity.y += vel;
}

void Camera::Yaw(float radians)
{
	if (radians == 0.0f)
	{
		return;
	}
	D3DXMATRIX rotation;
	D3DXMatrixRotationAxis(&rotation, &_up, radians);
	D3DXVec3TransformNormal(&_right, &_right, &rotation);
	D3DXVec3TransformNormal(&_look, &_look, &rotation);
}

void Camera::Pitch(float radians)
{
	if (radians == 0.0f)
	{
		return;
	}

	D3DXMATRIX rotation;
	D3DXMatrixRotationAxis(&rotation, &_right, radians);
	D3DXVec3TransformNormal(&_up, &_up, &rotation);
	D3DXVec3TransformNormal(&_look, &_look, &rotation);
}

void Camera::Roll(float radians)
{
	if (radians == 0.0f)
	{
		return;
	}
	D3DXMATRIX rotation;
	D3DXMatrixRotationAxis(&rotation, &_look, radians);
	D3DXVec3TransformNormal(&_right, &_right, &rotation);
	D3DXVec3TransformNormal(&_up, &_up, &rotation);
}

void Camera::SetPosition(D3DXVECTOR3* pPosition)
{
	_position.x = pPosition->x;
	_position.y = pPosition->y;
	_position.z = pPosition->z;
}

void Camera::SetLookAt(D3DXVECTOR3* pLookAt)
{
	_lookAt.x = pLookAt->x;
	_lookAt.y = pLookAt->y;
	_lookAt.z = pLookAt->z;
	D3DXVec3Normalize(&_look, &(_lookAt - _position));
}

void Camera::Update()
{
	// Move the camera
	_position += _velocity;
	
	// Could decelerate here. I'll just stop completely.
	_velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_lookAt = _position + _look;

	// Calculate the new view matrix
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&_view, &_position, &_lookAt, &up);

	// Set the camera axes from the view matrix
	_right.x = _view._11;
	_right.y = _view._21;
	_right.z = _view._31;
	_up.x = _view._12;
	_up.y = _view._22;
	_up.z = _view._32;
	_look.x = _view._13;
	_look.y = _view._23;
	_look.z = _view._33;
}

void Camera::CameraControl(DirectInput &directInput, float cameraVel)
{
	if (directInput.keyDown(Inaba::Input::KEY_W))
		MoveForward(cameraVel);
	if (directInput.keyDown(Inaba::Input::KEY_S))
		MoveForward(-cameraVel);
	if (directInput.keyDown(Inaba::Input::KEY_A))
		Strafe(-cameraVel);
	if (directInput.keyDown(Inaba::Input::KEY_D))
		Strafe(cameraVel);
	if (directInput.keyDown(Inaba::Input::KEY_Q))
		MoveUp(-cameraVel);
	if (directInput.keyDown(Inaba::Input::KEY_E))
		MoveUp(cameraVel);

	if (directInput.keyDown(Inaba::Input::KEY_LCONTROL))
	{
		Yaw(D3DXToRadian(directInput.mouseRelPosX()));
		Pitch(D3DXToRadian(directInput.mouseRelPosY()));
	}

}