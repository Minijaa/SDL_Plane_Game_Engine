#ifndef SPRITE_H
#define SPRITE_H
#include <SDL.h>
#include <string>

namespace planeGameEngine {

	class Sprite
	{
	private:
		SDL_Rect rect;
		SDL_Surface* surf = nullptr;
		bool interactable;
		bool collisionHandeled = false;
		int refCount;

	public:
		//Inline function
		SDL_Surface* getSurf() const { return surf; }
		void setSurf(SDL_Surface* s) { surf = s; }
		SDL_Rect& getRect() { return rect; }
		bool isInteractable() const { return interactable; }
		int getRefCount() const { return refCount; }
		void incrementRefCount() { refCount++; }
		void decrementRefCount() { refCount--; }
		bool collisionDetected(Sprite* other);
		bool collidableColor(int x, int y);
		int& getX() { return rect.x; }
		int& getY() { return rect.y; }

		//Subclasses can override these functions
		virtual void mouseDown(const SDL_Event& event) {}
		virtual void mouseUp(const SDL_Event& event) {}
		virtual void keyDown(const SDL_Event& event) {}
		virtual void keyUp(const SDL_Event& event) {}
		virtual void input(const SDL_Event& event) {}
		virtual void tick() {}
		virtual void collisionAction(Sprite* sprite, bool inferiorWeight) {}
		virtual int getCollisionWeight() const { return 0; }
		virtual void changeTextureForLevelChange() {}
		void setCollisionHandeled(bool value) { collisionHandeled = value; }
		bool isCollisionHandeled() const { return collisionHandeled; }
		void setXY(int x, int y);
		Sprite* makeTexture(std::string& imagepath) {}
		//Subclasses must override this function
		virtual void draw() = 0;

		//Subclasses can override desctructor
		virtual ~Sprite() {}

		//Forbids copy constructor and assignment operator in order to prevent using value semantics
		Sprite(const Sprite&) = delete;
		const Sprite& operator=(const Sprite&) = delete;

	protected:
		Sprite(int x, int y, int w, int h, bool interactable = false);
		void setWH(int w, int h);

	};

}
#endif