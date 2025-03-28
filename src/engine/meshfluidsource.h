/*
MIT License

Copyright (C) 2025 Ryan L. Guy & Dennis Fassbaender

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef FLUIDENGINE_MESHFLUIDSOURCE_H
#define FLUIDENGINE_MESHFLUIDSOURCE_H

#include "meshobject.h"
#include "macvelocityfield.h"

struct VelocityFieldData {
        MACVelocityField vfield;
        vmath::vec3 offset;
        GridIndex gridOffset;
    };

class MeshFluidSource
{
public:
    MeshFluidSource();
    MeshFluidSource(int i, int j, int k, double dx);
    ~MeshFluidSource();

    bool operator < (const MeshFluidSource& other) const {
        return (_meshObject._priority < other._meshObject._priority);
    }

    bool operator > (const MeshFluidSource& other) const {
        return (_meshObject._priority > other._meshObject._priority);
    }


    void updateMeshStatic(TriangleMesh meshCurrent);
    void updateMeshAnimated(TriangleMesh meshPrevious, 
                            TriangleMesh meshCurrent, 
                            TriangleMesh meshNext);
    
    void enable();
    void disable();
    bool isEnabled();

    void setSubstepEmissions(int n);
    int getSubstepEmissions();

    void setInflow();
    bool isInflow();
    void setOutflow();
    bool isOutflow();

    void enableFluidOutflow();
    void disableFluidOutflow();
    bool isFluidOutflowEnabled();

    void enableDiffuseOutflow();
    void disableDiffuseOutflow();
    bool isDiffuseOutflowEnabled();

    void setVelocity(vmath::vec3 v);
    vmath::vec3 getVelocity();

    void enableAppendObjectVelocity();
    void disableAppendObjectVelocity();
    bool isAppendObjectVelocityEnabled();

    void setObjectVelocityInfluence(float value);
    float getObjectVelocityInfluence();

    bool isRigidBody();

    void enableConstrainedFluidVelocity();
    void disableConstrainedFluidVelocity();
    bool isConstrainedFluidVelocityEnabled();


    void outflowInverse();
    bool isOutflowInversed();

    void setFrame(int f, float frameInterpolation);
    void update(double dt);
    float trilinearInterpolate(vmath::vec3 p);
    void getCells(std::vector<GridIndex> &cells);
    void getCells(float frameInterpolation, std::vector<GridIndex> &cells);
    MeshObject* getMeshObject();
    MeshLevelSet* getMeshLevelSet();
    vmath::vec3 getMeshLevelSetOffset();
    RigidBodyVelocity getRigidBodyVelocity(double framedt);
    VelocityFieldData* getVelocityFieldData();
    int getID();

    void setPriority(int n);
    int getPriority();

    void setSourceID(int id);
    int getSourceID();

    void setViscosity(float v);
    float getViscosity();

    void setLifetime(float v);
    float getLifetime();
    void setLifetimeVariance(float v);
    float getLifetimeVariance();

    void setSourceColor(vmath::vec3 c);
    vmath::vec3 getSourceColor();

    int _isize = 0;
    int _jsize = 0;
    int _ksize = 0;
    double _dx = 0.0;
    MeshObject _meshObject;

private:

    void _initializeID();
    void _calculateVelocityFieldData();
    void _getGridBoundsFromTriangleMesh(TriangleMesh &m, double pad, 
                                        GridIndex &gmin, GridIndex &gmax);

    int _currentFrame = 0;
    float _currentFrameInterpolation = 0.0f;
    bool _isUpToDate = false;
    int _exactBand = 2;

    bool _isEnabled = true;
    int _substepEmissions = 1;
    bool _isInflow = true;
    bool _isFluidOutflowEnabled = true;
    bool _isDiffuseOutflowEnabled = true;
    bool _isOutflowInversed = false;
    bool _isConstrainedFluidVelocity = true;
    vmath::vec3 _sourceVelocity;
    VelocityFieldData _vfieldData;

    MeshLevelSet _sourceSDF;
    GridIndex _sourceSDFGridOffset;
    vmath::vec3 _sourceSDFOffset;
    double _gridpad = 4.0;

    int _ID;
    static int _IDCounter;

};

bool compareMeshFluidSourcePointer(MeshFluidSource *a, MeshFluidSource *b);
bool compareMeshFluidSourcePointerDescending(MeshFluidSource *a, MeshFluidSource *b);

#endif
