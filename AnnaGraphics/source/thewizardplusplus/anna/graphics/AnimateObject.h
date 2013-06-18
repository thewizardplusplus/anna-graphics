#ifndef ANIMATEOBJECT_H
#define ANIMATEOBJECT_H

#include "Object.h"
#include "AnimateState.h"
#include "AnimateTrack.h"
#include "../maths/Maths.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class AnimateObject : public Object {
public:
	static AnimateObject* loadFromFile(const std::string& filename);

	AnimateObject(void);
	AnimateTrack* getTrack(void) const;
	void setTrack(AnimateTrack* track);
	size_t getNumberOfFrames(void) const;
	size_t getFps(void) const;
	void setFps(size_t fps);
	AnimateState::Types getState(void) const;
	size_t getStartFrame(void) const;
	size_t getEndFrame(void) const;
	bool isLoop(void) const;
	size_t getCurrentFrame(void) const;
	float getCurrentTime(void) const;
	void play(bool loop, size_t start_frame, size_t end_frame);
	void play(bool loop);
	void pause(bool pause);
	void stop(size_t frame);
	void stop(void);
	void update(float delta_time_in_ms);

private:
	AnimateTrack*       track;
	size_t              fps;
	AnimateState::Types state;
	size_t              start_frame;
	size_t              end_frame;
	bool                loop;
	float               current_time;

	void processUpdate(void);
};

}
}
}
#endif
