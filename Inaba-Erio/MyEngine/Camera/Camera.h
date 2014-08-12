#ifndef CAMERA_H
#define CAMERA_H

#include "../myengine_api.h"
#include <d3dx9.h>

namespace Inaba
{
	class MYENGINE_API Camera
	{
	public:
		Camera();
		void CreateProjectionMatrix(float fov, float aspect, float nearPlane, float farPlane);
		void MoveForward(float vel);
		void Strafe(float vel);
		void MoveUp(float vel);

		void Update();
		D3DXMATRIX* getViewMatrix()        { return &_view; }
		D3DXMATRIX* getProjectionMatrix()  { return &_projection; }
		void Yaw(float radians);
		void Pitch(float radians);
		/*void Roll(float radians);
		

		void SetPosition(D3DXVECTOR3* pPosition);
		void SetLookAt(D3DXVECTOR3* pLookAt);
		void SetFOV(float fov);
		void SetAspectRatio(float aspect);
		void SetNearPlane(float plane);
		void SetFarPlane(float plane);*/
	private:
		D3DXMATRIX  _view;
		D3DXMATRIX  _projection;

		D3DXVECTOR3 _right;
		D3DXVECTOR3 _up;		// the up direction
		D3DXVECTOR3 _look;		// the look-at position
		D3DXVECTOR3 _position;	// the camera position
		D3DXVECTOR3 _lookAt;  
		D3DXVECTOR3 _velocity; 
		float       _yaw;
		float       _pitch;
		float       _maxPitch;
		float       _maxVelocity;
		float       _fov;
		float       _aspect;
		float       _nearPlane;
		float       _farPlane;
	};
}

#endif