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
		bool bounceActivated = false;
		bool gravityActivated = false;
		int refCount;
		int defaultPosX;
		int defaultPosY;
		double elasticity;

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
		bool affectedByGravity() { return gravityActivated; }
		void setAffectedByGravity(bool value) { gravityActivated = value; }
		bool bounceIsActivated() const { return bounceActivated; }
		void activateBounce(bool value, double elast = 1.0) { bounceActivated = value; elasticity = elast; }
		double getElasticity() const { return elasticity; }
		int getDefaultPosX() const { return defaultPosX; }
		int getDefaultPosY() const { return defaultPosY; }
		void setCollisionHandeled(bool value) { collisionHandeled = value; }
		bool isCollisionHandeled() const { return collisionHandeled; }
		void setXY(int x, int y);
		virtual int getCollisionWeight() const { return 0; }
		Sprite* makeTexture(std::string& imagepath) {}
		//Subclasses must override this function
		virtual void draw() = 0;

		//Subclasses can override these functions
		virtual void mouseDown(const SDL_Event& event) {}
		virtual void mouseUp(const SDL_Event& event) {}
		virtual void keyDown(const SDL_Event& event) {}
		virtual void keyUp(const SDL_Event& event) {}
		virtual void input(const SDL_Event& event) {}
		virtual void tick() {}
		virtual void collisionAction(Sprite* sprite, bool inferiorWeight) {}
		virtual void changeTextureForLevelChange() {}
		virtual void resetSpriteInstance() {}
		virtual void bounce(Sprite* other) {}
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