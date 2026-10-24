#include "Light.h"
#include "Shared.h"
Light::Light(LightType lightType, Object3D &lightObject)
{
    initializationHelper(lightType);
}

void Light::initializationHelper(LightType lightType)
{
    this->lightType = lightType;
    switch (this->lightType)
    {
        case DIRECTIONAL_LIGHT: {};
        case POINT_LIGHT: {};
        case SPOT_LIGHT: {};
    }
}
