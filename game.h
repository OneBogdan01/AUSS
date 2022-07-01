#pragma once
#include <vector>
#include "Player.h"
#include "Updateable.h"
#include "FollowCursor.h"
#include <SDL_Scancode.h>

namespace Tmpl8 {

	class Surface;
	class Game
	{
	public:
		void SetTarget(Surface* surface) { screen = surface; }

		void Init();
		void AddInstancesToUpdates();
		void Shutdown();
		void Tick(float deltaTime);
		void MouseUp(int button);
		void MouseDown(int button);
		void MouseMove(int x, int y);
		void KeyUp(SDL_Scancode key);
		void KeyDown(SDL_Scancode key);
	private:
		Surface* screen;
		Player* player;
		FollowCursor* cursor;

		std::vector<Updateable*> updateables;
		std::vector<Renderable*> renderables;

		bool isPressingLeftMouse = false;

		const Tmpl8::vec2 START_POS = Tmpl8::vec2(450, 400);
		const Tmpl8::vec2 COL_MIN = Tmpl8::vec2(0, 0);
		const Tmpl8::vec2 COL_MAX = Tmpl8::vec2(26, 26);

	};

}; // namespace Tmpl8