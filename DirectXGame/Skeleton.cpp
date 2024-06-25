#include "Skeleton.h"
#include "MyMath/MyMath.h"
#include "PrimitiveDrawer.h"
#include <numbers>
#include <imgui.h>

void Skeleton::Initialize() {

	//�v�f��
	const uint32_t kNumJointHorizonal = 3;

	//�֐�1���̉���
	const float kJointWidth = 2.0f;
	const float kJointHeight = 2.0f;
	//�v�f����ύX����
	joints_.resize(kNumJointHorizonal);

	//�֐߂̐���
	for (uint32_t row = 0; row < kNumJointHorizonal; row++) {
		joints_[row] = new WorldTransform();
		joints_[row]->Initialize();
		joints_[row]->translation_.x = kJointHeight * row * 6.0f;
		joints_[row]->translation_.y = kJointWidth;
	}

	//born�̗v�f��
	const uint32_t kNumBorn = 2;
	//�v�f����ύX
	born_.resize(kNumBorn);
	//�{�[���̐���
	born_[0] = { {10,0,0}, {0,0,0},{0,0,0},0 };
	born_[0].length = MyMath::Distance(born_[0].tip, born_[0].root);
	born_[1] = { {20,0,0}, born_[0].tip,{0,0,0},0 };
	born_[1].length = MyMath::Distance(born_[1].tip, born_[1].root);

	modelJoint_ = Model::Create();
}

void Skeleton::Update() {

	//�{�[��1�̊p�x�̍X�V
	float born1Numerator = powf(born_[1].tip.x, 2) - powf(born_[1].tip.y, 2)
		+ powf(born_[0].length, 2) - powf(born_[1].length, 2);
	float born1Denominator = 2 * born_[0].length
		* sqrtf(powf(born_[1].tip.x, 2) + powf(born_[1].tip.y, 2));

	//atan�͈̔͂�-PI/2 ~ PI/2�Ȃ̂ŏꍇ�������Čv�Z����
	if (born_[1].tip.x >= 0) {

		born_[0].angle.x = acos(born1Numerator / born1Denominator)
			+ atan(born_[1].tip.y / born_[1].tip.x);

	} else { //x�̒l���}�C�i�X�̎�
		born_[0].angle.x = acos(born1Numerator / born1Denominator)
			+ atan(born_[1].tip.y / born_[1].tip.x) + std::numbers::pi_v<float>;
	}


	//�{�[��1�̍��{�E��[�̍X�V
	born_[0].root.x = 0;
	born_[0].root.y = 0;
	born_[0].tip.x = born_[0].length * cos(born_[0].angle.x);
	born_[0].tip.y = born_[0].length * sin(born_[0].angle.x);

	//�{�[��2�̊p�x�̍X�V
	float born2Numerator = powf(born_[0].length, 2) + powf(born_[1].length, 2)
		- (powf(born_[1].tip.x, 2) + powf(born_[1].tip.y, 2));
	float born2Denominator = 2 * born_[0].length * born_[1].length;
	born_[1].angle.x = std::numbers::pi_v<float> +acos(born2Numerator / born2Denominator);

	//�{�[��2�̍��{�E��[�̍X�V
	born_[1].root.x = born_[0].length * cos(born_[0].angle.x);
	born_[1].root.y = born_[0].length * sin(born_[0].angle.x);
	born_[1].tip.x = born_[1].root.x + born_[1].length * cos(born_[0].angle.x + born_[1].angle.x);
	born_[1].tip.y = born_[1].root.y + born_[1].length * sin(born_[0].angle.x + born_[1].angle.x);

	//�֐߂̍X�V
	joints_[0]->translation_ = { born_[0].root.x,born_[0].root.y,born_[0].root.z };
	joints_[1]->translation_ = { born_[1].root.x,born_[1].root.y,born_[1].root.z };
	joints_[2]->translation_ = { born_[1].tip.x,born_[1].tip.y,born_[1].tip.z };

	joints_[0]->UpdateMatrix();
	joints_[1]->UpdateMatrix();
	joints_[2]->UpdateMatrix();


	//�{�[���̑���
	ImGui::Begin("born_2");

	ImGui::SliderFloat(
		"tipTranslateX",
		&born_[1].tip.x,
		-1.0f * abs(born_[0].length + born_[1].length),
		abs(born_[0].length + born_[1].length),
		"%.3f"
	);
	ImGui::SliderFloat(
		"tipTranslateY",
		&born_[1].tip.y,
		-1.0f * abs(born_[0].length + born_[1].length + 1.0f),
		abs(born_[0].length + born_[1].length - 1.0f),
		"%.3f"
	);
	ImGui::End();

}

void Skeleton::Draw(ViewProjection viewProjection) {

	for (WorldTransform* worldTransformJoint : joints_) {
		modelJoint_->Draw(*worldTransformJoint, viewProjection);
	}

	//���C���`��
	PrimitiveDrawer::GetInstance()->DrawLine3d(born_[0].tip, born_[0].root, { 1.0f,0.0f,0.0f,1.0f });
	PrimitiveDrawer::GetInstance()->DrawLine3d(born_[1].tip, born_[1].root, { 0.0f,1.0f,0.0f,1.0f });
}
