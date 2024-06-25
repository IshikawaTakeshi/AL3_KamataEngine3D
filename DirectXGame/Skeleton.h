#pragma once
#include "Vector3.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Model.h"

struct Born {
	Vector3 tip; //�{�[���̐�[
	Vector3 root; //�{�[���̍��{
	Vector3 angle; //�{�[���̊p�x
	float length; //�{�[���̒���
};

class Skeleton {
public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection viewProjection);

private:
	
	//�{�[��
	std::vector<Born> born_;
	std::vector<WorldTransform*> joints_; //�֐�
	Model* modelJoint_ = nullptr; //�֐߂̃��f��

};

