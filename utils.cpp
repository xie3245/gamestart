#include "utils.h"

std::string getBasePath() noexcept {
    static std::string basePath = "";
    if (basePath == "") {
        auto bPath = SDL_GetBasePath();
        if (bPath) {
            basePath = std::string(bPath);
            SDL_free(const_cast<char*>(bPath));
        }
    }
    return basePath;
}