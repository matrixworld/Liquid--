/*
 * NSSolver.hh
 *
 *  Created on: 9 Apr 2012
 *      Author: "Dan <DPanth3r> Forest-Barbier"
 */

#ifndef NSSOLVER_HH_
#define NSSOLVER_HH_

class NSSolver
{
public:
    typedef f32 Scalar;

public:
    NSSolver(u32 res, Scalar density, Scalar viscosity, Scalar pressure, Scalar diffusion);
    ~NSSolver();

    void reset();
    void simulateStep(f64 delta);

    u32 getRes() const
    {
        return mRes;
    }

    Scalar getDensity(u32 x, u32 y) const
    {
        return mD[x][y];
    }

    Scalar getU(u32 x, u32 y) const
    {
        return mU[x][y];
    }

    Scalar getV(u32 x, u32 y) const
    {
        return mV[x][y];
    }

    void setDensity(u32 x, u32 y, Scalar value) const
    {
        mD[x][y] = value;
    }

    void setU(u32 x, u32 y, Scalar value) const
    {
        mU[x][y] = value;
    }

    void setV(u32 x, u32 y, Scalar value) const
    {
        mV[x][y] = value;
    }

private:
    Scalar** alloc();
    void free(Scalar** array);
    void fill(Scalar** array, Scalar value = 0);

    void velocityStep();
    void densityStep();

    inline void addSource(Scalar** to, Scalar** src);
    inline Scalar curl(u32 x, u32 y) const;

    void vorticityConfinement();
    void buoyancy();
    void diffuse(Scalar** x, Scalar** oldX, Scalar diffusion);

    void linearSolver(u32 b, Scalar** x, Scalar** x0, Scalar a, Scalar c);
    void setBoundaries(u32 b, Scalar** x);

    void project();
    void advect(u32 b, Scalar** d, Scalar** d0, Scalar** du, Scalar** dv);

    f64 mDelta;
    f64 mTime;

    u32 mRes;
    Scalar mDensity;
    Scalar mViscosity;
    Scalar mPressure;
    Scalar mDiffusion;

    Scalar** mD; //!< Density grid
    Scalar** mOldD; //!< Density grid (previous iteration)

    Scalar** mU; //!< TODO: Comments
    Scalar** mOldU; //!<

    Scalar** mV; //!<
    Scalar** mOldV; //!<

    Scalar** mCurl; //!< Vortex intensity
};

#endif /* NSSOLVER_HH_ */
