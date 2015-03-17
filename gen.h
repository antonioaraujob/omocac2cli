#ifndef GEN_H
#define GEN_H

/**
 * @brief Clase que abstrae un gen de un individuo. Incluye: Channel, MinChannelTime, MaxChannelTime, APs.
 */
class Gen
{

private:
    int channel;
    int maxChannelTime;
    int minCHannelTime;
    int APs;

public:
    /**
     * @brief Constructor
     */
    Gen();

    /**
     * @brief Destructor
     */
    ~Gen();

    /**
     * @brief Constructor
     * @param ch canal
     * @param min minCHannelTime
     * @param max maxChannelTime
     * @param aps APs
     */
    Gen(int ch, int min, int max, int aps);

    /**
     * @brief retorna la latencia del gen (minCHannelTime+maxChannelTime)
     * @return retorna la latencia del gen (minCHannelTime+maxChannelTime)
     */
    int getLatency();

    int getValue(int index);

    void setChannel(int c);

    void setMinChannelTime(int min);

    void setMaxChannelTime(int max);

    void setAPs(int aps);


};

#endif // GEN_H
