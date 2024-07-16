#pragma once
#include "../../library/tnl_sequence.h"

class SceneBase;

class GameManager {
public:
    //static GameManager* GetInstance(SceneBase* start_scene = nullptr);
    static Shared<GameManager> GetInstance(Shared<SceneBase> start_scene = nullptr);
    static void Destroy();

    //void changeScene(SceneBase* next_scene, float trans_time = 0.5f);
    void changeScene(Shared<SceneBase> next_scene, float trans_time = 0.5f);

    void update(float delta_time);

  // inline SceneBase* getSceneInstance() { return now_scene_; }
    inline Shared<SceneBase> getSceneInstance() { return now_scene_; }
    inline bool getTransitionFlg() { return isTransitioning_; }

    int score_ = 0;

private:
    //GameManager(SceneBase* start_scene);
    GameManager(Shared<SceneBase> start_scene);
    float trans_time_ = 0.5f;
    //SceneBase* now_scene_ = nullptr;
    //SceneBase* next_scene_ = nullptr;
    Shared<SceneBase> now_scene_ = nullptr;
    Shared<SceneBase> next_scene_ = nullptr;
    int tansition_graph_hdl_ = 0;

    //SceneResult* result_ = nullptr;

    int highscore_ = 0;

    tnl::Sequence<GameManager> sequence_ = tnl::Sequence<GameManager>(this, &GameManager::seqRunScene);
    bool isTransitioning_ = false;  // ‘JˆÚ’†ƒtƒ‰ƒO

    bool seqTransIn(const float delta_time);
    bool seqTransOut(const float delta_time);
    bool seqRunScene(const float delta_time);
};