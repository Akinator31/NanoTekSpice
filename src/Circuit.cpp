//
// Created by pavel on 07/02/2026.
//

#include <algorithm>
#include <iostream>
#include <vector>

#include "IComponent.h++"
#include "Components/Input.h++"
#include "Components/Out.h++"

namespace nts
{
    void Circuit::add_component(const std::string& name, std::unique_ptr<IComponent> component)
    {
        this->componentList[name] = std::move(component);
    }

    void Circuit::simulate()
    {
        this->_tick += 1;

        for (const auto &pair: this->componentList)
        {
            pair.second->simulate(this->_tick);
        }

        for (const auto &pair: this->componentList)
        {
            if (pair.first == "out")
            {
                pair.second->compute(0);
            }
        }
    }

    void Circuit::display()
    {
        std::vector<std::tuple<std::string, IComponent *>> inputs = {};
        std::vector<std::tuple<std::string, IComponent *>> outputs = {};

        for (const auto &pair: this->componentList)
        {
            if (dynamic_cast<Input *>(pair.second.get()))
            {
                inputs.emplace_back(pair.first, pair.second.get());
            }
            if (dynamic_cast<Out *>(pair.second.get()))
            {
                outputs.emplace_back(pair.first, pair.second.get());
            }
        }

        std::sort(inputs.begin(), inputs.end(), [](const auto &a, const auto &b)
        {
            return std::get<0>(a) < std::get<0>(b);
        });

        std::sort(outputs.begin(), outputs.end(), [](const auto &a, const auto &b)
        {
            return std::get<0>(a) < std::get<0>(b);
        });

        std::cout << "tick: " << this->_tick << std::endl;
        std::cout << "input(s):" << std::endl;

        for (const auto &pair: inputs)
        {
            std::cout << "  " << std::get<0>(pair) << ": " << dynamic_cast<Input *>(std::get<1>(pair))->getValue() << std::endl;
        }

        std::cout << "output(s):" << std::endl;

        for (const auto &pair: outputs)
        {
            std::cout << "  " << std::get<0>(pair) << ": " << dynamic_cast<Out *>(std::get<1>(pair))->getValue() << std::endl;
        }
    }
}
