//
// Created by pavel on 07/02/2026.
//

#include "Circuit.h++"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

#include "Components/SpecialComponents/Clock.h++"
#include "Components/SpecialComponents/Input.h++"
#include "Components/SpecialComponents/Out.h++"
#include "Errors/NanoTekSpiceErrors.h++"
#include "IComponent.h++"
#include "Utils/Utils.h++"

namespace nts
{
    Circuit::Circuit()
    {
        this->_circuitFuncs["exit"] = [this](std::string& command) { exit(command); };
        this->_circuitFuncs["simulate"] = [this](std::string& command) { simulate(command); };
        this->_circuitFuncs["loop"] = [this](std::string& command) { loop(command); };
        this->_circuitFuncs["display"] = [this](std::string& command) { display(command); };
        this->_circuitFuncs["assign"] = [this](const std::string& command) { assign(command); };
    }

    bool Circuit::addComponent(const std::string& name, std::unique_ptr<IComponent> component)
    {
        if (this->_componentList.contains(name))
            return false;
        this->_componentList[name] = std::move(component);
        return true;
    }

    void Circuit::simulate([[maybe_unused]] std::string& command)
    {
        this->_tick += 1;

        for (const auto& pair : this->_componentList)
        {
            pair.second->simulate(this->_tick);
        }

        for (const auto& pair : this->_componentList)
        {
            if (dynamic_cast<Out*>(pair.second.get()))
            {
                dynamic_cast<Out*>(pair.second.get())->compute(1);
            }
        }
    }

    [[noreturn]] void Circuit::loop(std::string& command)
    {
        while (true)
        {
            this->simulate(command);
            this->display(command);
        }
    }

    void Circuit::assign(const std::string& command)
    {
        std::string segment;
        std::stringstream commandString(command);

        std::string inputName;
        std::string value;

        while (getline(commandString, segment, '='))
        {
            if (inputName.empty())
            {
                inputName = segment;
                continue;
            }
            if (value.empty())
            {
                value = segment;
            }
        }

        if (inputName.empty() || value.empty())
            return; // C'est une erreur lol ?

        auto* input = dynamic_cast<Input*>(this->_componentList[inputName].get());
        auto* clock = dynamic_cast<Clock*>(this->_componentList[inputName].get());
        if (!this->_componentList.contains(inputName) || (!input && !clock))
            throw NanoTekSpiceException(ComponentNameException);

        if (input)
            input->setValue(Utils::stringToTristate(value));
        else
            clock->setValue(Utils::stringToTristate(value));
    }

    void Circuit::exit([[maybe_unused]] std::string& command)
    {
        this->_cliDoesExit = true;
    }

    void Circuit::display([[maybe_unused]] std::string& command) const
    {
        std::vector<std::tuple<std::string, IComponent*>> inputsAndClocks = {};
        std::vector<std::tuple<std::string, IComponent*>> outputs = {};

        for (const auto& pair : this->_componentList)
        {
            if (pair.second->getType() == InputComponent || pair.second->getType() == ClockComponent)
            {
                inputsAndClocks.emplace_back(pair.first, pair.second.get());
            }
            if (pair.second->getType() == OutComponent)
            {
                outputs.emplace_back(pair.first, pair.second.get());
            }
        }

        std::sort(inputsAndClocks.begin(), inputsAndClocks.end(), [](const auto& a, const auto& b)
        {
            return std::get<0>(a) < std::get<0>(b);
        });

        std::sort(outputs.begin(), outputs.end(), [](const auto& a, const auto& b)
        {
            return std::get<0>(a) < std::get<0>(b);
        });

        std::cout << "tick: " << this->_tick << std::endl;
        std::cout << "input(s):" << std::endl;

        for (const auto& pair : inputsAndClocks)
        {
            IComponent* comp = std::get<1>(pair);

            if (comp->getType() == InputComponent || comp->getType() == ClockComponent)
                std::cout << "  " << std::get<0>(pair) << ": " << comp->compute(1) << std::endl;
        }

        std::cout << "output(s):" << std::endl;

        for (const auto& pair : outputs)
        {
            IComponent* comp = std::get<1>(pair);

            if (comp->getType() == OutComponent)
                std::cout << "  " << std::get<0>(pair) << ": " << comp->compute(1) << std::endl;
        }
    }

    void Circuit::addLink(
        const std::string& componentName, const size_t componentPin, const std::string& componentToLink,
        const size_t componentToLinkPin)
    {
        if (!this->_componentList.contains(componentName) || !this->_componentList.contains(componentToLink))
            throw NanoTekSpiceException(ComponentNameException);
        this->_componentList[componentName].get()->setLink(componentPin, *this->_componentList[componentToLink],
                                                           componentToLinkPin);
        this->_componentList[componentToLink].get()->setLink(componentToLinkPin, *this->_componentList[componentName],
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
            }
            else if (line.find('=') != std::string::npos)
            {
                this->_circuitFuncs["assign"](line);
            }
            if (this->_cliDoesExit)
                break;
            std::cout << "> ";
        }
    }
}
