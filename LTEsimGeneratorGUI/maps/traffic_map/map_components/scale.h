#ifndef SCALE_H
#define SCALE_H

//------Template class for scalling between real coordinate system values and
//------arbitrary cartesian coordinate system for displaying purposes
template <typename T1, typename T2>
class Scale
{
private:
    T1 A, B, C, D;
    T1 E, F, G, H;
public:
    Scale(T2 xe0, T2 ye0, T2 ewidth, T2 eheigth, T2 xr0, T1 yr0, T1 rwidth, T1 rheigth);
    T1 getRealX( T2 xe);
    T1 getRealY( T2 ye);
    T2 getDisplayX( T1 xr);
    T2 getDisplayY( T1 yr);
    T2 getDislpayLengthOX( T1 value);
    T2 getDisplayLengthOY( T1 value);
};

//------Scale template creator------
template <typename T1, typename T2>
Scale<T1, T2>::Scale( T2 xe0, T2 ye0, T2 ewidth, T2 eheigth, T2 xr0,
                                     T1 yr0, T1 rwidth, T1 rheigth)
{
    A = (T1) ewidth / rwidth;
    B = (T1) xe0 - A * xr0;
    C = -(T1) eheigth / rheigth;
    D = (T1) ye0 - C * yr0;

    E = rwidth / (T1)ewidth;
    F = xr0 - E * (T1)xe0;
    G = -rheigth / (T1)eheigth;
    H = yr0 - G * (T1)ye0;
}

//------Scaling to the real values------
template <typename T1, typename T2>
T1 Scale<T1, T2>::getRealX(T2 xe)
{
    return E * xe + F;
}

template <typename T1, typename T2>
T1 Scale<T1, T2>::getRealY(T2 ye)
{
    return G * ye + H;
}

//------Scaling from the real values------
template <typename T1, typename T2>
T2 Scale<T1, T2>::getDisplayX(T1 xr)
{
    return (int)(A * xr + B);
}

template <typename T1, typename T2>
T2 Scale<T1, T2>::getDisplayY(T1 yr)
{
    return (int)(C * yr + D);
}

template <typename T1, typename T2>
T2 Scale<T1, T2>::getDislpayLengthOX(T1 xr)
{
    return (int)(A * xr);
}

template <typename T1, typename T2>
T2 Scale<T1, T2>::getDisplayLengthOY(T1 yr)
{
    return (int)(-C * yr);
}
#endif // SCALE_H
