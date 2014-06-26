#ifndef __SURFACE_H_INCLUDE__
#define __SURFACE_H_INCLUDE__


class Surface {
public:
	Surface() {

	}

	virtual ~Surface() {

	}


	void create();

	void destroy();


	void animate(double dt);

	void render();
};


#endif //__SURFACE_H_INCLUDE__