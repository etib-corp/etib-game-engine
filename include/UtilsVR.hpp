/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** UtilsVR
*/

#ifndef UTILSVR_HPP_
#define UTILSVR_HPP_

#include "external/vr/include/android_native_app_glue.h"
#include <android/log.h>
#include <android/native_activity.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "Error.hpp"


namespace EGE {

    class UtilsVRError : public Error {
        public:
            UtilsVRError(std::string const &message,
                std::string const &component = "UtilsVRError");
            ~UtilsVRError() = default;
    };

    class UtilsVR {
        public:
            UtilsVR();
            ~UtilsVR();

            static std::string readAssetFile(const std::string &filename);

            static android_app *app;

        protected:
        private:
    };
}
#endif /* !UTILSVR_HPP_ */
