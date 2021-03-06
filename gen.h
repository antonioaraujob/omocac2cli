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

    /**
     * @brief getValue
     * @param index
     * @return
     */
    int getValue(int index);

    /**
     * @brief asigna el valor del canal del gen
     * @param c canal a asignar
     */
    void setChannel(int c);

    /**
     * @brief asigna el valor de minCHannelTime del gen
     * @param min minCHannelTime a asignar
     */
    void setMinChannelTime(int min);

    /**
     * @brief asigna el valor de maxChannelTime del gen
     * @param max maxChannelTime a asignar
     */
    void setMaxChannelTime(int max);

    /**
     * @brief asigna el valor de APs del gen
     * @param aps APs a asignar
     */
    void setAPs(int aps);


};

#endif // GEN_H
