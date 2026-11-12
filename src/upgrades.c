#include "upgrades.h"

void upgrade_fire_rate(double *fire_interval)
{
    if (*fire_interval > FIRE_INTERVAL_MIN)
    {
        *fire_interval *= FIRE_UPGRADE_FACTOR;

        if (*fire_interval < FIRE_INTERVAL_MIN)
        {
            *fire_interval = FIRE_INTERVAL_MIN;
        }
    }
}