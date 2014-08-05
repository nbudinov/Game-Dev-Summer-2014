

class Timer
{
private:
	int StartTicks;
	int PausedTicks;
	bool Paused;
	bool Started;

public:
	Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	Uint32 getTicks();

	bool isStarted();
	bool isPaused();
};