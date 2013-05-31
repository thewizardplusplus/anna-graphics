#ifndef LISTENER_H
#define LISTENER_H

#include "../maths/Vector3D.h"

namespace anna {
namespace sound {

class Listener {
public:
	inline virtual ~Listener(void);
	virtual maths::Vector3D<float> getPosition(void) const = 0;
	virtual void setPosition(const maths::Vector3D<float>& position) = 0;
	virtual maths::Vector3D<float> getForwardDirection(void) const = 0;
	virtual void setForwardDirection(
		const maths::Vector3D<float>& forward_direction) = 0;
	virtual maths::Vector3D<float> getUpDirection(void) const = 0;
	virtual void setUpDirection(const maths::Vector3D<float>& up_direction) = 0;
	virtual maths::Vector3D<float> getVelocity(void) const = 0;
	virtual void setVelocity(const maths::Vector3D<float>& velocity) = 0;
	virtual float getGain(void) const = 0;
	virtual void setGain(float gain) = 0;
};

Listener::~Listener(void) {}

}
}
#endif
