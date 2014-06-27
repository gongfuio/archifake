/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "archifake.hpp"


void SurfaceTask::start() {
    if (!this->started) {
        this->started = true;
        this->startTick = this->lastTick = Clock::tick();
    }
}

void SurfaceTask::animate() {
    if (started) {
        f64 t = Clock::elapsed(this->startTick);
        f64 dt = Clock::elapsed(this->lastTick);

        this->lastTick = Clock::tick();
        this->surface->animate(t, dt);
    }
}

void SurfaceTask::stop() {
    if (this->started) {
        this->lastTick = Clock::tick();
        this->started = false;
    }
}

void SurfaceTask::show() {
    if (!this->visible) {
        this->visible = true;
    }
}

void SurfaceTask::render() {
    if (this->visible) {
        this->surface->render();
        this->renderCount++;
    }
}

void SurfaceTask::hide() {
    if (this->visible) {
        this->visible = false;
    }
}


void Scene::startAll() {
    for (auto it = this->surfaces.begin(); it != this->surfaces.end(); it++) {
        (*it).second.start();
    }
}

void Scene::start(const string &name) {
    this->surfaces[name].start();
}

void Scene::animate() {
    for (auto it = this->surfaces.begin(); it != this->surfaces.end(); it++) {
        (*it).second.animate();
    }
}

void Scene::stop(const string &name) {
    this->surfaces[name].stop();
}

void Scene::stopAll() {
    for (auto it = this->surfaces.begin(); it != this->surfaces.end(); it++) {
        (*it).second.stop();
    }
}

void Scene::showAll() {
    for (auto it = this->surfaces.begin(); it != this->surfaces.end(); it++) {
        (*it).second.show();
    }
}

void Scene::show(const string &name) {
    this->surfaces[name].show();
}

void Scene::render() {
    for (auto it = this->surfaces.begin(); it != this->surfaces.end(); it++) {
        (*it).second.render();
    }
}

void Scene::hide(const string &name) {
    this->surfaces[name].hide();
}

void Scene::hideAll() {
    for (auto it = this->surfaces.begin(); it != this->surfaces.end(); it++) {
        (*it).second.hide();
    }
}

void Scene::addSurface(const string &name, const shared_ptr<Surface> &surface) {
    this->surfaces[name] = surface;
}

void Scene::removeSurface(const string &name) {
    this->surfaces.erase(name);
}

void Scene::clearSurfaces() {
    this->surfaces.clear();
}
