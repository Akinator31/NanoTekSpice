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
    Circuit::Circuit()
    {
        this->_circuitFuncs["exit"] = [](std::string &command) { exit(command); };
        this->_circuitFuncs["simulate"] = [this](std::string &command) { simulate(command); };
        this->_circuitFuncs["loop"] = [](std::string &command) { loop(command); };
        this->_circuitFuncs["display"] = [this](std::string &command) { display(command); };
        this->_circuitFuncs["assign"] = [](std::string &command) { assign(command); };
    }

    bool Circuit::addComponent(const std::string& name, std::unique_ptr<IComponent> component)
    {
        if (this->componentList.contains(name))
            return false;
        this->componentList[name] = std::move(component);
        return true;
    }

    void Circuit::simulate([[maybe_unused]] std::string &command)
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

    void Circuit::loop([[maybe_unused]] std::string &command)
    {
        std::cout << "loop" << std::endl;
    }

    void Circuit::assign([[maybe_unused]] std::string& command)
    {
        std::cout << "assign" << std::endl;
    }

    void Circuit::exit([[maybe_unused]] std::string &command)
    {
        std::exit(0);
    }

    void Circuit::display([[maybe_unused]] std::string &command) const
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
            if (const Tristate state = dynamic_cast<Input*>(std::get<1>(pair))->getValue(); state == -1)
                std::cout << "  " << std::get<0>(pair) << ": U" << std::endl;
            else
                std::cout << "  " << std::get<0>(pair) << ": " << dynamic_cast<Input*>(std::get<1>(pair))->getValue() <<
                    std::endl;
        }

        std::cout << "output(s):" << std::endl;

        for (const auto& pair : outputs)
        {
            if (const Tristate state = dynamic_cast<Out*>(std::get<1>(pair))->getValue(); state == -1)
                std::cout << "  " << std::get<0>(pair) << ": U" << std::endl;
            else
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
            if (this->_circuitFuncs.contains(line))
            {
                this->_circuitFuncs[line](line);
            } else
            {
                this->_circuitFuncs["assign"](line);
            }
            std::cout << "> ";
        }
    }
}
