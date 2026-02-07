//
// Created by pavel on 06/02/2026.
//

#include "IComponent.h++"
#include "Circuit/Circuit.h++"
#include "Components/SpecialComponents/Input.h++"
#include "Factory/Factory.h++"

int main()
{
    nts::Factory factory;
    nts::Circuit new_circuit;

    std::unique_ptr<nts::IComponent> input1 = factory.createComponent("input");
    std::unique_ptr<nts::IComponent> input2 = factory.createComponent("input");
    std::unique_ptr<nts::IComponent> and_gate = factory.createComponent("and");
    std::unique_ptr<nts::IComponent> out = factory.createComponent("out");

    auto& inp1 = dynamic_cast<nts::Input&>(*input1);
    inp1.setValue(nts::True);

    auto& inp2 = dynamic_cast<nts::Input&>(*input2);
    inp2.setValue(nts::True);

    and_gate->setLink(1, *input1, 1);
    and_gate->setLink(2, *input2, 2);
    out->setLink(1, *and_gate, 3);

    new_circuit.add_component("and0", std::move(and_gate));
    new_circuit.add_component("a", std::move(input1));
    new_circuit.add_component("b", std::move(input2));
    new_circuit.add_component("out", std::move(out));

    new_circuit.simulate();
    new_circuit.display();

    return 0;
}
