#ifndef TIMING_H
#define TIMING_H

namespace Frucht {

class FpsLimiter 
{
public:
    FpsLimiter();

    void init(float maxFPS);
    void setMaxFPS(float maxFPS);
    void begin();
    float end(); // Return current FPS

private:
    void calculateFPS();
    
    float m_fps;
    float m_maxFPS;
    float m_frameTime;
    unsigned int m_startTicks;
};

}

#endif // TIMING_H
