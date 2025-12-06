# UI project format (scratch)

It'd be nice to keep things as close to text as possible, but failing that protobuf is probably a good intermediate. 

The library will convert to an internal repressentation which is the same regardless of if it loaded data via the game filesystem or a project, meaning the editor probably doesn't need to care. Tooling can use the library to convert game UI data to the project format (and vice versa).