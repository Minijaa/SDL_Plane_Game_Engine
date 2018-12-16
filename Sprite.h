#ifndef SPRITE_H
#define SPRITE_H
#include <SDL.h>
#include <string>

namespace planeGameEngine {

	class Sprite
	{
	public:
		//Inline function
		SDL_Rect getRect() const {
			return rect;
		}
		bool isInteractable() const {
			return interactable;
		}


		//Subclasses can override these functions
		virtual void mouseDown(const SDL_Event& event) {}
		virtual void mouseUp(const SDL_Event& event) {}
		virtual void keyDown(const SDL_Event& event) {}
		virtual void keyUp(const SDL_Event& event) {}
		virtual void tick(const int iteractionCount) {}
		virtual void collisionAction(Sprite* sprite, bool inferiorWeight) {}
		virtual int getCollisionWeight() const { return 0; }
		virtual void changeTextureForLevelChange() {}

		void setFlagForDeletion(bool deletionValue) { flagForDeletion = deletionValue; }
		bool isFlaggedForDeletion() { return flagForDeletion; }
		Sprite* makeTexture(std::string& imagepath) {}
		//Subclasses must override this function
		virtual void draw() const = 0;

		//Subclasses can override desctructor
		virtual ~Sprite() {}

		//Forbids copy constructor and assignment operator in order to prevent using value semantics
		Sprite(const Sprite&) = delete;
		const Sprite& operator=(const Sprite&) = delete;

	protected:
		Sprite(int x, int y, int w, int h, bool interactable = false);
		void setWH(int w, int h);
		void setXY(int x, int y);

	private:
		SDL_Rect rect;
		bool interactable;
		bool flagForDeletion;
	};

}
#endif