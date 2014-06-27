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

#ifndef __SCENE_H_INCLUDE__
#define __SCENE_H_INCLUDE__


class SurfaceTask {
protected:
    shared_ptr<Surface> surface;

    bool started;

    i64u startTick;

    i64u lastTick;

    bool visible;

    i64u renderCount;


public:
    SurfaceTask() : started(false), startTick(0), lastTick(0), visible(false), renderCount(0) {
    }

    SurfaceTask(const shared_ptr<Surface> &surface) : surface(surface), started(false), startTick(0), lastTick(0), visible(false), renderCount(0) {
    }

    ~SurfaceTask() {
    }


    void start();
    void animate();
    void stop();


    void show();
    void render();
    void hide();
};


class Scene {
protected:
    map<string, SurfaceTask> surfaces;


public:
    Scene() {
    }

    ~Scene() {
    }


    void startAll();
    void start(const string &name);
    void animate();
    void stop(const string &name);
    void stopAll();

    void showAll();
    void show(const string &name);
    void render();
    void hide(const string &name);
    void hideAll();


    void addSurface(const string &name, const shared_ptr<Surface> &surface);
    void removeSurface(const string &name);
    void clearSurfaces();
};


#endif //__SCENE_H_INCLUDE__