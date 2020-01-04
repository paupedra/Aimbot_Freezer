#ifndef __j1TIMER_H__
#define __j1TIMER_H__



class j1Timer
{
public:

	// Constructor
	j1Timer();

	void Start();
	int Read() const;
	float ReadSec() const;

private:
	int	started_at;
};

#endif //__j1TIMER_H__