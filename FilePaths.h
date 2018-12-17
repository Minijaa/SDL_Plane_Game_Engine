#ifndef IMAGEPATHS_H
#define IMAGEPATHS_H
#include <string>

namespace planeGameEngine {

	//Path variables to image, sound and font files.
	class FilePaths {
	public:
		//IMAGES:
			//Background Sprites [bg]
			std::string bg_Level_1 = "Images/background.png";
			std::string bg_Level_2 = "Images/background_night.png";
			std::string bg_Level_3 = "Images/background3_darker.png";

			//Non-interactable Sprites [ni] 
			std::string ni_Cloud_1 = "Images/Cloud1.png";
			std::string ni_Cloud_2 = "Images/Cloud2.png";
			std::string ni_Cloud_1d = "Images/Cloud1_dark.png";
			std::string ni_Cloud_2d = "Images/Cloud2_dark.png";

			//Effects [fx]
			std::string fx_Bullet = "Images/Bullet.png";

			//Player Sprites [p]
			std::string p_Plane_idle_1 = "Images/Fly1.png";
			std::string p_Plane_idle_2 = "Images/Fly2.png";

			//Enemy Sprites [e]
			std::string e_SpaceShip = "Images/Enemy1.png";

		//SOUNDS:
			//Sound Effect [sfx]
			std::string sfx_BulletSound = "Sfx/shot.wav";
			std::string sfx_BoomSound_1 = "Sfx/boom.wav";
			std::string sfx_BoomSound_2 = "Sfx/boom2.wav";

			//Music [m]
			std::string m_Level1_Music = "Sfx/L1Music.mp3";

		//FONTS [f]:
			std::string f_BauhausFont= "Fonts/BAUHS93.TTF";
	};

	extern FilePaths path;
}
#endif // !IMAGEPATHS_H
