#ifndef __j1PERFTIMER_H__
#define __j1PERFTIMER_H__



class j1PerfTimer
{
public:

	// Constructor
	j1PerfTimer();

	void Start();
	double ReadMs() const;
	int ReadTicks() const;

private:
	int	started_at;
	static int frequency;
};

#endif //__j1PERFTIMER_H__