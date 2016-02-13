#ifndef MY_PHYSICS_H_
#define MY_PHYSICS_H_

/******************************************************************************/
/*!
\brief
Math namespace
*/
/******************************************************************************/
namespace Physics
{
    //Earth's gravitional force is not this value!
    int earth_gravitational_force = 50;

    /******************************************************************************/
    /*!
    \brief
    decreases the acceleration and velocity. 
    Do note that time is double

    \param pull - the force or acceleration
    \param dt - time passes
    */
    /******************************************************************************/
    template<typename T>
    T gravitational_pulled(T pull_speed, double dt, int gravity = earth_gravitational_force)
    {
        pull_speed = pull_speed - (static_cast<T>(dt * (gravity)));
        return pull_speed;
    }

    template<typename T>
    void speed(T& speed, T force, T mass,double dt)
    {
        if (speed * mass < force)
            speed += (T)(force * dt);
    }

    template<typename T>
    T getAcceleration(T force, T mass)
    {
        return (force / mass);
    }
}


#endif