#ifndef IMAGEPATHS_H
#define IMAGEPATHS_H
#include <string>

namespace planeGameEngine {

	//Path variables to images
	class ImagePaths {
	public:

		//Background Sprites [bg]
		std::string bg_Level_1 = "Images/background.png";
		
		//Non-interactable Sprites [ni] 
		std::string ni_Cloud_1 = "Images/Cloud1.png";
		std::string ni_Cloud_2 = "Images/Cloud2.png";

		//Effects [fx]
		std::string fx_Bullet = "Images/Bullet.png";

		//Player Sprites [p]
		std::string p_Plane_1 = "Images/Fly1.png";

		//Enemy Sprites [e]
		std::string e_SpaceShip = "Images/Enemy1.png";
	};
	

}
#endif // !IMAGEPATHS_H
