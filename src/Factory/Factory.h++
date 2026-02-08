//
// Created by pavel on 07/02/2026.
//

#pragma once
#include <functional>
#include <map>
#include <memory>
#include <string>

#include "IComponent.h++"

namespace nts
{
    /**
     * @brief Factory class for create components
     */
    class Factory
    {
        std::map<std::string, std::function<std::unique_ptr<IComponent> ()>> _builder = {}; ///< The map that stored component constructor functions

    public:
        /**
         * @brief Factory constructor. Initialize the map of components constructor functions.
         */
        Factory();

        /**
         *
         * @param type The of the component we want to create.
         * @throw std::exception Throw an exception if the type of the component given as parameter isn't support by the program.
         * @return std::unique_ptr<IComponent> The component newly created.
         */
        std::unique_ptr<IComponent> createComponent(const std::string &type);
    };
}
