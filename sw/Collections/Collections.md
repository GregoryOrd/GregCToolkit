# Collections Implementations

## Keeping this Implmentation Generic for Reuse

In an attempt to make these collections generic, the data inside of the nodes of these data structures are simply a void pointers. 

## Type Protection

Currently the mechanism for type protection is very loose. Each collection has an integer member
that the user can use to assign a type to the data of the collection.
Many collection functions then requires an integer argument representing this type to be passed in to allow the execution of the function.
The decision of which integer represents which data type will be left to the user of the collection and should be consistent through multiple uses of these collections in their application.

## Freeing A Collection

Since the Node has a void* for its data member, we do not know ahead of time how to free that data member.
Therefore, the user must provide a function pointer, as an argument to the collections' freeing functions, to define how to free the data type.