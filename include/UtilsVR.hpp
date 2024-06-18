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
    /**
     * @brief The UtilsVRError class represents an error that can occur during UtilsVR operations.
    */
    class UtilsVRError : public Error {
        public:
            /**
             * @brief Constructs a UtilsVRError object with the given error message.
             * @param message The error message.
             * @param component The component that caused the error.
            */
            UtilsVRError(std::string const &message,
                std::string const &component = "UtilsVRError");

            /**
             * @brief Destroys the UtilsVRError object.
             */
            ~UtilsVRError() = default;
    };

    /**
     * @brief The UtilsVR class provides utility functions for VR applications.
    */
    class UtilsVR {
        public:
            /**
             * @brief Constructs a UtilsVR object.
            */
            UtilsVR();

            /**
             * @brief Destroys the UtilsVR object.
            */
            ~UtilsVR();

            /**
             * @brief Reads the content of an asset file.
             * @param filename The name of the asset file.
             * @return The content of the asset file.
            */
            static std::string readAssetFile(const std::string &filename);

            static android_app *app;    ///< The android app instance.
    };
}
#endif /* !UTILSVR_HPP_ */
