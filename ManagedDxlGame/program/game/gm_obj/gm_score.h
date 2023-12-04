#pragma once


class Score {
public:
	Score();
	~Score();
	void update(float delta_time);
	void draw();

	void set_score1_judge(bool b) { score1_judge = b; }
	void set_score2_judge(bool b) { score2_judge = b; }
	void set_score3_judge(bool b) { score3_judge = b; }
	void set_score4_judge(bool b) { score4_judge = b; }
	void set_score5_judge(bool b) { score5_judge = b; }
	void set_sort_(int a) { enemy_sort_s = a; }
	int get_scorepoint() { return _scorepoint; }
	int _scorepoint = 0;
	int enemy_sort_s = 0;
private:
	bool score1_judge = false;
	bool score2_judge = false;
	bool score3_judge = false;
	bool score4_judge = false;
	bool score5_judge = false;
	tnl::Vector3 score_pos = { 1040,30,0 };
};