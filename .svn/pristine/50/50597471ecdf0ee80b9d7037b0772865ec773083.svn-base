#include <ctime> // chrono is C++11 and above
#include "FPSTracker.h"

FPSTracker::FPSTracker()
{
  m_frames = 0;
  m_fps = 0;
  time(&m_time);
}

void FPSTracker::timekeep() {
    time_t newTime;
    time(&newTime);
    // This implementation will return the number of frames processed in the previous second.
    // Ideally, it would return the number of frames processed in the immediate second preceding
    // the call. Implementing this may create greater overhead.
    // TODO: Find an efficient way to count FPS in the last second.
    if (newTime != m_time) {
        m_time = newTime;
        m_fps = m_frames;
        m_frames = 0;
    }
}

void FPSTracker::count()
{
    timekeep();
    m_frames++;
}

double FPSTracker::getFPS()
{
  return m_fps;
}
