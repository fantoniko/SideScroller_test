#include "useful_functions.h"

std::string getResourcePath(const std::string &subDir)
{
	const char PATH_SEP = '\\';
	static std::string baseRes;
	if (baseRes.empty()) {
		char *basePath = SDL_GetBasePath();
		if (basePath) {
			baseRes = basePath;
			SDL_free(basePath);
		}
		else {
			std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
			return "";
		}
		//We replace the last bin/ with res/ to get the the resource path
		size_t pos = baseRes.rfind("bin");
		baseRes = baseRes.substr(0, pos) + "Resources" + PATH_SEP;
	}
	return subDir.empty() ? baseRes : baseRes + subDir;
}

SDL_Texture* SurfToTexture(SDL_Renderer* renderer, const char* filename)
{
	SDL_Surface* surf = SDL_LoadBMP(filename);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	return texture;
}