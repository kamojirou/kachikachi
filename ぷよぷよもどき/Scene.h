#pragma once
#include <string>

class Scene
{
private:
	std::string m_name;
	std::string m_comment;

public:
	// �V�[���������ăV�[���I�u�W�F�N�g��V�K�쐬���܂��B
	Scene(const char * name) : m_name(name) { }

	// �V�[�������擾���܂��B
	const char * GetSceneName() const { return m_name.c_str(); }

	// �V�[���R�����g��ݒ肵�܂��B
	void SetSceneComment(const char * comment) { m_comment = comment; }

	// �V�[���R�����g���擾���܂��B
	const char * GetSceneComment() const { return m_comment.c_str(); }

public:
	//�V�[���̏�����
	virtual void OnCreate() {}
	virtual void OnStart() {}
	//�V�[���̍X�V
	virtual void OnUpdate(float deltaTime) {}
	//�V�[���̕`��
	virtual void OnRender() {}
	virtual void OnStop() {}
	virtual void OnDestroy() {}
};
