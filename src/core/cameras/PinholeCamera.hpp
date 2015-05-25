#ifndef PINHOLECAMERA_HPP_
#define PINHOLECAMERA_HPP_

#include "Camera.hpp"

namespace Tungsten {

class Scene;

class PinholeCamera : public Camera
{
    float _fovDeg;
    float _fovRad;
    float _planeDist;

    void precompute();

public:
    PinholeCamera();
    PinholeCamera(const Mat4f &transform, const Vec2u &res, float fov);

    virtual void fromJson(const rapidjson::Value &v, const Scene &scene) override;
    virtual rapidjson::Value toJson(Allocator &allocator) const override;

    virtual bool samplePosition(SampleGenerator &sampler, PositionSample &sample) const override final;
    virtual bool sampleDirection(SampleGenerator &sampler, const PositionSample &point,
            DirectionSample &sample) const override final;
    virtual bool sampleDirection(SampleGenerator &sampler, const PositionSample &point, Vec2u pixel,
            DirectionSample &sample) const override final;
    virtual bool sampleDirect(const Vec3f &p, SampleGenerator &sampler, LensSample &sample) const override final;
    virtual bool evalDirection(SampleGenerator &sampler, const PositionSample &point,
                const DirectionSample &direction, Vec3f &weight, Vec2f &pixel) const override final;
    virtual float directionPdf(const PositionSample &point, const DirectionSample &direction) const override final;

    virtual bool isDirac() const override;

    virtual bool generateSample(Vec2u pixel, SampleGenerator &sampler, Vec3f &throughput, Ray &ray) const override;

    virtual Mat4f approximateProjectionMatrix(int width, int height) const override;

    virtual float approximateFov() const override
    {
        return _fovRad;
    }

    float fovDeg() const
    {
        return _fovDeg;
    }
};

}

#endif /* PINHOLECAMERA_HPP_ */
