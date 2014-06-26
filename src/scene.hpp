#ifndef __SCENE_H_INCLUDE__
#define __SCENE_H_INCLUDE__


#include <list>
#include <map>
#include <memory>
#include <string>

using namespace std;


#include "clock.hpp"


class Scene {
protected:
	class SurfaceTask {
	protected:
		shared_ptr<Surface> surface;

		bool started;

		unsigned long long startTick;

		unsigned long long lastTick;

		bool visible;

		unsigned long long renderCount;


	public:
		SurfaceTask() : started(false), startTick(0), lastTick(0), visible(false), renderCount(0) {
		}

		SurfaceTask(const shared_ptr<Surface> &surface) : surface(surface), started(false), startTick(0), lastTick(0), visible(false), renderCount(0) {
		}

		~SurfaceTask() {
		}


		void start() {
			if (!this->started) {
				this->started = true;
				this->startTick = this->lastTick = Clock::tick();
			}
		}

		void animate() {
			if (started) {
				double t = Clock::elapsed(this->startTick);
				double dt = Clock::elapsed(this->lastTick);

				this->lastTick = Clock::tick();
				this->surface->animate(t, dt);
			}
		}

		void end() {
			if (this->started) {
				this->lastTick = Clock::tick();
				this->started = false;
			}
		}


		void show() {
			if (!this->visible) {
				this->visible = true;
			}
		}

		void render() {
			if (this->visible) {
				this->surface->render();
				this->renderCount++;
			}
		}

		void hide() {
			if (this->visible) {
				this->visible = false;
			}
		}
	};


	map<string, SurfaceTask> surfaces;


public:
	Scene() {
	}

	virtual ~Scene() {

	}


	void animate() {
		for (list<SurfaceTask>::iterator it = this->surfaces.begin(); it != this->surfaces.end(); i++) {
			(*it).second.animate();
		}
	}

	void render() {
		for (list<SurfaceTask>::iterator it = this->surfaces.begin(); it != this->surfaces.end(); i++) {
			(*it).second.render();
		}
	}


	void addSurface(const string &name, shared_ptr<Surface> surface) {
		this->surfaces[name] = surface;
	}

	void removeSurface(const string &name) {
		this->surfaces.erase(name);
	}

	void clearSurfaces() {
		this->surfaces.clear();
	}
};


#endif //__SCENE_H_INCLUDE__