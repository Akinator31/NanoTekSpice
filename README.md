## NanoTekSpice

NanoTekSpice is a student project (Epitech) that implements a digital electronic circuit simulator.

It allows you to define components and their connections using `.nts` files and to run simulations from the command line.

## Project structure

Main layout (inside `src/`):

```
src/
├── Circuit/
│   ├── Circuit.cpp
│   └── Circuit.h++
├── Components/
│   ├── AdvancedComponents/
│   ├── ElementaryComponents/
│   ├── GatesComponents/
│   └── SpecialComponents/  (Clock, Input, Out, True, False, ...)
├── Errors/                 (exception definitions)
├── Factory/                (component factory)
├── Parser/                 (parsing of .nts files)
├── Utils/
└── main.cpp
```

All components implement the `IComponent` interface which provides at least the following methods:

- `simulate()` — simulate one clock tick for the component
- `compute(pin)` — compute the value of a given pin
- `link(pin, otherComponent, otherPin)` — connect a pin to another component's pin

## Exceptions

The project defines several domain-specific exceptions used during parsing and runtime:

- `NoFileException` — "No file was given as parameter!"
- `TooMuchArgumentsException` — "Too much arguments was given parameters!"
- `FileOpenException` — "Impossible to open the given file!"
- `SyntaxFileException` — "The circuit file includes one or several lexical or syntactic errors!"
- `ComponentTypeException` — "A component type is unknown!"
- `ComponentAlreadyExistException` — "Several components share the same name!"
- `ComponentNameException` — "A component name is unknown!"
- `InvalidValue` — "Invalid value when using input=value command!"

## `.nts` file format

An `.nts` circuit file is composed of two main sections: `chipset` (component declarations) and `links` (connections between pins).

The parser uses a state machine that switches between `CHIPSET` and `LINKS` modes to validate and construct the circuit.

Rules and examples:
- In `CHIPSET` mode: each line declares a component (type and name).
- In `LINKS` mode: each line declares a connection between two pins, e.g. `A:1 B:2`.

## Build and run
Typical build steps from the repository root:

```bash
cmake . .
make
```

The produced binary should be named `nanotekspice` 

To run the simulator:

```bash
./nanotekspice path/to/circuit.nts
```

This will start a command-line interface to interact with the loaded circuit (see example tests in `test/`).
