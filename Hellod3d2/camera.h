#pragma once
#include "MapGenerator.h"
struct camera {
  float camX = MapGenerator::chunk_width / 2;
  float camY = 30.0f;
  float camZ = MapGenerator::chunk_width / 2;

  float cam_rot_h = 0.0f;
  float cam_rot_v = 0.0f;

  float yaw_ = -90.0f;
  float pitch_ = 0.0f;

  DirectX::XMVECTOR camForward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
  DirectX::XMVECTOR camRight = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
  DirectX::XMVECTOR camUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);

  const float speed_ = 0.50f;
  const float sensitivity_ = 0.005f;

  DirectX::XMMATRIX FPSViewMatrix(float pos_x, float pos_y, float pos_z,
                                  float rot_h, float rot_v) {
    DirectX::XMVECTOR DefaultForward =
        DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    DirectX::XMVECTOR DefaultRight =
        DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
    DirectX::XMVECTOR camPosition =
        DirectX::XMVectorSet(pos_x, pos_y, pos_z, 1.0f);

    DirectX::XMMATRIX camRotationMatrix;
    DirectX::XMMATRIX groundWorld;

    camRotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(rot_v, rot_h, 0);
    DirectX::XMVECTOR camTarget =
        DirectX::XMVector3TransformCoord(DefaultForward, camRotationMatrix);
    camTarget = DirectX::XMVector3Normalize(camTarget);

    DirectX::XMMATRIX RotateYTempMatrix;
    RotateYTempMatrix = DirectX::XMMatrixRotationY(rot_h);

    camRight =
        DirectX::XMVector3TransformCoord(DefaultRight, RotateYTempMatrix);
    camUp = XMVector3TransformCoord(camUp, RotateYTempMatrix);
    camForward = XMVector3TransformCoord(DefaultForward, RotateYTempMatrix);

    camTarget = DirectX::XMVectorAdd(camPosition, camTarget);

    return DirectX::XMMatrixLookAtRH(camPosition, camTarget, camUp);
  }

  DirectX::XMMATRIX UpdateCamera(bool left, bool right, bool up, bool down,
                                 bool space, bool ctrl, float mouse_x,
                                 float mouse_y) {


  	static float rot_h = 0.f;
    static float rot_v = 0.f;

    rot_h += -mouse_x * sensitivity_;
    rot_v += mouse_y * sensitivity_;

    if (up) {
      camZ -= speed_ * -cosf(rot_h);
      camX += speed_ * sinf(rot_h);
    }
    if (down) {
      camZ += speed_ * -cosf(rot_h);
      camX -= speed_ * sinf(rot_h);
    }
    if (left) {
      camX -= speed_ * -cosf(rot_h);
      camZ -= speed_ * sinf(rot_h);
    }
    if (right) {
      camX += speed_ * -cosf(rot_h);
      camZ += speed_ * sinf(rot_h);
    }
    if (space) {
      camY += speed_;
    }
    if (ctrl) {
      camY -= speed_;
    }

    DirectX::XMMATRIX view_matrix =
        FPSViewMatrix(camX, camY, camZ, rot_h, rot_v);

    return view_matrix;
  }
};