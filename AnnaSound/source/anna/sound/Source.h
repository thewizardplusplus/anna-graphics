#ifndef SOURCE_H
#define SOURCE_H

#include "../maths/Vector3D.h"

namespace anna {
namespace sound {

class Source {
public:
	enum OFFSET_UNITS {
		SECONDS,
		SAMPLES,
		BYTES
	};
	enum STATE {
		INITIAL,
		PLAYING,
		PAUSED,
		STOPPED,
		UNKNOWN
	};

	inline virtual ~Source(void);
	virtual maths::Vector3D<float> getPosition(void) const = 0;
	virtual void setPosition(const maths::Vector3D<float>& position) = 0;
	virtual maths::Vector3D<float> getVelocity(void) const = 0;
	virtual void setVelocity(const maths::Vector3D<float>& velocity) = 0;
	virtual maths::Vector3D<float> getDirection(void) const = 0;
	virtual void setDirection(const maths::Vector3D<float>& direction) = 0;
	virtual float getConeInnerAngle(void) const = 0;
	virtual void setConeInnerAngle(float angle_in_degrees) = 0;
	virtual float getConeOuterAngle(void) const = 0;
	virtual void setConeOuterAngle(float angle_in_degrees) = 0;
	virtual float getGain(void) const = 0;
	virtual void setGain(float gain) = 0;
	virtual float getConeOuterGain(void) const = 0;
	virtual void setConeOuterGain(float gain) = 0;
	virtual float getMinimalGain(void) const = 0;
	virtual void setMinimalGain(float minimal_gain) = 0;
	virtual float getMaximalGain(void) const = 0;
	virtual void setMaximalGain(float maximal_gain) = 0;
	virtual float getReferenceDistance(void) const = 0;
	virtual void setReferenceDistance(float reference_distance) = 0;
	virtual float getRolloffFactor(void) const = 0;
	virtual void setRolloffFactor(float rolloff_factor) = 0;
	virtual float getMaximalDistance(void) const = 0;
	virtual void setMaximalDistance(float maximal_distance) = 0;
	virtual float getPitch(void) const = 0;
	virtual void setPitch(float pitch) = 0;
	virtual bool getLooping(void) const = 0;
	virtual void setLooping(bool looping) = 0;
	virtual Source::STATE getState(void) const = 0;
	virtual float getOffset(Source::OFFSET_UNITS units) const = 0;
	virtual void setOffset(float offset, Source::OFFSET_UNITS units) = 0;
	virtual void play(void) = 0;
	virtual void pause(void) = 0;
	virtual void stop(void) = 0;
	virtual void rewind(void) = 0;
};

Source::~Source(void) {}

}
}
#endif
