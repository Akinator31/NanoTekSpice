//
// Created by pavel on 07/02/2026.
//

#include "Circuit.h++"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

#include "IComponent.h++"
#include "Components/SpecialComponents/Input.h++"
#include "Components/SpecialComponents/Out.h++"
#include "Errors/NanoTekSpiceErrors.h++"

namespace nts
{
    bool Circuit::add_component(const std::string& name, std::unique_ptr<IComponent> component)
    {
        if (this->componentList.contains(name))
            return false;
        this->componentList[name] = std::move(component);
        return true;
    }

    void Circuit::simulate()
    {
        this->_tick += 1;

        for (const auto& pair : this->componentList)
        {
            pair.second->simulate(this->_tick);
        }

        for (const auto& pair : this->componentList)
        {
            if (pair.first == "out")
            {
                pair.second->compute(0);
            }
        }
    }

    void Circuit::loop()
    {
        std::cout << "loop" << std::endl;
    }

    void Circuit::assign([[maybe_unused]] std::string& command)
    {
        std::cout << "assign" << std::endl;
    }

    void Circuit::exit()
    {
        std::exit(0);
    }

    void Circuit::display() const
    {
        std::vector<std::tuple<std::string, IComponent*>> inputs = {};
        std::vector<std::tuple<std::string, IComponent*>> outputs = {};

        for (const auto& pair : this->componentList)
        {
            if (dynamic_cast<Input*>(pair.second.get()))
            {
                inputs.emplace_back(pair.first, pair.second.get());
            }
            if (dynamic_cast<Out*>(pair.second.get()))
            {
                outputs.emplace_back(pair.first, pair.second.get());
            }
        }

        std::sort(inputs.begin(), inputs.end(), [](const auto& a, const auto& b)
        {
            return std::get<0>(a) < std::get<0>(b);
        });

        std::sort(outputs.begin(), outputs.end(), [](const auto& a, const auto& b)
        {
            return std::get<0>(a) < std::get<0>(b);
        });

        std::cout << "tick: " << this->_tick << std::endl;
        std::cout << "input(s):" << std::endl;

        for (const auto& pair : inputs)
        {
            std::cout << "  " << std::get<0>(pair) << ": " << dynamic_cast<Input*>(std::get<1>(pair))->getValue() <<
                std::endl;
        }

        std::cout << "output(s):" << std::endl;

        for (const auto& pair : outputs)
        {
            std::cout << "  " << std::get<0>(pair) << ": " << dynamic_cast<Out*>(std::get<1>(pair))->getValue() <<
                std::endl;
        }
    }

    void Circuit::addLink(const std::string& componentName, const size_t componentPin,
                          const std::string& componentToLink,
                          const size_t componentToLinkPin)
    {
        if (!this->componentList.contains(componentName) || !this->componentList.contains(componentToLink))
            throw NanoTekSpiceException(ComponentNameException);
        this->componentList[componentName].get()->setLink(componentPin, *this->componentList[componentToLink],
                                                          componentToLinkPin);
        this->componentList[componentToLink].get()->setLink(componentToLinkPin, *this->componentList[componentName],
                                                            componentPin);
    }

    void Circuit::startCli()
    {
        std::string line;

        std::cout << "> ";
        while (getline(std::cin, line))
        {
            if (line == "exit")
            {
                exit();
            }
            if (line == "simulate")
            {
                simulate();
                std::cout << "> ";
                continue;
            }
            if (line == "display")
            {
                display();
                std::cout << "> ";
                continue;
            }
            if (line == "loop")
            {
                loop();
                std::cout << "> ";
                continue;
            }
            assign(line);
            std::cout << "> ";
        }
    }
}
