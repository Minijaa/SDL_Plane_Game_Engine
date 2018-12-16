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
			std::string bg_Level_2 = "Images/background2.png";
			std::string bg_Level_3 = "Images/background3_darker.png";

			//Non-interactable Sprites [ni] 
			std::string ni_Cloud_1 = "Images/Cloud1.png";
			std::string ni_Cloud_2 = "Images/Cloud2.png";


			//Effects [fx]
			std::string fx_Bullet = "Images/Bullet.png";

			//Player Sprites [p]
			std::string p_Plane_idle_1 = "Images/Fly1.png";
			std::string p_Plane_idle_2 = "Images/Fly2.png";

			//Enemy Sprites [e]
			std::string e_SpaceShip = "Images/Enemy1.png";

		//SOUNDS:
			//Sound Effect [sfx]
			std::string sfx_BulletSound = "Sfx/show.wav";
			//Music [m]
			std::string m_Level1_Music = "Sfx/L1Music.wav";

		//FONTS [f]:
			std::string f_BauhausFont= "Fonts/BAUHS93.TTF";
	};

	extern FilePaths path;
}
#endif // !IMAGEPATHS_H
