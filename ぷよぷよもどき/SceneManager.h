#pragma once
#include <string>
#include <unordered_map>

// �O���錾
class Scene;

class SceneManager
{
private:
	static SceneManager * s_instance;
	std::unordered_map<std::string, Scene *> m_scenes;
	Scene * m_currScene;
	Scene * m_nextScene;

private:
	SceneManager();
	~SceneManager() = default;
	SceneManager(const SceneManager &) = delete;
	SceneManager(SceneManager &&) = delete;
	void operator =(const SceneManager &) = delete;
	void operator =(SceneManager &&) = delete;

public:
	static void Startup();
	static void Shutdown();
	static SceneManager * GetInstance();

	// �V�[����o�^���܂��B
	void RegisterScene(Scene * scene);

	//�ŏ��̃V�[�����N������֐�
	void RunFirstScene(const char * sceneName);

	//���̃V�[����\�񂷂�֐�
	void ReserveNextScene(const char * sceneName);

	//�V�[����J�ڂ���֐�
	void TransitScene();

	//���݂̃V�[����`�悷��֐�
	void RenderCurrentScene();

	//���݂̃V�[�����X�V����֐�
	void UpdateCurrentScene(float deltaTime);

private:
	// �V�[�������w�肵�ăV�[���I�u�W�F�N�g���������܂��B
	Scene * GetSceneByName(const char * sceneName) const;
};