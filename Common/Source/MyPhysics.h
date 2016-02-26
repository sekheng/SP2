/******************************************************************************/
/*!
\file       MyPhysics.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief
header file for physics helper function
*/
/******************************************************************************/
#ifndef MY_PHYSICS_H_
#define MY_PHYSICS_H_

/******************************************************************************/
/*!
\brief
Physics namespace
*/
/******************************************************************************/
namespace Physics
{
    //Earth's gravitional force is not this value! and realism sucks
    int earth_gravitational_force = 10;

    /******************************************************************************/
    /*!
    \brief
    decreases the velocity. 
    Do note that time's data type is double

    \param pull - the force or speed
    \param dt - time passes
    \param gravity - the gravity that will affect the the acceleration, but is being default to earth's gravitational force

    \return 
    Affected Speed
    */
    /******************************************************************************/
    template<typename T>
    T gravitational_pulled(T pull_speed, double dt, T gravity = earth_gravitational_force)
    {
        pull_speed = pull_speed - (static_cast<T>(dt * (gravity)));
        return pull_speed;
    }

    /******************************************************************************/
    /*!
    \brief
    Get the acceleration from the force and mass. 
    Do note that the force should be impulse instead of a regular force

    \param force - the force or impulse
    \param mass - mass of the object

    \return
    Acceleration
    */
    /******************************************************************************/
    template<typename T>
    T getAcceleration(T force, T mass)
    {
        return (force / mass);
    }
}


#endif