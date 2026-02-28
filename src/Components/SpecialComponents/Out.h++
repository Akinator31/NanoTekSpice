//
// Created by pavel on 07/02/2026. Le mec est out.
//

#pragma once
#include "IComponent.h++"
#include "Components/AComponent.h++"

namespace nts {
    /**
     * @class Out
     * @brief Class for Out Special Component
     * @details This class inherit from IComponent interface
     * @see IComponent
     */
    class Out : public AComponent {
    public:
        /**
         * Output constructor
         */
        Out();
    };
}

///< Macro used for create a Out easily
#define CREATE_OUTPUT std::make_unique<Out>();
